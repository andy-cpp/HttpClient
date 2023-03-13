#include <thread>
#include "Request.hpp"
#include <stdexcept>

Request::Request()
{
    m_handle = curl_easy_init();
    #if CONFIG_TIMEOUT_MS != 0
    curl_easy_setopt(m_handle, CURLOPT_TIMEOUT_MS, CONFIG_TIMEOUT_MS);
    #endif
}

void Request::SetHeader(std::string const& key, std::string const& value)
{
    m_headers.Set(key, value);
}

void Request::SetHeaders(std::vector<std::pair<std::string, std::string>> const& headers)
{
    for(auto& header : headers)
    {
        m_headers.Set(header.first, header.second);
    }
}

void Request::SetBody(std::string const& body)
{
    m_body = body;
    curl_easy_setopt(m_handle, CURLOPT_POSTFIELDS, m_body.c_str());
    curl_easy_setopt(m_handle, CURLOPT_POSTFIELDSIZE, m_body.size());
}

void Request::ThreadHandler(std::string const& url, Request::callback_t callback)
{
    Response& response = this->Go(url);

    callback(*this, response);
}

void Request::Go(std::string const& url, callback_t callback)
{
    std::thread(&ThreadHandler, this,url, callback).detach();
}

Response& Request::Go(std::string const& url)
{
    m_response.PrePerform(m_handle);
    
    LinkedList headerlist = m_headers.ToList();
    curl_easy_setopt(m_handle, CURLOPT_HTTPHEADER, headerlist.GetList());
    curl_easy_setopt(m_handle, CURLOPT_URL, url.c_str());
    curl_easy_perform(m_handle);

    #ifdef CONFIG_EXCEPTIONS
    if(ret != CURLE_OK){
        throw std::runtime_error(std::string("Error performing request: ") + curl_easy_strerror(ret));
    }
    #endif
    m_response.PostPerform();
    return m_response;
}