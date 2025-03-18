// 测试链接 :
// https://leetcode.cn/problems/insert-delete-getrandom-o1-duplicates-allowed/
#include <map>
#include <set>
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;
class RandomizedCollection
{
public:
    std::map<int, std::set<int>> map;
    std::vector<int> arr;

    RandomizedCollection() {}

    bool insert(int val)
    {
        arr.push_back(val);//加入一个值
        map[val].insert(arr.size() - 1);//记录这个值和值所在下标，有可能多个下标
        return map[val].size() == 1;
    }

    bool remove(int val)
    {
        if (map.find(val) == map.end())//先查找是否有值
        {
            return false;
        }

        auto &valSet = map[val];//拿出这个值对应的所有下标
        int valAnyIndex = *valSet.begin();//随便取一个下标做为擦除对象
        int endValue = arr.back();//获取到数组的最后一个值，用于填空白

        if (val == endValue)//如果这个值就是最后一个值
        {
            valSet.erase(arr.size() - 1);//直接擦除最后一个下标
        }
        else
        {
            auto &endValueSet = map[endValue];//最后一个值有一些什么下标，插入空白的那个小标，到这个最后的值里面
            endValueSet.insert(valAnyIndex);
            arr[valAnyIndex] = endValue;//把值放到空白位置
            endValueSet.erase(arr.size() - 1);//擦除最后下标
            valSet.erase(valAnyIndex);//原来位置擦除下标
        }

        arr.pop_back();//删除最后一个元素
        if (valSet.empty())//如果valset空了，删除整个set
        {
            map.erase(val);
        }
        return true;
    }

    int getRandom()
    {
        return arr[std::rand() % arr.size()];
    }
};

int main()
{
    RandomizedCollection RandomizedCollection;
    RandomizedCollection.insert(0);
    RandomizedCollection.insert(1);
    RandomizedCollection.remove(0);
    RandomizedCollection.insert(2);
    RandomizedCollection.remove(1);
    cout << RandomizedCollection.getRandom() << endl;
    // insert(2);
    // cout << getRandom() << endl;
}