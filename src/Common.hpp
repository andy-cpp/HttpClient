#pragma once
#include <vector>
#include <string>

#include <curl/curl.h>


class LinkedList
{
public:
    LinkedList(std::vector<std::string> const& headers);

    ~LinkedList()
    {
        curl_slist_free_all(m_list);
    }

    curl_slist* GetList() {return m_list;}

private:
    curl_slist* m_list = 0;
};