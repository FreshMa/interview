#include "ini_parser.h"
#include <sstream>
#include <iostream>

namespace qh
{
    INIParser::INIParser(){}
    INIParser::~INIParser(){}

    bool INIParser::Parse(const std::string &ini_file_path)
    {
        return true;
        
    }
    bool INIParser::Parse(const char *ini_data, size_t ini_data_len, const std::string &line_seperator, const std::string &key_value_seperator)
    {
        std::string ini_data_str = ini_data;
        size_t found = 0;
        size_t pos = 0;

        // 按line_sep分割字符串，获取param，长度不为0才加入vector<string> params中
        while(pos < ini_data_str.length() && (found = ini_data_str.find(line_seperator, pos)) != std::string::npos)
        {
            std::string tmp = ini_data_str.substr(pos, found-pos);
            if(tmp.length() > 0)
            {
                params.push_back(tmp);
            }
            pos = found + line_seperator.length();
        }

        // 末尾是否有param
        if(found == std::string::npos)
        {
            size_t nreadable = ini_data_str.length() - pos;
            if(nreadable > 0){
                params.push_back(ini_data_str.substr(pos, nreadable));
            }
        }

        //遍历params，处理每一个键值对，如果存在不合法的param,返回false
        for(size_t i = 0; i < params.size(); ++i)
        {
            if(!ParsePair(params[i], key_value_seperator))
                return false;
        }
        return true;
    }

    const std::string& INIParser::Get(const std::string &key, bool *found)
    {
        find_result.clear();
        auto it = kv_map.find(key);
        if(it != kv_map.end())
        {
            *found = true;
            find_result = it->second;
        }
        else
        {
            *found = false;
        }
        return find_result;
        
    }

    const std::string& INIParser::Get(const std::string &section, const std::string &key, bool *found)
    {
        find_result.clear();
        return find_result;
    }

    //是否成功转换一个键值对
    bool INIParser::ParsePair(const std::string &line, const std::string &kv_sep)
    {
        size_t found = 0;
        found = line.find(kv_sep);
        int key_len = found;
        int value_len = line.length() - key_len - kv_sep.length();

        if(key_len > 0){
            std::string key = line.substr(0,key_len);
            std::string value = line.substr(found + kv_sep.length(), value_len);
            kv_map[key] = value;
            return true;
        }
        else{
            return false;
        }
    }
}
