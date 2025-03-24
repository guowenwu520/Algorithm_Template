#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
//  https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/
// 最大异或值
const int MAXN = 100;
int cnt;
int tree[MAXN][2];
// 数字只需要从哪一位开始考虑
int left_;
int maxXor(int num)
{
    int ans = 0;
    int cur = 1;
    for (int i = left_; i >= 0; i--)
    {
        int status = (num >> i) & 1;
        int want = status ^ 1;
        // 没有想要的结果，能让他变为1的值
        if (tree[cur][want] == 0)
            want ^= 1;
        // 设置值
        ans |= (status ^ want) << i;
        cur = tree[cur][want];
    }
    return ans;
}
void insert(int num)
{
    int cur = 1;
    for (int i = left_; i >= 0; i--)
    {
        int path = (num >> i) & 1;
        if (tree[cur][path] == 0)
        {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
    }
}
void build(vector<int> &nums)
{
    cnt = 1;
    int max_v = INT32_MIN;
    for (int num : nums)
    {
        max_v = max(num, max_v);
    }
    //    计算最大值的二进制状态，有多少个前缀0
    //    可以忽略这些前缀0
    for (int i = 31; i >= 0; i--)
    {
        if ((max_v >> i) & 1)
        {
            left_ = i;
            break;
        }
    }
    for (int num : nums)
    {
        insert(num);
    }
}
void clear()
{
    for (int i = 0; i < cnt; i++)
    {
        tree[i][0] = 0;
        tree[i][1] = 0;
    }
}
int findMaximumXOR(vector<int> &nums)
{
    build(nums);
    int ans = 0;
    for (int num : nums)
    {
        ans = max(ans, maxXor(num));
    }
    clear();
    return ans;
}

// 搜索单词
// https://leetcode.cn/problems/word-search-ii/
// 可以使用前缀树优化
int step[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
int used[13][13] = {};
bool dfs(int x, int y, int index, string str, vector<vector<char>> &board)
{
    if (index >= str.size())
        return true;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + step[i][0];
        int ny = y + step[i][1];
        if (nx < 0 || ny < 0 || nx >= board.size() || ny >= board[0].size())
            continue;
        if (used[nx][ny])
            continue;
        if (str[index] == board[nx][ny])
        {
            used[nx][ny] = 1;
            if (dfs(nx, ny, index + 1, str, board))
                return true;
            used[nx][ny] = 0;
        }
    }
    return false;
}
bool check(string str, vector<vector<char>> &board)
{
    memset(used, 0, sizeof(used));
    int m = board.size();
    int n = board[0].size();
    int sx, sy;
    bool isE = false;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (str[0] == board[i][j])
            {
                used[i][j] = 1;
                isE = dfs(i, j, 1, str, board);
                used[i][j] = 0;
                if (isE)
                    break;
            }
        }
        if (isE)
            break;
    }
    return isE;
}
vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
{
    vector<string> ans;
    for (int i = 0; i < words.size(); i++)
    {
        if (check(words[i], board))
            ans.push_back(words[i]);
    }
    return ans;
}
int main()
{
    return 0;
}