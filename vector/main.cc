#include <stdlib.h>
#include "qh_vector.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <string.h>



int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。

    //-------------------------------------------------int start------------------------------------------
    //int类型，普通类型
    //ctor
    qh::vector<int> num_vect;
    qh::vector<int> num_vect1(5);
    qh::vector<int> num_vect2(5,4);
    qh::vector<int> num_vect3 = num_vect2;
    qh::vector<int> num_vect4;
    num_vect4 = num_vect1;

    //size()
    assert(num_vect.size() == 0);
    assert(num_vect1.size() == 5);
    assert(num_vect2.size() == 5);
    assert(num_vect3.size() == num_vect2.size());
    assert(num_vect4.size() == num_vect1.size());

    //capacity() 至少为1
    assert(num_vect.capacity() == 1);
    assert(num_vect1.capacity() == 5);
    assert(num_vect2.capacity() == 5);
    assert(num_vect3.capacity() == num_vect2.capacity());
    assert(num_vect4.capacity() == num_vect1.capacity());

    //push_back  pop_back
    num_vect.push_back(1);
    num_vect.push_back(1);
    num_vect.push_back(1);

    assert(num_vect.size() == 3 && num_vect.capacity() == 4);

    num_vect.pop_back();
    assert(num_vect.size()==2 && num_vect.capacity() == 4);

    num_vect1.push_back(2);
    assert(num_vect1.size()==6 && num_vect1.capacity() == 10);

    //重载[]
    assert(num_vect[0] == 1);
    //函数中使用assert处理越界，运行终止
    //assert(num_vect[10]);

    //resize() 一定改变size
    num_vect.resize(1);
    assert(num_vect.size() == 1 && num_vect.capacity() == 4);
    num_vect.resize(3);
    assert(num_vect.size() == 3 && num_vect.capacity() == 4);
    num_vect.resize(8);
    assert(num_vect.size() == 8 && num_vect.capacity() == 8);

    //reserve() 只在需要扩容的时候改变capacity
    num_vect.reserve(1);
    assert(num_vect.size() == 8 && num_vect.capacity() == 8);
    num_vect.reserve(12);
    assert(num_vect.size() == 8 && num_vect.capacity() == 12);
    
    //clear, empty
    assert(!num_vect.empty());
    num_vect.clear();
    assert(num_vect.empty());
    //-------------------------------------------------int end------------------------------------------


    //-------------------------------------------------char* start------------------------------------------
    /**
    *char* ，用来测试是否支持深拷贝
    *char* 类型无 char*()式的初始化方式，所以无法使用第二种构造函数中的默认参数
    */
    char s1[6]  = "hello";
    char s2[5]  = "test";
    char s3[11] = "helloworld";
    char s4[] = "oneworld";

    //ctor
    qh::vector<char *> char_vec;
    qh::vector<char *> char_vec1(3,s1);
    qh::vector<char *> char_vec2 = char_vec1;
    qh::vector<char *> char_vec3;
    char_vec3 = char_vec;
    
    //size() , capacity()
    assert(char_vec.size() == 0 && char_vec.capacity() == 1);
    assert(char_vec1.size() == 3 && char_vec1.capacity() == 3);
    assert(char_vec2.size() == 3 && char_vec2.capacity() == 3);
    assert(char_vec3.size() == 0 && char_vec3.capacity() == 1);
    
    //push_back, pop_back
    char_vec.push_back(s2);
    char_vec.push_back(s3);
    assert(char_vec.size() == 2 && char_vec.capacity() == 2);
    char_vec.push_back(s4);
    assert(char_vec.size() == 3 && char_vec.capacity() == 4);
    char_vec.pop_back();
    assert(char_vec.size() == 2 && char_vec.capacity() == 4);

    //重载[]
    assert(strcmp(char_vec[0],s2) == 0);
    char_vec[0] = s3;
    assert(strcmp(char_vec[0],s3) == 0);

    //resize
    char_vec.resize(1);
    assert(char_vec.size() == 1 && char_vec.capacity() == 4);
    char_vec.resize(10);
    assert(char_vec.size() == 10 && char_vec.capacity() == 10);

    //reserve
    char_vec.reserve(2);
    assert(char_vec.size() == 10 && char_vec.capacity() == 10);
    char_vec.reserve(12);
    assert(char_vec.size() == 10 && char_vec.capacity() == 12);

    //clear, empty
    assert(!char_vec.empty());
    char_vec.clear();
    assert(char_vec.empty());
    //-------------------------------------------------char* end------------------------------------------

    //-------------------------------------------------string start----------------------------------------
    //string类型（对象），拥有自定义的析构函数，即non-trivial destructor
    using std::string;

    string str1 = "hello";
    string str2 = "world";
    string str3 = "vector";

    //ctor
    qh::vector<string> str_vec;
    qh::vector<string> str_vec1(3);
    qh::vector<string> str_vec2(4,str1);
    qh::vector<string> str_vec3(str_vec2);
    qh::vector<string> str_vec4;
    str_vec4 = str_vec;

    //size, capacity
    assert(str_vec.size() == 0 && str_vec.capacity() == 1);
    assert(str_vec1.size() == 3 && str_vec1.capacity() == 3);
    assert(str_vec2.size() == 4 && str_vec2.capacity() == 4);
    assert(str_vec3.size() == 4 && str_vec3.capacity() == 4);
    assert(str_vec4.size() == 0 && str_vec4.capacity() == 1);

    //push_back, pop_back
    str_vec.push_back(str3);
    str_vec.push_back(str3);
    str_vec.push_back(str3);
    
    assert(str_vec.size() == 3 && str_vec.capacity() == 4);
    str_vec.pop_back();
    assert(str_vec.size() == 2 && str_vec.capacity() == 4);

    //重载[]
    assert(str_vec[0].compare(str3) == 0);
    str_vec[0] = str1;
    assert(str_vec[0].compare(str1) == 0);

    assert(str_vec1[0].compare("") == 0);
    assert(str_vec2[0].compare(str1) == 0);

    //resize 一定会改变size，在需要扩容时改变capacity;
    str_vec3.resize(1);
    assert(str_vec3.size() == 1 && str_vec3.capacity() == 4);
    str_vec3.resize(5);
    assert(str_vec3.size() == 5 && str_vec3.capacity() == 5);

    //reserve不改变size，只在扩容时改变capacity
    str_vec3.reserve(1);
    assert(str_vec3.size() == 5 && str_vec3.capacity() == 5);
    str_vec3.reserve(10);
    assert(str_vec3.size() == 5 && str_vec3.capacity() == 10);

    //clear, empty
    assert(!str_vec.empty());
    str_vec.clear();
    assert(str_vec.empty());
    //-------------------------------------------------string end------------------------------------------

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

