#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;
// 子集
// https://leetcode.cn/problems/subsets/
void dfs(vector<int> &nums, int index, int size, vector<int> &cur, vector<vector<int>> &ret)
{

    if (index > size)
    {
        return;
    }
    ret.push_back(cur);
    for (int i = index; i < size; i++)
    {
        cur.push_back(nums[i]);
        dfs(nums, i + 1, size, cur, ret);
        cur.pop_back();
    }
}

void dfs_up(vector<int> &nums, int index, int size, vector<int> &cur, vector<vector<int>> &ret)
{

    if (index == size)
    {
        ret.push_back(cur);
        return;
    }
    // 要这个值
    cur.push_back(nums[index]);
    dfs(nums, index + 1, size, cur, ret);
    // 不要这个值
    cur.pop_back();
    dfs(nums, index + 1, size, cur, ret);
}
// 有这种覆盖思路，但是在这里面还是直接抹掉方便
void dfs(vector<int> &nums, int index, int size, int *cur, int cur_size, vector<vector<int>> &ret)
{
    if (index > size)
    {
        return;
    }
    vector<int> cur2;
    for (int i = 0; i < cur_size; i++)
    {
        cur2.push_back(cur[i]);
    }
    ret.push_back(cur2);
    for (int i = index; i < size; i++)
    {
        cur[cur_size++] = nums[i];
        dfs(nums, i + 1, size, cur, cur_size, ret);
        cur_size--;
    }
}

vector<vector<int>> subsets(vector<int> &nums)
{
    vector<int> cur;
    vector<vector<int>> ant;
    dfs(nums, 0, nums.size(), cur, ant);
    int cur2[3000];
    dfs(nums, 0, nums.size(), cur2, 0, ant);
    return ant;
}

// 子集2
// https://leetcode.cn/problems/subsets-ii/
// 把相同数字作为一个组，在组类做选择,剪枝了，组合到一起
void dfs_up(vector<int> &nums, int index, int size, int *cur, int cur_size, vector<vector<int>> &ret)
{

    if (index == size)
    {
        vector<int> cur2;
        for (int i = 0; i < cur_size; i++)
        {
            cur2.push_back(cur[i]);
        }
        ret.push_back(cur2);
        return;
    }
    else
    {
        int j = index + 1; // 下一组的第一个数位置
        while (j < size && nums[index] == nums[j])
            j++;
        // 要0个
        dfs_up(nums, j, size, cur, cur_size, ret);
        // 要1,2,3...个
        for (; index < j; index++)
        {
            cur[cur_size++] = nums[index];
            dfs_up(nums, j, size, cur, cur_size, ret);
        }
    }
}
// 全排列
// https://leetcode.cn/problems/permutations/description/

void q_bfs(vector<int> &nums, int i, int size, vector<vector<int>> &ant)
{
    if (i == size)
    {
        ant.push_back(nums);
        return;
    }
    // 轮流来到i位置
    set<int> mak;
    for (int j = i; j < size; j++)
    {
        // 如果有重复数字来的，就不要
        if (mak.count(nums[j]))
            continue;
        mak.insert(nums[j]);
        swap(nums[i], nums[j]);
        q_bfs(nums, i + 1, size, ant);
        swap(nums[i], nums[j]);
    }
}
vector<vector<int>> permute(vector<int> &nums)
{
    vector<vector<int>> ant;
    q_bfs(nums, 0, nums.size(), ant);
    return ant;
}

vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    int cur[300];
    vector<vector<int>> ant;
    sort(nums.begin(), nums.end());
    dfs_up(nums, 0, nums.size(), cur, 0, ant);
    return ant;
}
// 汉罗塔
// https://leetcode.cn/problems/hanota-lcci/description/
// 一个开始，一个目标，一个用于中转
void f(int i, vector<int> &from, vector<int> &to, vector<int> &other)
{
    if (i == 1)
    {
        to=from;//只有最后一个就直接移动到目标位置
    }
    else
    {
        to.assign(from.begin() + 1, from.end());//多于一个，就从这推里面把上面的全部移动到目标，留最后一个
        f(i - 1, from, other, to);//先把目标上面的除了最底层，全部移动到空余的other
        f(i - 1, other, to, from);//最后在移动到目标
    }
}
void hanota(vector<int> &A, vector<int> &B, vector<int> &C)
{
   f(A.size(),A,C,B);
}
int main()
{
    return 0;
}