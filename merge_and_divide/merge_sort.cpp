
// 1）左部分排好序、右部分排好序、利用merge过程让左右整体有序
// 2）merge过程：谁小拷贝谁，直到左右两部分所有的数字耗尽，拷贝回原数组
// 3）递归实现和非递归实现
// 4）时间复杂度O(n * logn)
// 5）需要辅助数组，所以额外空间复杂度O(n)
// 6）归并排序为什么比O(n^2)的排序快？因为比较行为没有浪费！
// 7）利用归并排序的便利性可以解决很多问题 - 归并分治 - 下节课

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
    void merge(int l,int m,int r){
        int index=0;
        int i=l;
        int j=m+1;
        while(i<=m&&j<=r)temp[index++]=(arr[i]<arr[j])?arr[j++]:arr[i++];
        while (i<=m)temp[index++]=arr[i++];
        while (j<=r)temp[index++]=arr[j++];
        for(int k=r;k>=l;k--){
           arr[k]=temp[--index];
        }
    }
    //递归排序
    void mergeSort(int l,int r){
        if(l==r)return;
        int mid=l+(r-l)/2;
        mergeSort(l,mid);
        mergeSort(mid+1,r);
        merge(l,mid,r);
    }
   
     //从顶到底建立大根堆
    int* enter_main_1(vector<int> &row)
    {
        int length = row.size();
        for(int i=0;i<length;i++){
            arr[i]=row[i];
        }
        mergeSort(0,length-1);
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