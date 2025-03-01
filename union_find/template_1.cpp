
#include <iostream>
#include <vector>
using namespace std;

const int N = 100;
class Solution
{
    int set = 0;
    int a[N];

public:
    // 初始化并查集
    void build(int n)
    {
        for (int i = 0; i < n; i++)
        {
            a[i] = i;
            set++;
        }
    }
    // 找父节点,带压缩的递归写法
    int find(int i)
    {
        if (a[i] != i)
        {
            a[i] = find(a[i]);
        }
        return a[i];
    }
    // 合并
    void union_m(int x, int y)
    {
        int fa = find(x);
        int fb = find(y);
        if (fa != fb)
        {
            set--;
            a[fa] = fb;
        }
    }
    int enter_main(vector<int> &row)
    {
        int n = row.size();
        build(n);
        // 满足某种条件就合并
        union_m(8, 9);
        union_m(8, 2);
        return n - set;
    }
};

int main()
{
    Solution *solution = new Solution();
    vector<int> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(7);
    data.push_back(8);
    data.push_back(9);
    int value = solution->enter_main(data);
    cout << value << endl;
}
//练习题
//    情侣牵手： https://leetcode.cn/problems/couples-holding-hands/
//    相似字符串组：https://leetcode.cn/problems/similar-string-groups/
//    岛屿数量: https://leetcode.cn/problems/number-of-islands/
//    移除最多的同行或同列石头:https://leetcode.cn/problems/most-stones-removed-with-same-row-or-column/
//    找出知晓秘密的所有专家: https://leetcode.cn/problems/find-all-people-with-secret/
//    好路径的数目: https://leetcode.cn/problems/number-of-good-paths/
//    尽量减少恶意软件的传播 II :https://leetcode.cn/problems/minimize-malware-spread-ii/
