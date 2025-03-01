// 堆结构
// 完全二叉树和数组前缀范围来对应，大小，单独的变量size来控制
// i的父亲节点：(i-1)/2，i的左孩子：i*2 + 1，i的右孩子：i*2 + 2
// 堆的定义（大根堆、小根堆），本节课讲解按照大根堆来讲解，小根堆是同理的。
// 堆的调整：heapInsert（向上调整）、heapify（向下调整）
// heapInsert、heapify方法的单次调用，时间复杂度O(log n)，完全二叉树的结构决定的

// 堆排序
//    A. 从顶到底建堆，时间复杂度O(n * log n)，log1 + log2 + log3 + … + logn -> O(n*logn)
//       或者用增倍分析法：建堆的复杂度分析+子矩阵数量的复杂度分析
//    B. 从底到顶建堆，时间复杂度O(n)，总代价就是简单的等比数列关系，为啥会有差异？简单图解一下
//    C. 建好堆之后的调整阶段，从最大值到最小值依次归位，时间复杂度O(n * log n)
// 时间复杂度O(n * log n)，不管以什么方式建堆，调整阶段的时间复杂度都是这个，所以整体复杂度也是这个
// 额外空间复杂度是O(1)，因为堆直接建立在了要排序的数组上，所以没有什么额外空间

#include <iostream>
#include <vector>
using namespace std;
#include <queue>
const int N=100;
class Solution
{
  int arr[N];
  int length=0;
public:
    void swap(int a,int b){
        int k=arr[a];
        arr[a]=arr[b];
        arr[b]=k;
    }
    // 向上调整大根堆
    void heapInsert(int i)
    {
        while(arr[i]>arr[(i-1)/2]){
            swap(i,(i-1)/2);
            i=(i-1)/2;
        }
    }
    // i位置变小重新调整大根堆
    void heapify(int i)
    {
        int l = i*2+1;
        while (l<length)
        {
            int best=(l+1<length&&arr[l+1]>arr[l])?l+1:l;
            if(arr[best]>arr[i]){
                swap(best,i);
                i=best;
                l=best*2+1;
            }else{
                break;
            }
        }
        
    }
     //从顶到底建立大根堆
    int* enter_main_1(vector<int> &row)
    {
        length = row.size();
        for(int i=0;i<length;i++){
            arr[i]=row[i];
        }
        for(int i=0;i<length;i++){
            heapInsert(i);
        }
        while(length>1){
           swap(0,--length);
           heapify(0);
        }
        return arr;
    }

         //从底到顶建立大根堆
    int* enter_main_2(vector<int> &row)
    {
        length = row.size();
        for(int i=0;i<length;i++){
            arr[i]=row[i];
        }
        for(int i=length-1;i>=0;i--){
            heapify(i);
        }
        while(length>1){
           swap(0,--length);
           heapify(0);
        }
        return arr;
    }
};

priority_queue<int> maxHeap; // 默认是最大堆
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
    int* value = solution->enter_main_2(data);
    for(int i=0;i<9;i++)
    cout << value[i] << endl;

    // 使用 lambda 作为比较函数，实现小根堆
    // auto cmp = [](int a, int b) { return a > b; };
    // priority_queue<int, vector<int>, decltype(cmp)> minHeap(cmp);

    // priority_queue<int, vector<int>, greater<int>> minHeap;
    
    //  系统自带，默认大根堆
    // 插入元素建队
    maxHeap.push(4);
    maxHeap.push(10);
    maxHeap.push(3);
    maxHeap.push(5);
    maxHeap.push(1);
    maxHeap.push(7);
    maxHeap.push(9);
    // 取出元素
    cout << "大根堆元素（从大到小）: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " "; // 访问堆顶元素
        maxHeap.pop(); // 删除堆顶
    }
    cout << endl;
}
//练习题
