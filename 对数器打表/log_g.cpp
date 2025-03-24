#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;
// 先计算部分数据找规律，然后把规律写成代码
// 一秒，大概在10^7到10^8次方左右，根据数量选择算法
// 问题规模和可用算法
//                  logn      n      n*logn      n*根号n      n^2      2^n      n!

// n <= 11          Yes      Yes      Yes         Yes        Yes      Yes      Yes
// n <= 25          Yes      Yes      Yes         Yes        Yes      Yes      No
// n <= 5000        Yes      Yes      Yes         Yes        Yes      No       No
// n <= 10^5        Yes      Yes      Yes         Yes        No       No       No
// n <= 10^6        Yes      Yes      Yes         No         No       No       No
// n <= 10^7        Yes      Yes      No          No         No       No       No
// n >= 10^8        Yes      No       No          No         No       No       No

// 上面每个复杂度，课上都讲过类似的过程了。
// 除了 n*根号n，这个复杂度常出现在“莫队算法”能解决的相关题目里，后续的【挺难】课程会有系统讲述
// 这张表其实作用有限
// 因为时间复杂度的估计很多时候并不是一个入参决定，可能是多个入参共同决定。比如O(n*m), O(n+m)等
// 所以最关键的就是记住常数指令操作量是 10^7 ~ 10^8，然后方法是什么复杂度就可以估计能否通过了

// 现在有一个打怪类型的游戏，这个游戏是这样的，你有n个技能
// 每一个技能会有一个伤害，
// 同时若怪物小于等于一定的血量，则该技能可能造成双倍伤害
// 每一个技能最多只能释放一次，已知怪物有m点血量
// 现在想问你最少用几个技能能消灭掉他(血量小于等于0)
// 技能的数量是n，怪物的血量是m
// i号技能的伤害是x[i]，i号技能触发双倍伤害的血量最小值是y[i]
// 1 <= n <= 10
// 1 <= m、x[i]、y[i] <= 10^6
int kill[100], blood[100];
int f(int i, int n, int total)
{
    if (total < 0)
    {
        return i;
    }
    if (i == n)
    {
        return INT32_MAX;
    }
    int ant = INT32_MAX;
    for (int j = i; j < n; j++)
    {
        swap(kill[i], kill[j]);
        swap(blood[i], blood[j]);
        ant = min(ant, f(i + 1, n, total - (total < blood[i] ? kill[i] * 2 : kill[i])));
        swap(kill[i], kill[j]);
        swap(blood[i], blood[j]);
    }
    return ant;
}
void kill_m()
{
    int n = 0, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> kill[i] >> blood[i];
    }
    int ant = f(0, n, m);
    cout << ((ant == INT32_MAX) ? -1 : ant) << endl;
}
// 超级回文数
// https://leetcode.cn/problems/super-palindromes/
// 先枚举数据前一半结构->数据在平方(更快的方法把这个范围的所有超级回文都记录到数组里面，最后遍历一下数组就行)
//  10^5 ->10^10 ->10^20
// 更具半边捏造另外一边
long  jisun(long v, int flag)
{
    string str = to_string(v);
    string fa = str;
    reverse(fa.begin(),fa.end());
    if (flag)
    {
        str = str + fa;
    }
    else
    {
        str = str + fa.substr(1);
    }
    return stol(str);
}
// 检测回文
bool checkout_h(long v)
{
    string str = to_string(v);
    string fa = str;
    reverse(fa.begin(),fa.end());
    return str == fa;
}
int superpalindromesInRange(string left, string right)
{
    long long left_v = stol(left);
    long long right_v = stol(right);
    int count = 0;
    long long start_v = 1;
    while (true)
    {
        // 合成奇数位数字
        long cur_left_v = jisun(start_v, 0);
        if (cur_left_v > sqrt(right_v))
            break;
        if (cur_left_v >= sqrt(left_v) && checkout_h(cur_left_v*cur_left_v))
        {
            count++;
        }
        // 合成偶数位数字
        cur_left_v = jisun(start_v, 1);
        if (cur_left_v > sqrt(right_v) || sqrt(left_v) > cur_left_v)
        {
            start_v++;
            continue;
        }
        if (checkout_h(cur_left_v*cur_left_v))
        {
            count++;
        }
        start_v++;
    }
    return count;
}

int main()
{
    // kill_m();
    cout << superpalindromesInRange("0", "999999999999999999") << endl;
    return 0;
}