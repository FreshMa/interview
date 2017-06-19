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
        std::unordered_map<std::string,int> sec_names;
        std::vector<std::string> sec_content;

        //去掉注释
        skipComment(ini_data_str);
        
        //找到section
        setSecName(ini_data_str, sec_names);

        //如果没有section，直接处理该文本
        if(sec_names.empty()){
            ssmap kv_map;
            if(ParseSection(kv_map, ini_data_str, line_seperator, key_value_seperator))
            {
                sec_map["default_section_randomstr_xxxyyyzzz"] = kv_map;
                return true;
            }
            return false;
        }  
        
        std::vector<std::string> sec_set;
        sec_set.reserve(sec_names.size());
        std::vector<int> pos_set;
        pos_set.reserve(sec_names.size());

        for(auto it = sec_names.begin(); it!=sec_names.end();++it)
        {
            sec_set.push_back(it->first);
            pos_set.push_back(it->second);
        }
        pos_set.push_back(ini_data_str.length());
        for(size_t i = 0; i < sec_set.size(); ++i)
        {
            std::string sec_name = sec_set[i];
            int skip_length = pos_set[i] + sec_name.length() + 2;
            std::string content = ini_data_str.substr(skip_length, pos_set[i+1]-skip_length);
            ssmap tmp_kv_map;
            if(!ParseSection(tmp_kv_map, content, line_seperator, key_value_seperator))
                return false;
            sec_map[sec_name] =tmp_kv_map;
        }
        return true;
        
    }

    const std::string& INIParser::Get(const std::string &key, bool *found)
    {
        find_result.clear();
        auto kv_map = sec_map["default_section_randomstr_xxxyyyzzz"];
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
        ssmap kv_map = sec_map[section];
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

    void INIParser::skipComment(std::string &content)
    {
        size_t len = content.length();
        std::string newContent;
        newContent.reserve(len);
        
        for(size_t i = 0;i < len; )
        {
            if(content[i] != ';' && content[i] != '#')
            {
                newContent.push_back(content[i]);
                ++i;
            }
            else
            {
                //不删除换行符
                while(content[i++]!='\n');
                --i;
            }
        }
        content.swap(newContent);
        content.shrink_to_fit();
    }

    void INIParser::setSecName(std::string &content, std::unordered_map<std::string, int> &sec_names)
    {
        for(size_t i = 0;i<content.length();)
        {
            if(content[i] == '[')
            {
                int sec_start = i + 1;
                while(content[i++]!=']');
                int sec_name_len = i - sec_start - 1;
                sec_names[content.substr(sec_start, sec_name_len)] = sec_start - 1;
            }
            else
                ++i;
        }
    }
    bool INIParser::ParseSection(ssmap &kv_map, const std::string &section_content, const std::string &line_sep, const std::string &kv_sep)
    {
        size_t found = 0;
        size_t pos = 0;

        // 按line_sep分割字符串，获取param，长度不为0才加入vector<string> params中
        while(pos < section_content.length() && (found = section_content.find(line_sep, pos)) != std::string::npos)
        {
            std::string tmp = section_content.substr(pos, found-pos);
            if(tmp.length() > 0)
            {
                params.push_back(tmp);
            }
            pos = found + line_sep.length();
        }

        // 末尾是否有param
        if(found == std::string::npos)
        {
            size_t nreadable = section_content.length() - pos;
            if(nreadable > 0){
                params.push_back(section_content.substr(pos, nreadable));
            }
        }

        //遍历params，处理每一个键值对，如果存在不合法的param,返回false
        for(size_t i = 0; i < params.size(); ++i)
        {
            if(!ParsePair(params[i], kv_sep, kv_map))
                return false;
        }
        return true;
    }

    //是否成功转换一个键值对
    bool INIParser::ParsePair(const std::string &line, const std::string &kv_sep, ssmap &kv_map)
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
            kv_map.clear();
            return false;
        }
    }
}
