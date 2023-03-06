#include "Common.hpp"

LinkedList::LinkedList(std::vector<std::string> const& headers)
{
    for(auto& v : headers)
    {
        m_list = curl_slist_append(m_list, v.c_str());
    }
}
