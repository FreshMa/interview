#include "ini_parser.h"

#include <string.h>
#include <assert.h>
#include <iostream>

void test1()
{
    const char* ini_text= "a=1\nb=2\n"; 
    bool found = false;
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }
    
    const std::string& a = parser.Get("a", &found);
    assert(a == "1");
    assert(found);

    std::string b = parser.Get("b", &found);
    assert(b == "2");
    assert(found);

    const std::string& c = parser.Get("c", &found);
    assert(c == "");
    assert(!found);
}

void test2()
{
    const char* ini_text= "a=1||b=2||c=3"; 
    qh::INIParser parser;
    bool found = false;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", &found);
    assert(a == "1");
    assert(found);

    std::string b = parser.Get("b", &found);
    assert(b == "2");
    assert(found);

    const std::string& c = parser.Get("c", &found);
    assert(c == "3");
    assert(found);
}

void test3()
{
    const char* ini_text= "||||a:1||b:2||||c:3||||||"; 
    qh::INIParser parser;
    bool found = false;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", &found);
    assert(a == "1");
    assert(found);

    std::string b = parser.Get("b", &found);
    assert(b == "2");
    assert(found);

    const std::string& c = parser.Get("c", &found);
    assert(c == "3");
    assert(found);
}

void test4()
{
    const char* ini_text = "[one]\na=3\nb=2\nc=1[two]\nd=6\ne=5\nf=4";
    qh::INIParser parser;
    bool found = false;
    if(!parser.Parse(ini_text, strlen(ini_text), "\n", "="))
        assert(false);
    
    const std::string& a = parser.Get("one", "a", &found);
    assert(a == "3");
    assert(found);

    std::string b = parser.Get("two", "b", &found);
    assert(b == "");
    assert(!found);

    const std::string& e = parser.Get("two", "e", &found);
    assert(e == "5");
    assert(found);
}

//文件测试
void test5()
{
    std::string file = "test_file.txt";
    bool found = false;
    qh::INIParser parser;
    if(!parser.Parse(file))
        assert(false);

    const std::string& name = parser.Get("owner", "name", &found);
    assert(name == "John Doe");
    assert(found);

    const std::string& org = parser.Get("owner", "organization", &found);
    assert(org == "Acme Products");
    assert(found);

    const std::string& ip = parser.Get("database", "server", &found);
    assert(ip == "192.0.2.42");
    assert(found);

    const std::string& age = parser.Get("owner", "age", &found);
    assert(age == "");
    assert(!found);

    const std::string& f = parser.Get("database", "file",&found);
    assert(f=="\"acme payroll.dat\"");
}

void test6()
{
    const char* ini_text = "[owner]\nname=John Doe\norganization=Acme Products\n[database]\nserver=192.0.2.42";
    //; use IP address in case network name resolution is not working\nport=143\nfile = \"acme payroll.dat\"";
    qh::INIParser parser;
    bool found = false;
    if(!parser.Parse(ini_text, strlen(ini_text), "\n", "="))
        assert(false);
    
    const std::string& a = parser.Get("owner", "name", &found);
    assert(a == "John Doe");
    assert(found);

    const std::string& org = parser.Get("owner", "organization", &found);
    assert(org == "Acme Products");
    assert(found);

    const std::string& ip = parser.Get("database", "server", &found);
    assert(ip == "192.0.2.42");
    assert(found);

    const std::string& age = parser.Get("owner", "age", &found);
    assert(age == "");
    assert(!found);

}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    return 0;
}


