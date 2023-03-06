#pragma once
#include "Common.hpp"
class Headers
{
public:
    Headers() = default;

    std::string Get(std::string const& key) const
    {
        return m_headers.at(key);
    }

    std::string Set(std::string const& key, std::string const& value)
    {
        m_headers[key] = value;
    }

    bool Exists(std::string const& key)
    {
        return m_headers.find(key) != m_headers.end();
    }

    LinkedList ToList()
    {
        std::vector<std::string> vec;
        for(auto& h : m_headers)
        {
            vec.push_back(h.first + ": " + h.second);
        }
        return LinkedList(vec);
    }

    std::unordered_map<std::string, std::string>& GetMap(){return m_headers;}
private:
    std::unordered_map<std::string, std::string> m_headers;
};