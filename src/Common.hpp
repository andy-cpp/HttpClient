#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

#include <curl/curl.h>
#include <curl/easy.h>

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