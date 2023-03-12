#include "Response.hpp"

static size_t write_header_cb(char* buffer, size_t size, size_t nitems, Headers* userdata)
{
    char* delim_pos = strchr(buffer, ':');
    if(delim_pos == 0){
        return nitems * size;
    }

    char* key = buffer;
    char* value = delim_pos + 2;
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

void Response::PrePerform(CURL* handle_)
{
    handle = handle_;
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_body_cb);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &body);

    curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, write_header_cb);
    curl_easy_setopt(handle, CURLOPT_WRITEHEADER, &headers);
}

void Response::PostPerform()
{
    curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &code);
}