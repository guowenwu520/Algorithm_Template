
// 快慢指针技巧，一个指针走一步一个走两步，就能找到中点
// 检测环入口，使用快慢指针第一次相遇之后将一个指针返回开头，一个指针保留在原地，之后同时一步一步移动，下一次相遇的时候一定是环的入口，如果访问到空指针，说明是无环的
#include <iostream>
using namespace std;
struct NodeList
{
    int val;
    NodeList() : val(0) {};
    NodeList(int val) : val(val) {};
    NodeList *next = nullptr;
};

NodeList *build(int *a, int num)
{
    NodeList *head = new NodeList();
    head->val = a[0];
    NodeList *p = new NodeList();
    p = head;
    for (int i = 1; i < num; i++)
    {
        NodeList *p2 = new NodeList();
        p2->val = a[i];
        p->next = p2;
        p = p2;
    }
    return head;
}

void show(NodeList *head)
{
    NodeList *p = head;
    while (p != nullptr)
    {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}

NodeList *reverse_list(NodeList *head)
{
    NodeList *p = nullptr;
    NodeList *next = nullptr;
    while (head != nullptr)
    {
        next = head->next; // 保留后面的节点防止丢失
        head->next = p;    // 从原链表断开，指向现有链表
        p = head;          // 移动到头部来
        head = next;       // 继续向下
    }
    return p;
}
// 合并有序链表
NodeList *NomergeTwoLists(NodeList *list1, NodeList *list2)
{
    NodeList *head;
    if (list1 == nullptr && list2 == nullptr)
    {
        return nullptr;
    }
    if (list2 == nullptr)
        return list1;
    if (list1 == nullptr)
        return list2;
    head = (list1->val > list2->val) ? list2 : list1;
    NodeList *next1 = head->next;
    NodeList *next2 = (list1->val <= list2->val) ? list2 : list1;
    NodeList *p = head;
    while (next1 != nullptr && next2 != nullptr)
    {
        if (next1->val > next2->val)
        {
            p->next = next2;
            next2 = next2->next;
        }
        else
        {
            p->next = next1;
            next1 = next1->next;
        }
        p = p->next;
    }
    if (next1 != nullptr)
        p->next = next1;
    if (next2 != nullptr)
        p->next = next2;
    return head;
}

NodeList *addTwoNumbers(NodeList *l1, NodeList *l2)
{
    NodeList *ans = nullptr, *head = nullptr;
    if (l1 == nullptr && l2 == nullptr)
        return nullptr;
    if (l1 == nullptr)
        return l2;
    if (l2 == nullptr)
        return l1;
    int out_v = 0, cur = 0;
    int a = l1->val;
    int b = l2->val;
    cur = (a + b + out_v) % 10;
    out_v = (a + b + out_v) / 10;
    NodeList *p2 = new NodeList(cur);
    head = ans = p2;
    while (l1 != nullptr && l2 != nullptr)
    {
        int a = l1->val;
        int b = l2->val;
        cur = (a + b + out_v) % 10;
        out_v = (a + b + out_v) / 10;
        NodeList *p = new NodeList(cur);
        ans->next = p;
        ans = p;
        l1 = l1->next;
        l2 = l2->next;
    }
    while (l1 != nullptr)
    {
        int a = l1->val;
        cur = (a + out_v) % 10;
        out_v = (a + out_v) / 10;

        NodeList *p = new NodeList(cur);
        ans->next = p;
        ans = p;

        l1 = l1->next;
    }

    while (l2 != nullptr)
    {
        int a = l2->val;
        cur = (a + out_v) % 10;
        out_v = (a + out_v) / 10;

        NodeList *p = new NodeList(cur);
        ans->next = p;
        ans = p;

        l2 = l2->next;
    }
    if (out_v != 0)
    {
        NodeList *p = new NodeList(cur);
        ans->next = p;
        ans = p;
    }
    return head;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    NodeList *head = build(a, 10);
    show(head);
    show(reverse_list(head));
    int c[] = {1, 2, 3, 4, 5, 6};
    int d[] = {2, 5, 7, 1, 2, 5};
    NodeList *head2 = build(d, 6);
    NodeList *head3 = build(c, 6);
    show(addTwoNumbers(head3, head2));
}
// 练习题
// 返回两个无环链表相交的第一个节点
// 测试链接 : https://leetcode.cn/problems/intersection-of-two-linked-lists/
// 每k个节点一组翻转链表
// 测试链接：https://leetcode.cn/problems/reverse-nodes-in-k-group/
// 复制带随机指针的链表
// 测试链接 : https://leetcode.cn/problems/copy-list-with-random-pointer/
// 判断链表是否是回文结构
// 测试链接 : https://leetcode.cn/problems/palindrome-linked-list/
// 返回链表的第一个入环节点
// 测试链接 : https://leetcode.cn/problems/linked-list-cycle-ii/
// 排序链表
// 要求时间复杂度O(n*logn)，额外空间复杂度O(1)，还要求稳定性
// 数组排序做不到，链表排序可以
// 测试链接 : https://leetcode.cn/problems/sort-list/