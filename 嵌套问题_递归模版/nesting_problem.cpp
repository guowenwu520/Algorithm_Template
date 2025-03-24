#include <vector>
#include <string>
#include <iostream>
using namespace std;

// 经典嵌套递归
// https://leetcode.cn/problems/basic-calculator-ii/description/
int where = 0;
void push(vector<int> &numbers, vector<char> &opt, int value, char c)
{
    if (!opt.empty())
    {
        char last_c = opt[opt.size() - 1];
        if (last_c == '*' || last_c == '/')
        {
            int last_v = numbers[numbers.size() - 1];
            if (last_c == '/')
                value = last_v / value;
            if (last_c == '*')
                value = last_v * value;
            numbers.pop_back();
            opt.pop_back();
        }
    }
    numbers.push_back(value);
    opt.push_back(c);
}
int compute(vector<int> &numbers, vector<char> &opt)
{
    if (numbers.size() < 1)
        return 0;
    int ant = numbers[0];
    for (int i = 1; i < numbers.size(); i++)
    {
        if (opt[i - 1] == '+')
        {
            ant += numbers[i];
        }
        else if (opt[i - 1] = '-')
        {
            ant -= numbers[i];
        }
    }
    return ant;
}
int f(string s, int i)
{
    vector<int> numbers;
    vector<char> ops;
    int cur = 0;
    // 统计到结尾或者右括号
    while (i < s.length() && s[i] != ')')
    {
        // 剔除空格
        if (s[i] == ' ')
        {
            i++;
            continue;
        }
        // 统计数字
        if (s[i] >= '0' && s[i] <= '9')
        {
            cur = cur * 10 + (s[i++] - '0');
        }
        // 如果不是左括号，就把值压入两个栈中
        else if (s[i] != '(')
        {
            push(numbers, ops, cur, s[i++]);
            cur = 0;
        }
        else
        {
            // 遇到括号，就开一个递归从新开始计算，计算好了返回给我，而我下次继续开始计算的位置就是你结束的位置加1用where记录你的位置
            cur = f(s, i + 1);
            i = where + 1;
        }
    }
    // 最后一个入栈，做收尾
    push(numbers, ops, cur, '+');
    // 记录我走到哪里了
    where = i;
    // 计算这一段结果返回
    return compute(numbers, ops);
}
int calculate(string s)
{
    return f(s, 0);
}
// https://leetcode.cn/problems/decode-string/
int where_s = 0;
string add_str(int count, string s)
{
    string str;
    for (int i = 0; i < count; i++)
    {
        str += s;
    }
    return str;
}
string str_f(string s, int i)
{
    string cur;
    int count = 0;
    while (i < s.length() && s[i] != ']')
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            count = count * 10 + (s[i++] - '0');
        }
        else if (s[i] != '[')
        {
            cur += s[i++];
        }
        else
        {
            cur += add_str(count, str_f(s, i + 1));
            i = where_s + 1;
            count = 0;
        }
    }
    where_s = i;
    return cur;
}
string decodeString(string s)
{
    where_s = 0;
    return str_f(s, 0);
}

// N皇后
// https://leetcode.cn/problems/n-queens/
vector<vector<string>> ant;
bool check(int * path,int i,int j){
    for(int k=0;k<i;k++){
        if(path[k]==j||abs(path[k]-j)==abs(k-i))return false;
    }
    return true;
}
void dfs(int i, int n, int * path)
{
    if (i == n)
    {
        vector<string> k;
        for (int i = 0; i < n; i++)
        {
            string str;
            for (int j = 0; j < n; j++)
            {
                if (path[i] == j)
                {
                    str.append("Q");
                }
                else
                {
                    str.append(".");
                }
            }
            k.push_back(str);
        }
        ant.push_back(k);
        return;
    }
    for (int j = 0; j < n; j++)
    {
        if (check(path, i, j))
        {
            path[i]=j;
            dfs(i + 1, n, path);
            path[i]=-1;
        }
    }
}
vector<vector<string>> solveNQueens(int n)
{
    int path[20];
    dfs(0, n, path);
    return ant;
}

int main()
{
    // cout<<calculate("3+5/2+(5-4+4*(78+22))+90")<<endl;
    // cout << calculate("3+5 / 2") << endl;
    solveNQueens(4) ;

    return 0;
}