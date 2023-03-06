#include "Request.hpp"

Request::Request()
{
    m_handle = curl_easy_init();
}

void Request::SetHeader(std::string const& header)
{
    curl_slist* list = curl_slist_append(0, header.c_str());
    curl_easy_setopt(m_handle, CURLOPT_HTTPHEADER, list);
    curl_slist_free_all(list);

}

void Request::SetHeader(std::vector<std::string> const& headers)
{
    curl_easy_setopt(m_handle, CURLOPT_HTTPHEADER, LinkedList(headers).GetList());
}

Response Request::Go(std::string const& url)
{
    Response response(m_handle);
    curl_easy_setopt(m_handle, CURLOPT_URL, url.c_str());
    curl_easy_perform(m_handle);

    response.PostPerform();
    return response;
}