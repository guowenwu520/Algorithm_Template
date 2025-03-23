// 位运算实现加减乘除，过程中不能出现任何算术运算符

// 加法：利用每一步无进位相加的结果 + 进位的结果不停计算，直到进位消失
// 减法：利用加法，和一个数字x相反数就是(~x)+1
// 乘法：回想小学时候怎么学的乘法，除此之外没别的了
// 除法：为了防止溢出，让被除数右移，而不是除数左移。从高位尝试到低位
#include <iostream>
#include <algorithm>
using namespace std;
int MIN = INT32_MIN;
class Solution
{
private:
    /* data */
public:
    Solution();
    int add(int a, int b);
    int minus(int a, int b);
    int neg(int b);
    int multiply(int a, int b);
int divide(int a, int b);
    int div(int a, int b);
    ~Solution();
};

Solution::Solution()
{
}
int Solution::divide(int a, int b)
{
    if (a == MIN && b == MIN)
    {
        // a和b都是整数最小
        return 1;
    }
    if (a != MIN && b != MIN)
    {
        // a和b都不是整数最小，那么正常去除
        return div(a, b);
    }
    if (b == MIN)
    {
        // a不是整数最小，b是整数最小
        return 0;
    }
    // a是整数最小，b是-1，返回整数最大，因为题目里明确这么说了
    if (b == neg(1))
    {
        return Integer.MAX_VALUE;
    }
    // a是整数最小，b不是整数最小，b也不是-1
    a = add(a, b > 0 ? b : neg(b));
    int ans = div(a, b);
    int offset = b > 0 ? neg(1) : 1;
    return add(ans, offset);
}
int Solution::add(int a, int b)
{
    int ans = a;
    while (b != 0) // 这里是表示没有进位信息，所以一定是等于0结束，小于零也有进位信息的
    {
        ans = a ^ b;      // 无进位相加
        b = (a & b) << 1; // 进位信息
        a = ans;
    }
    return ans;
}

int Solution::minus(int a, int b)
{
    return add(a, neg(b)); // a-b等于a+(-b);
}
int Solution::neg(int b)
{
    return add(~b, 1); // b取反在加一就等于-b
}
// 必须保证a和b都不是整数最小值，返回a除以b的结果,280=25*2^3+25*2^1+25*2^0;
int Solution::div(int a, int b)
{
    int x = a < 0 ? neg(a) : a;
    int y = b < 0 ? neg(b) : b;
    int ans = 0;
    for (int i = 30; i >= 0; i = minus(i, 1))
    {
        if ((x >> i) >= y) // y*2的多少次方是在x里面的,就把这个次方指数相加,y左移的话会溢出，x移动没有风险
        {
            ans |= (1 << i);      // 包含设置成1
            x = minus(x, y << i); // 这里就是x减掉最大的x的2的i次方，
        }
    }
    return a < 0 ^ b < 0 ? neg(ans) : ans;
}

// 和小学乘法一样这里只是二进制
int Solution::multiply(int a, int b)
{
    int m = a > 0 ? a : neg(a); // 处理一下负数的情况
    int n = b > 0 ? b : neg(b);
    int ans = 0;
    while (m != 0)
    {
        if ((m & 1) != 0)
        {
            ans = add(n, ans); // 累加n，想到与n在上面下面用m去乘，有1的地方就需要加上一个n的进位
        }
        n <<= 1; // n不断扩大
        m >>= 1; // m不断被使用
    }
    return (a > 0 ^ b > 0) ? neg(ans) : ans;
}
Solution::~Solution()
{
}

int main()
{
    Solution *solution = new Solution();
    cout << solution->add(100, 232) << endl;
    cout << solution->minus(109, 22) << endl;
    cout << solution->multiply(-124, 232) << endl;
    cout << solution->div(124, 2) << endl;
}
