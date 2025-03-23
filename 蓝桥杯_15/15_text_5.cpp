#include <bits/stdc++.h>
using namespace std;
const int N=1e7+5;//评测用
int r[N]={0},l[N]={0};//两个数组存放正负方向的矿洞
int f=0,res=0;//
int main(){
int n,m;cin>>n>>m;
for(int i=1;i<=n;i++){
  int pos;cin>>pos;//输入坐标，即矿洞 
  if(pos>0) r[pos]++;//存放正负方向的矿洞
  if(pos<0) l[abs(pos)]++;
  if(!pos) f++;//也要考虑0坐标的矿洞
}
r[0]=l[0]=0;
for(int i=1;i<=m;i++){//移动距离最大为m，在m范围里前缀和，统计m范围里左右两边各自的矿洞
  r[i]+=r[i-1];
  l[i]+=l[i-1];
}
for(int i=1;i<=m;i++){//也是在m范围里考虑，计算矿石数目
   int sum1=r[i];
  if(m-2*i>0){
      sum1+=l[m-2*i];//从正坐标可以返回到负坐标的情况，如果返回不了直接等于第一个sum1
  }
    int sum2=l[i];
  if(m-2*i>0){
      sum2+=r[m-2*i];//从负坐标可以返回到正坐标的情况，如果返回不了直接等于第一个sum2
  }
  res=max({res,sum1,sum2});//正确更新res避免每次max被覆盖 
}
cout<<res+f;
return 0;
}