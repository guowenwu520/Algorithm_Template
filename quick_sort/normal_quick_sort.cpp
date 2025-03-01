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
public:
    void swap(int a,int b){
        int k=arr[a];
        arr[a]=arr[b];
        arr[b]=k;
    }
    //排序,以右边固定为基准，找到第一个小于和第一个大于。交换，最后归位基准
    int partSort(int l,int r){
      int key=l;
      int value=arr[key];
      while (l<r)
      {
        while (l<r&&arr[l]<=value)l++;
        while (l<r&&value<=arr[r])r--;
        swap(l,r);
      }
      arr[key]=arr[l];
      arr[l]=value;
      return l;
    }
    //递归排序
    void quickSort(int l,int r){
        if(l>=r)return;
        int key_i=partSort(l,r);
        quickSort(l,key_i-1);
        quickSort(key_i+1,r);
    }
   
     //从顶到底建立大根堆
    int* enter_main_1(vector<int> &row)
    {
        int length = row.size();
        for(int i=0;i<length;i++){
            arr[i]=row[i];
        }
        quickSort(0,length-1);
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


