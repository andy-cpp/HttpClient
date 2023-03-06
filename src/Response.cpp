#include "Response.hpp"

static size_t write_header_cb(char* buffer, size_t size, size_t nitems, Headers* userdata)
{
    char* delim_pos = strchr(buffer, ':');
    if(delim_pos == 0){
        return nitems * size;
    }

    char* key = buffer;
    char* value = delim_pos + 1;
    char* end = strstr(buffer, "\r\n");
    *delim_pos = 0;
    userdata->Set(key, std::string(value, end - value));
    return nitems * size;
}

static size_t write_body_cb(char* buffer, size_t size, size_t nmemb, std::string* userdata)
{
    userdata->append(buffer, std::size_t(nmemb));
    return size * nmemb;
}

Response::Response(CURL* handle) : m_handle(handle)
{
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_body_cb);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &m_body);

    curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, write_header_cb);
    curl_easy_setopt(handle, CURLOPT_WRITEHEADER, &m_headers);
}

void Response::PostPerform()
{
    curl_easy_getinfo(m_handle, CURLINFO_RESPONSE_CODE, &m_code);
}