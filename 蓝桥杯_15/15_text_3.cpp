#include <iostream>
#include<map>
#include<algorithm>
using namespace std;
map<int,int> quan;
bool comper(int a,int b){
     int aq=0,bq=0,x=a,y=b;
     while(x){
         aq+=quan[(x%10)];
         x/=10;
     }
     while(y){
         bq+=quan[(y%10)];
         y/=10;
     }
     if(aq>bq){
        return 0;
     }else if(aq==bq){
        return a>b?0:1;
     }else{
       return 1;
     }
}
int main()
{
    int n;
    cin >> n;
    int a[200001];
    quan[0]=1;
    quan[1]=0;
    quan[2]=0;
    quan[3]=0;
    quan[4]=1;
    quan[5]=0;
    quan[6]=1;
    quan[7]=0;
    quan[8]=2;
    quan[9]=1;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    
    sort(a,a+n,comper);
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}