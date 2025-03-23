// 基于比较的排序
// 只需要定义好两个对象之间怎么比较即可，对象的数据特征并不关心，很通用
// 不基于比较的排序
// 和比较无关的排序，对于对象的数据特征有要求，并不通用

// 计数排序，非常简单，但是数值范围比较大了就不行了

// 基数排序的实现细节，非常优雅的一个实现
// 关键点：前缀数量分区的技巧、数字提取某一位的技巧
// 时间复杂度O(n)，额外空间复杂度O(m)，需要辅助空间做类似桶的作用，来不停的装入、弹出数字

// 一般来讲，计数排序要求，样本是整数，且范围比较窄
// 一般来讲，基数排序要求，样本是10进制的非负整数
// 如果不是就需要转化，代码里做了转化，并且代码里可以设置任何进制来进行排序
// 一旦比较的对象不再是常规数字，那么改写代价的增加是显而易见的，所以不基于比较的排序并不通用
// 0,0,2,3,5,7,3,3,2、、统计次数加前缀和
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N=1000;
const int BASE = 10;//改的越大，理论上会变大
class Solution
{
    int arr[N];
    int cnts[BASE];
    int help[N];
public:
    // 如果有负数的话，找到最小值，然后所有值减去最小值就能全部转化成正数
    //数组必须保证没有负数，bits表示最大的数有几位
    int* enter_main(vector<int> &row,int bits)
    {
        int length = row.size();
        for(int i=0;i<length;i++){
            arr[i]=row[i];
        }
        for(int offset=1;bits>0;offset*=BASE,bits--){
            fill(cnts,cnts+BASE,0);
            // 计算当前位，数字出现频率
            for(int i=0;i<length;i++){
                cnts[(arr[i]/offset)%BASE]++;
            }
            // 求出出现频率前缀和
            for(int i=1;i<BASE;i++){
                 cnts[i]=cnts[i]+cnts[i-1];
            }
            // 前缀和的数量刚好可以表示这个数应该放在那个位置上
            for(int i=length-1;i>=0;i--){
               help[--cnts[(arr[i]/offset)%BASE]]=arr[i];
            }
            for(int i=0;i<length;i++){
                arr[i]=help[i];
            }
        }
        return arr;
    }
};

int main()
{
    // 手动建堆
    Solution *solution = new Solution();
    vector<int> data;
    data.push_back(17);
    data.push_back(24);
    data.push_back(23);
    data.push_back(14);
    data.push_back(56);
    data.push_back(16);
    data.push_back(97);
    data.push_back(48);
    data.push_back(69);
    int* value = solution->enter_main(data,2);
    for(int i=0;i<9;i++)
       cout << value[i] << " ";
    cout<<endl;   
}