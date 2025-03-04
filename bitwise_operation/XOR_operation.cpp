// 异或运算就是无进位相加，满足交换律，结合律。同一批数字任意交互位置都一样
// 0^n=n,n^n=0;
// 整体异或是x,整体部分异或是y,那么剩下的部分就是x^y

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N=1000;
class Solution
{
    int arr[N];
public:
    void enter_main()
    {
        // 交换两个数，必须是不同地址
        int a=110,b=120;
        cout<<a<<" "<<b<<endl;
        a=a^b;
        b=a^b;
        a=a^b;
        cout<<a<<" "<<b<<endl;
        // 所有数都出现偶数次，只有一个数出现奇数次，找出奇数次的数
        int an[11]={1,2,3,4,4,3,2,1,5,1,1};
        int ans=0;
        for(int i=0;i<11;i++){
             ans^=an[i];
        }
        cout<<ans<<endl;
        // 数组中有2种数出现了奇数次，其他的数都出现了偶数次，返回这2种出现了奇数次的数
        int an2[12]={1,2,9,3,4,4,3,2,1,5,1,1};
        int ev1=0;
        for(int i=0;i<12;i++){
             ev1^=an2[i];
        }
        // Brian Kernighan算法 - 提取出二进制状态中最右侧的1
        int rightOne=ev1&(-ev1);

        int ev2=0;
        for(int i=0;i<12;i++){
            if((rightOne&an2[i])==rightOne){
               ev2^=an2[i];
            }
        }
        cout<<ev2<<" "<<(ev1^ev2)<<endl;
        // 数组中所有数都出现了M次，有一个数出现了k次，找到这个数
        int an3[20]={1,2,9,3,4,4,4,3,2,1,5,7,7,7,5,1,3,2,5,9};
        int as[32];
        fill(as,as+32,0);
        for(int j=0;j<20;j++){
             for(int i=0;i<32;i++){
                    as[i]+=(an3[j]>>i)&1;
             }
        }
        int ret=0;
        for(int j=0;j<32;j++){
            if(as[j]%3!=0)
            ret|=1<<j;
        }
        cout<<ret<<endl;
        //判断一个数是不是2的幂(二进制只有一个1)
        int m=64;
        cout<<(m==(m&(-m)))<<endl;
        // 大于且最接近2的幂
        int n=m;
        n--;//防止等于的出现，然后把后面的全部刷成1，在加一（就是找到最右侧的1，在上移动一位）
        n|=n>>1;
        n|=n>>2;
        n|=n>>4;
        n|=n>>8;
        n|=n>>16;
        cout<<n+1<<endl;
        int k=0;
        m--;
        for(int i=0;i<32;i++){
           if(((m>>i)&1)==1){
              k=i+1;
           }
        }
        cout<<(1<<k)<<endl;
        // 你两个整数 left 和 right ，表示区间 [left, right] ，返回此区间内所有数字 按位与 的结果
        // 在&的过程中只要出现0，就留不住。所以只要这个值没有小于left那么他最右边的那个1一定留不住
        int left=0,right =300;
        while(left<right){
            right-=(right&(-right));
        }
        cout<<right<<endl;
        // 翻转二进制位，常规思路把每一位都保存下来，再逆序合并回去，大神
        n=290;
          n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);//与上10101010，和01010101.然后分别左右移动一位。在合起来，实现相邻位两两交互
		n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);//与上11001100，和00110011.然后分别左右移动两位。在合起来，实现相连续两位，两两交互
		n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
		n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
		n = (n >> 16) | (n << 16);
        cout<<n<<endl;
        n=290;
        // 常规思路
          int anws[32];
         for(int i=0;i<32;i++){
            anws[i]=(n>>i)&1;
         }
         m=0;
         for(int i=31;i>=0;i--){
            if(anws[i]==1){
                m|=1<<(31-i);
            }
         }
         cout<<m<<endl;

    }
};

int main()
{
    // 手动建堆
    Solution *solution = new Solution();
    solution->enter_main();
}