#include <iostream>
#include <map>
#include <vector>
using namespace std;
// 前缀和＋前缀和map最早出现的位置,找数字中最长的k个数和为aim的序列
// 和为k的数组
// https://leetcode.cn/problems/subarray-sum-equals-k/description/

int subarraySum(vector<int> &nums, int k)
{
    map<long, int> index_map; // 统计这个前缀和出现了多少次
    long sum = 0;
    index_map[0] = 1; // 没人任何数字的时候
    int count = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        sum += nums[i];
        // 包含需要的前缀和
        if (index_map.count(sum - k))
        {
            // 加上这个前缀和的数量
            count += index_map[sum - k];
        }
        index_map[sum]++;
    }
    return count;
}
// 996
// https://leetcode.cn/problems/longest-well-performing-interval/description/
int longestWPI(vector<int> &hours)
{
    map<int, int> map_i;
    map_i[0] = -1;
    int sum = 0;
    int ans = 0;
    for (int i = 0; i < hours.size(); i++)
    {
        // 将时间转化到1,-1,就转化成求累加和严格大于0的最长子数组
        sum += hours[i] > 8 ? 1 : -1;
        if (sum > 0)
        {
            // 如果大于0，这一段一定是最长的
            ans = i + 1;
        }
        else
        {
            // 如果是负的，但是可以找到更小的一个，因为所有值都是-1，1累积出来的，所以小一个一定是距离最远的
            if (map_i.count(sum - 1))
                // 统计答案
                ans = max(ans, i - map_i[sum - 1]);
        }
        // 如果不包含才加入，因为要求最长，如果使用后面的值覆盖了，求出来就不是最长的了，最早位置
        if (!map_i.count(sum))
            map_i[sum] = i;
    }
    return ans;
}

// 取模
// https://leetcode.cn/problems/make-sum-divisible-by-p/description/
int minSubarray(vector<int> &nums, int p)
{
    int target = 0, ans = nums.size(), sum = 0, res;
    for (int &num : nums)
        target = (target + num) % p;
    if (target == 0)
        return 0;
    map<int, int> pos;
    pos[0] = -1;
    for (int i = 0; i < nums.size(); ++i)
    {
        sum = (sum + nums[i]) % p;
        res = (sum - target + p) % p;
        pos[sum] = i;
        ans = min(ans, pos.find(res) == pos.end() ? INT_MAX : i - pos[res]);
    }
    return ans == nums.size() ? -1 : ans;
}
}
;
int main()
{
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(1);
    int k = 2;
    subarraySum(nums, k);
}