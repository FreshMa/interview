#include "ini_parser.h"

#include <string.h>
#include <assert.h>

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

    std::string b = parser.Get("b", &found);
    assert(b == "2");

    const std::string& c = parser.Get("c", &found);
    assert(c == "");
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

    std::string b = parser.Get("b", &found);
    assert(b == "2");

    const std::string& c = parser.Get("c", &found);
    assert(c == "3");
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

    std::string b = parser.Get("b", &found);
    assert(b == "2");

    const std::string& c = parser.Get("c", &found);
    assert(c == "3");
}

void test4()
{
    const char* ini_text = "[one]\na=3\nb=2\nc=1[two]\nd=6\ne=5\nf=4";
    qh::INIParser parser;
    bool found = false;
    if(!parser.Parse(ini_text, strlen(ini_text), "\n", "="))
        assert(false);
    
    const std::string& a = parser.Get("one", "a", &found);
    assert(a == "1");

    std::string b = parser.Get("two", "b", &found);
    assert(b == "");

    const std::string& e = parser.Get("two", "e", &found);
    assert(e == "5");
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好

    test1();
    test2();
    test3();

    return 0;
}


