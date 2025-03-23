
#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;
// 测试链接 : https://leetcode.cn/problems/lru-cache/
struct DoubleNode
{
    int key;
    int value;
    DoubleNode *next;
    DoubleNode *pre;
    DoubleNode(int k, int v) : key(k), value(v) {};
};

map<int, DoubleNode *> doublemap;
int capacity = 0;
DoubleNode *head, *tail;
int cut = 0;

void toEnd(DoubleNode *item)
{
    if (item == tail)
    {
        return;
    }
    if (item == head)
    {
        // 重新调整开始
        head = item->next;
        head->pre = nullptr;
        // 移动到尾部
        item->pre = tail;
        item->next = nullptr;
        tail->next = item;
        tail = item;
        return;
    }
    // 断开item
    item->pre->next = item->next;
    item->next->pre = item->pre;
    // 连接到尾部
    item->pre = tail;
    item->next = nullptr;
    tail->next = item;
    tail = item;
}

void addEnd(DoubleNode *item)
{
    if (head == nullptr)
    {
        head = item;
        tail = item;
        return;
    }
    tail->next = item;
    item->pre = tail;
    tail = item;
}
DoubleNode *removeStart()
{
    if (head == nullptr)
        return nullptr;
    DoubleNode *ans = head;
    if (head == tail)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        head = ans->next;
        ans->next = nullptr;
        head->pre = nullptr;
    }
    return ans;
}

int get(int key)
{
    if (doublemap.count(key))
    {
        toEnd(doublemap[key]);
        return doublemap[key]->value;
    }
    else
    {
        return -1;
    }
}
void put(int key, int value)
{
    if (doublemap.count(key))
    {
        doublemap[key]->value = value;
        toEnd(doublemap[key]);
    }
    else
    {
        DoubleNode *doublek = new DoubleNode(key, value);
        if (cut >= capacity)
        {
            DoubleNode * s= removeStart();
            doublemap.erase(s->key);
            doublemap[key]=doublek;
            addEnd(doublek);
        }
        else
        {
            if (cut == 0)
            {
                head = doublek;
                tail = doublek;
            }
            doublemap[key]=doublek;
            addEnd(doublek);
            cut++;
        }
    }
}

int main()
{
    capacity = 2;
    put(1, 1);
    put(2, 2);
    cout << get(1) << endl;
    put(3, 3);
    cout << get(2) << endl;
    put(4, 4);
    cout << get(1) << endl;
    cout << get(3) << endl;
    cout << get(4) << endl;
}