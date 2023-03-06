#pragma once
#include "Common.hpp"
#include "Header.hpp"
class Request;

class Response
{
protected:
    friend class Request;
    Response(CURL* handle);

    void PostPerform();
public:


private:
    long m_code = 0;
    std::string m_body;
    Headers m_headers;
    CURL* m_handle = 0;
};