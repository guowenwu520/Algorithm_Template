#include <iostream>
#include <algorithm>
using namespace std;
// 最大公约数
long gcd(long a, long b)
{
    return b == 0 ? a : gcd(b, a % b);
}
// 最小公倍数,a/最大公约数*b
long lcm(long a, long b)
{
    return a / gcd(a, b) * b;
}

// 神奇的数字
// https://leetcode.cn/problems/nth-magical-number/description/
// 可以确定范围（1，n*min(a,b)）
int nthMagicalNumber(int n, int a, int b)
{
    long lc = lcm(a, b);
    long right = n * min(a, b);
    long left = 1;
    long ans = 0;
    while (left <= right)
    {
        long mind = left + (right - left) / 2;
         // 计算1-mind所有可以被a,b同时整除的数，就等于能被a整除的数加上能被b整除的数减掉同时可被整除的
        int cur = mind / a + mind / b - mind / lc;
        if (cur >= n)
        {
            ans = mind;
            right = mind - 1;
        }
        else
        {
            left = mind + 1;
        }
    }
    return ans%1000000007;
}
// 同余原理，当一个数太大的时候就会用到求余
// 加法取模原理 ，a%m+...+b%m=(a+b)%m
// 乘法取模原理 ，a%m*...*b%m=(a*b)%m
// 减法取模原理， (a%m-...-b%m+m)%m=(a-b)%m
int main()
{
    cout << nthMagicalNumber(3, 6, 4) << endl;
    return 0;
}