#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "qh_string.h"

int main(int argc, char *argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。

    //四种拷贝构造函数测试
    
    qh::string str1;
    qh::string str2 = "thisistest";
    qh::string str3("justfortestit", 5);
    qh::string str4 = str2;
    qh::string str5 = str1;
    qh::string str6 = "";

    //size函数
    assert(str1.size() == 0);
    assert(str2.size() == 10);
    assert(str3.size() == 5);
    assert(str4.size() == 10);
    assert(str5.size() == 0);
    assert(str6.size() == 0);

    //c_str和data函数
    assert(strcmp(str2.c_str(), "thisistest") == 0);
    assert(strcmp(str2.data(), "thisistest") == 0);
    assert(strcmp(str3.data(), "justf") == 0);
    assert(strcmp(str2.c_str(), "thisistest") == 0);
    assert(strcmp(str5.c_str(), "") == 0);
    assert(strcmp(str6.c_str(), "") == 0);

    //赋值运算符
    str1 = str3;
    assert(str1.size() == 5);
    assert(strcmp(str3.data(), "justf") == 0);
    str1 = str6;
    assert(str1.size() == 0);
    assert(strcmp(str1.data(), "") == 0);
    

    //重载[]
    *str2[2] = '2';
    assert('2' == *str2[2]);

    //调用[]失败
    assert(NULL == str2[20]);
    assert(NULL == str2[-1]);

#ifdef WIN32
    system("pause");
#endif

    return 0;
}