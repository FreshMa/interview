
#ifndef QIHOO_INI_PARSER_H_
#define QIHOO_INI_PARSER_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

namespace qh
{
    class INIParser
    {
    public:
        INIParser();
        ~INIParser();

        //! \brief 解析一个磁盘上的INI文件
        //! \param[in] -  const std::string & ini_file_path
        //! \return - bool
        bool Parse(const std::string& ini_file_path);

        //! \brief 解析一段形如INI格式的内存数据。
        //!   例如：ini_data="a:1||b:2||c:3"
        //!         调用<code>Parse(ini_data, ini_data_len, "||", ":")</code>即可解析出这段数据。
        //!         解析完毕之后 
        //!         Get("a")=="1" && Get("b")=="2" && Get("c")=="3"
        //! \param[in] - const char * ini_data
        //! \param[in] - size_t ini_data
        //! \param[in] - const std::string & line_seperator
        //! \param[in] - const std::string & key_value_seperator
        //! \return - bool
        bool Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator = "\n", const std::string& key_value_seperator = "=");

        //! \brief 从默认section中查找某个key，并返回找到的value。如果找不到，返回一个空串
        //! \param[in] - const std::string & key
        //! \param[in] - bool * found - 输出参数，true表明找到这个key
        //! \return - const std::string& - 返回的具体key对应的value
        const std::string& Get(const std::string& key, bool* found);

        const std::string& Get(const std::string& section, const std::string& key, bool* found);

    private:
        using ssmap = std::unordered_map<std::string, std::string>;
        
        //存储Get的结果，防止返回局部变量的引用
        std::string find_result;
        
        std::unordered_map<std::string, ssmap> sec_map;
        
        // 去掉字符串的注释，注释从字符';'和'#'开始直到该行结束
        void skipComment(std::string &content);

        //sec_names存放<section出现的位置, section名称>,并按照key值，即pos排序
        void setSecName(const std::string &content, std::map<int, std::string> &sec_names);

        bool Parse(const std::string &content, const std::string &line_sep, const std::string &kv_sep);

        //对section的内容进行解析，解析结果放到kv_map中
        bool ParseSection(ssmap& kv_map, const std::string &section_content, const std::string &line_sep = "\n", const std::string &kv_sep = "=");

        //section中每一行代表一个键值对，解析该键值对，将结果存放到kv_map中
        bool ParsePair(const std::string &line, const std::string &kvsep, ssmap &kv_map);
        
    };
}

#endif
