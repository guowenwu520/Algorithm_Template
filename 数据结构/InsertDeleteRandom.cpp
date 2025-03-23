// 测试链接 : https://leetcode.cn/problems/insert-delete-getrandom-o1/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> ant;     // 满足随机返回的时候O(1)
map<int, int> map_m; // 满足查找的时候O(1)

bool insert(int val)
{
    if (map_m.count(val))
    {
        return false;
    }
    //    放入集合并使用map记录值和对应位置
    ant.push_back(val);
    map_m[val] = ant.size() - 1;
    return true;
}

bool remove(int val)
{
    if (!map_m.count(val))
    {
        return false;
    }
    if (ant.size() == 1)
    {
        map_m.clear();
        ant.clear();
    }
    else
    {
        int index = map_m[val];
        int endvalue=ant[ant.size()-1];
        map_m[endvalue]=index;
        ant[index]=endvalue;
        map_m.erase(val);
        ant.pop_back();
    }
    return true;
}

int getRandom()
{
    return ant[(rand() % ant.size())];
}

int main()
{
    insert(1);
    remove(2);
    insert(2);
    cout << getRandom() << endl;
    remove(1);
    insert(2);
    cout << getRandom() << endl;
}