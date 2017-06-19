#include "qh_string.h"
#include <stdio.h>
#include <string.h>

namespace qh
{
    // TODO
    // 长度为0的空串，避免data_为NULL
    string::string()
        :len_(0)
    {
        data_ = new char[1];
        data_[0] = '\0';
    }

    /**
    * 
    * 时间复杂度： O(n)，n为s的长度
    * 空间复杂度： O(n)，构造了新的字符串
    * 无内存泄漏
    */
    string::string( const char* s )
    {
        assign(s,strlen(s));
    }
    /**
    * 时间复杂度： O(n)，n为s的长度
    * 空间复杂度： O(len)，构造了新的字符串
    * 无内存泄漏
    */
    string::string( const char* s, size_t len )
    {
        assign(s,len);
    }

    /**
    * 以下两个函数时间和空间复杂度一样
    * 时间复杂度： O(n)，n为s的长度
    * 空间复杂度： O(n)，构造了新的字符串
    * 无内存泄漏
    */
    string::string( const string& rhs )
    {
        assign(rhs.c_str(),rhs.size());
    }

    string& string::operator=( const string& rhs )
    {
        if(this == &rhs){
            return *this;
        }
        
        delete [] data_;
        assign(rhs.c_str(),rhs.size());

        return *this;
    }

    /**
    * 析构函数，防止内存泄漏
    * 时间复杂度： O(n)，从后往前删除元素
    * 空间复杂度： O(1)
    */
    string::~string()
    {
        // 判断可以省略，因为data_不可能为NULL
        if(data_)
            delete [] data_;
    }

    /**
    * 以下四个函数空间复杂度和时间复杂度一样
    * 时间复杂度： O(1)
    * 空间复杂度：O(1)，不需要额外空间
    * 无内存泄漏
    */
    size_t string::size() const
    {
        return len_;
    }

    // 在c++11中，data和c_str函数没有区别，之前的版本中data的返回没有结束符
    const char* string::data() const
    {
        return data_;
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char* string::operator[]( size_t index )
    {
        if(index < len_){
            return &data_[index];
        }
        else
            return NULL;
    }

    /**
    * 时间复杂度： O(n)，n为s的长度
    * 空间复杂度： O(n)，构造了新的字符串
    * 无内存泄漏
    */
    void string::assign(const char* s, int len)
    {
        len_ = len;
        data_ = new char[len + 1];
        strncpy(data_, s, len);
    }
}