#pragma once
#include <memory>
#include <curl/curl.h>
#include <curl/easy.h>

#include "Common.hpp"

class Request
{
public:
    Request();

    void SetHeader(std::string const& header);

    void SetHeader(std::vector<std::string> const& headers);

    template <typename T>
    bool SetOption(CURLoption opt, T const& value)
    {
        return curl_easy_setopt(m_handle, opt, value) == CURLE_OK;
    }

    void Go(std::string const& url);

private:
    CURL* m_handle = 0;
};