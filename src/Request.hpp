#pragma once
#include "Common.hpp"
#include "Response.hpp"
class Request
{
public:
    Request();

    ~Request()
    {
        curl_easy_cleanup(m_handle);
    }

    void SetHeader(std::string const& header);

    void SetHeader(std::vector<std::string> const& headers);

    template <typename T>
    bool SetOption(CURLoption opt, T const& value)
    {
        return curl_easy_setopt(m_handle, opt, value) == CURLE_OK;
    }

    Response Go(std::string const& url);

private:
    CURL* m_handle = 0;
};