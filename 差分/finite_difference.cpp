#include <iostream>
#include<algorithm>
#include <vector>
using namespace std;
// 一维差分
// https://leetcode.cn/problems/corporate-flight-bookings/
// 常规老老实实遍历加，利用差分只需要在当前位和结束位＋1减掉，最后的做一个前缀和就是结果
vector<int> corpFlightBookings(vector<vector<int>> &bookings, int n)
{
    int mun[200001] = {};
    vector<int> ans;
    for (int i = 0; i < bookings.size(); i++)
    {
        mun[bookings[i][0]] += bookings[i][2];
        mun[bookings[i][1] + 1] -= bookings[i][2];
    }
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += mun[i];
        ans.push_back(sum);
    }
    return ans;
}
// 等差数列差分
// l - r s开始 e结束 d等差
// arr[l]+=s;
// arr[l+1]+=d-s;
// arr[r+1]-=d+e;
// arr[r+2]+=e;
// 在经历两遍前缀和就能复原

// 二维前缀和
// 在二维数组中计算下标（a,b）->（c,d）的值
// 提前维护一个前缀和，当前值等于=(上＋前－上前+自己),没有上就前，没有前就上，都没有就是他自己，
// sum[i][j]：代表左上角（0，0）到右下角（i，j）这个范围的累加和
// sum[i][j]+=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];
// 查询a,b）->（c,d）的累加和
// sum[c][d]-sum[c][b-1]-sum[a-1][d]+sum[a-1][b-1];

// 二维差分
// https://leetcode.cn/problems/stamping-the-grid/

bool possibleToStamp(vector<vector<int>> &grid, int stampHeight, int stampWidth)
{
    int m = grid.size(), n = grid[0].size();

    // 1. 计算前缀和，便于快速判断某个区域内是否全为 0
    vector<vector<int>> preSum(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            preSum[i + 1][j + 1] = grid[i][j] + preSum[i][j + 1] + preSum[i + 1][j] - preSum[i][j];

    // 2. 记录可以盖章的位置，用二维差分数组
    vector<vector<int>> diff(m + 2, vector<int>(n + 2, 0)); // 多加1行1列，便于差分操作
    for (int i = 0; i <= m - stampHeight; ++i)
    {
        for (int j = 0; j <= n - stampWidth; ++j)
        {
            // 当前矩形区域内是否全为 0
            int x1 = i, y1 = j, x2 = i + stampHeight, y2 = j + stampWidth;
            int total = preSum[x2][y2] - preSum[x1][y2] - preSum[x2][y1] + preSum[x1][y1];
            if (total == 0)
            {
                // 差分标记：盖章影响的是矩形 (i,j)~(i+H-1,j+W-1)
                diff[i + 1][j + 1] += 1;
                diff[i + 1][j + stampWidth + 1] -= 1;
                diff[i + stampHeight + 1][j + 1] -= 1;
                diff[i + stampHeight + 1][j + stampWidth + 1] += 1;
            }
        }
    }

    // 3. 还原差分数组成覆盖次数的矩阵
    vector<vector<int>> cover(m + 2, vector<int>(n + 2, 0));
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            cover[i][j] = cover[i - 1][j] + cover[i][j - 1] - cover[i - 1][j - 1] + diff[i][j];

    // 4. 检查所有为 0 的位置是否被覆盖到
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (grid[i][j] == 0 && cover[i + 1][j + 1] == 0)
                return false;

    return true;
}

// 离散化技巧
// 由于可能有小数需要放大处理，另外差分数组的时候可能数字太大不能直接建立一个那么大的数组，因此可以对大小排序之后重新编号处理
// https://leetcode.cn/problems/xepqZ5/

// 对原数组排序，之后去掉重复的元素，返回去重之后数组的大小位置

void add(vector<vector<int>> &diff, int a, int b, int c, int d)
{
    diff[a][b] += 1;
    diff[c + 1][d + 1] += 1;
    diff[c + 1][b] -= 1;
    diff[a][d + 1] -= 1;
}
// 查找v所在的位置
int rank_(vector<long> &nums, long v, int size)
{
    int l = 0;
    int r = size - 1;
    int m, ans = 0;
    // 使用二分查找当前值所在的位置
    while (l <= r)
    {
        m = (l + r) / 2;
        if (nums[m] >= v)
        {
            ans = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }
    return ans + 1;
}
int f_sort(vector<long> &a)
{
    sort(a.begin(), a.end());
    int size = 1;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != a[size - 1])
            a[size++] = a[i];
    }
    return size;
}
int fieldOfGreatestBlessing(vector<vector<int>> &forceField)
{
    int length = forceField.size();
    vector<long> xs(length << 1);
    vector<long> ys(length << 1);
    // 统一映射到数组
    for (int i = 0, k = 0, p = 0; i < length; i++)
    {
        long x = forceField[i][0];
        long y = forceField[i][1];
        long r = forceField[i][2];
        xs[k++] = (x << 1) - r;
        xs[k++] = (x << 1) + r;
        ys[p++] = (y << 1) - r;
        ys[p++] = (y << 1) + r;
    }
    int x_size = f_sort(xs);
    int y_size = f_sort(ys);
    vector<vector<int>> diff(x_size + 2, vector<int>(y_size + 2, 0));
    for (int i = 0, a, b, c, d; i < length; i++)
    {
        long x = forceField[i][0];
        long y = forceField[i][1];
        long r = forceField[i][2];
        a = rank_(xs, (x << 1) - r, x_size);
        b = rank_(ys, (y << 1) - r, y_size);
        c = rank_(xs, (x << 1) + r, x_size);
        d = rank_(ys, (y << 1) + r, y_size);
        add(diff, a, b, c, d);
    }
    int ans = 0;
    // 恢复差分
    for (int i = 1; i < diff.size(); i++)
    {
        for (int j = 1; j < diff[0].size(); j++)
        {
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            ans = max(ans, diff[i][j]);
        }
    }
    return ans;
}

int main()
{
    vector<vector<int>> grid;
    grid.push_back({0, 0, 1});
    grid.push_back({1, 0, 1});
    cout << fieldOfGreatestBlessing(grid) << endl;
    return 0;
}