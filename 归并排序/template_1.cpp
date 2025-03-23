// 原理：
// 1）思考一个问题在大范围上的答案，是否等于，左部分的答案 + 右部分的答案 + 跨越左右产生的答案
// 2）计算“跨越左右产生的答案”时，如果加上左、右各自有序这个设定，会不会获得计算的便利性
// 3）如果以上两点都成立，那么该问题很可能被归并分治解决（话不说满，因为总有很毒的出题人）
// 4）求解答案的过程中只需要加入归并排序的过程即可，因为要让左、右各自有序，来获得计算的便利性

// 补充：
// 1）一些用归并分治解决的问题，往往也可以用线段树、树状数组等解法。时间复杂度也都是最优解，这些数据结构都会在
// 【必备】或者【扩展】课程阶段讲到
// 2）本节讲述的题目都是归并分治的常规题，难度不大。归并分治不仅可以解决简单问题，还可以解决很多较难的问题，只要符合上面说的特征。比如二维空间里任何两点间的最短距离问题，这个内容会在【挺难】课程阶段里讲述。顶级公司考这个问题的也很少，因为很难，但是这个问题本身并不冷门，来自《算法导论》原题
// 3）还有一个常考的算法：“整块分治”。会在【必备】课程阶段讲到


#include <iostream>
#include <vector>
using namespace std;
const int N=100;
class Solution
{
    int arr[N];
    int temp[N];
public:
    //部分排序
    int merge(int l,int m,int r){
        // 合并之前进行一些记录工作，举例记录 求数组在某个值前面的所有小于当前值的和
        // 固定前半部分还是后半部分，取决于我的结果是否可以累加，当固定值移动的时候，前面是否都满足之前的要求
        // 这里已经保证了区分两端是有序的情况，也就是说后面的数据之会更大，所以一定包含之前的结果
        int ans=0;
        for(int j=m+1,i=l,sum=0;j<r;j++){
            while(i<=m&&arr[i]<=arr[j]){
                sum+=arr[i++];
            }
            ans+=sum;
        }
        int index=0;
        int i=l;
        int j=m+1;
        while(i<=m&&j<=r)temp[index++]=(arr[i]<arr[j])?arr[j++]:arr[i++];
        while (i<=m)temp[index++]=arr[i++];
        while (j<=r)temp[index++]=arr[j++];
        for(int k=r;k>=l;k--){
           arr[k]=temp[--index];
        }
        return ans;
    }
    //递归排序
    int mergeSort(int l,int r){
        if(l==r)return 0;
        int mid=l+(r-l)/2;
       return mergeSort(mid+1,r)+mergeSort(l,mid)+merge(l,mid,r);
    }
   
     //从顶到底建立大根堆
    int* enter_main_1(vector<int> &row)
    {
        int length = row.size();
        for(int i=0;i<length;i++){
            arr[i]=row[i];
        }
        int ans=mergeSort(0,length-1);
        cout<<"记录个数 "<<ans<<endl;
        return arr;
    }

};

int main()
{
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
   int* value = solution->enter_main_1(data);
    for(int i=0;i<9;i++)
    cout << value[i] << " ";
}
//练习题
//    翻转对数量: https://leetcode.cn/problems/reverse-pairs/

