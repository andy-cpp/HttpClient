#pragma once
#include <functional>
#include "Common.hpp"
#include "Response.hpp"
class Request
{
public:
    using callback_t = std::function<void(Request& request, Response& response)>;
    Request();

    ~Request()
    {
        curl_easy_cleanup(m_handle);
    }

    CURL* GetHandle(){return m_handle;}

    void SetHeader(std::string const& key, std::string const& value);

    void SetHeaders(std::vector<std::pair<std::string, std::string>> const& headers);

    void SetBody(std::string const& body);

    template <typename T>
    bool SetOption(CURLoption opt, T const& value)
    {
        return curl_easy_setopt(m_handle, opt, value) == CURLE_OK;
    }

    void Go(std::string const& url, callback_t callback);

    Response& Go(std::string const& url);
private:
    void ThreadHandler(std::string const& url, callback_t cb);

private:
    std::string m_body;
    Headers m_headers;
    Response m_response;
    CURL* m_handle = 0;
};
