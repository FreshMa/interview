#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <set>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#define H_ARRAYSIZE(a)            \
    ((sizeof(a) / sizeof(*(a))) / \
     static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

struct Node
{
    int xpos, height, isLeft;
    Node(int x, int h, int l) : xpos(x), height(h), isLeft(l) {}
    //要保证在相同的点上，左边(left edge)排在右边(right edge)前面，所以应该是isLeft>rNode.isLeft
    bool operator<(const Node &rNode) const
    {
        return xpos < rNode.xpos || xpos == rNode.xpos && isLeft > rNode.isLeft;
    }
};

int resolve(const char *input)
{
    string s = input;
    istringstream iss(s);
    string line;
    vector<Node> nodevec;

    //建立一个有序的集合来维护当前扫描的线段
    multiset<int, greater<int>> heap;
    int result = 0;
    int maxEnd = 0; 

    //将三元组存到临时vector中，并以此构造Node对象
    while (getline(iss, line, '\n'))
    {
        //找到包含三元组的行，根据逗号进行分割
        if (line.length() > 1)
        {
            vector<int> tmp;
            string num;
            istringstream inss(line);
            while (getline(inss, num, ','))
            {
                tmp.push_back(atoi(num.c_str()));
            }
            maxEnd = max(maxEnd, tmp[1]);
            nodevec.push_back(Node(tmp[0], tmp[2], 1));
            nodevec.push_back(Node(tmp[1], tmp[2], 0));
        }
    }

    //横坐标上的路程即为山的最大终点坐标
    result += maxEnd;

    //扫描线算法计算纵坐标上的路程
    sort(nodevec.begin(), nodevec.end());
    for (int i = 0; i < nodevec.size(); ++i)
    {
        if (nodevec[i].isLeft == 1)
        {
            int tmp = nodevec[i].height;
            if (heap.empty())
            {
                result += tmp;
            }
            else if (tmp > *heap.begin())
            {
                result += tmp - *heap.begin();
            }
            heap.insert(nodevec[i].height);
        }
        else
        {
            int tmp = *heap.begin();
            heap.erase(heap.find(nodevec[i].height));
            if (heap.empty())
            {
                result += tmp;
            }
            
            else if (nodevec[i].height == tmp && !heap.empty())
            {
                result += tmp - *heap.begin();
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
        "6\n0,2,3\n1,2,3\n3,6,2\n2,8,4\n7,10,5\n10,11,2",
        "0\n",
        "3\n10,11,3\n12,15,4\n16,17,1",
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}
