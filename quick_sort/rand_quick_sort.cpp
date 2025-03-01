// 原理：
// 每次递归选择第一个位置作为关键位置，前后分别寻找大于和小于的数，两两交互，相遇时在把关键位置交换过去
#include <iostream>
#include <vector>
using namespace std;
const int N=100;
class Solution
{
    int arr[N];
    int temp[N];
    int fl=0,fr=0;
public:
    void swap(int a,int b){
        int k=arr[a];
        arr[a]=arr[b];
        arr[b]=k;
    }
    //排序,小于等于x的方一边，大于的方一边
    int partSort(int l,int r,int x){
      int a=l,x1=0;
      for(int i=l;i<=r;i++)
      {
        if(arr[i]<=x){
            swap(a,i);
            if(arr[a]==x){
                x1=a;
            }
            a++;
        }
      }
      swap(x1,a-1);
      return a-1;
    }

    //排序,小于x的方一边，等于的一堆，大于的方一边
    void partSort2(int l,int r,int x){
      fl=l;
      fr=r;
      for(int i=l;i<=fr;i++)
      {
        // 小于的移动到左边，左边区域变大
        if(arr[i]<x){
            swap(fl,i);
            fl++;
        }
        // 大于的移动右边，右边区域变大，同时换过来的是没有判断过的i不能加
        if(arr[i]>x){
            swap(i,fr);
            fr--;
            i--;
        }
      }
    }

    //递归排序
    void quickSort(int l,int r){
        if(l>=r)return;
        // 随机选择一个位置
        int x=arr[rand()%(r-l)+l];
        int key_i=partSort(l,r,x);
        quickSort(l,key_i-1);
        quickSort(key_i+1,r);
    }
   
    //递归排序
    void quickSort2(int l,int r){
        if(l>=r)return;
        // 随机选择一个位置
        int x=arr[rand()%(r-l)+l];
        partSort2(l,r,x);
        int left=fl;
        int right=fr;
        quickSort2(l,left-1);
        quickSort2(right+1,r);
    }
   
     //从顶到底建立大根堆
    int* enter_main_1(vector<int> &row)
    {
        int length = row.size();
        for(int i=0;i<length;i++){
            arr[i]=row[i];
        }
        quickSort2(0,length-1);
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


