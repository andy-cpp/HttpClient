#pragma once
#include "Common.hpp"
#include "Header.hpp"

class Request;

class Response
{
protected:
    friend class Request;
    void PrePerform(CURL* handle);

    void PostPerform();
public:

public:
    long code = 0;
    std::string body;
    Headers headers;
    CURL* handle = 0;
};
