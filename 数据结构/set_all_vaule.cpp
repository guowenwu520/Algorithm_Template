
#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;
// setall，要求时间复杂度o(1),设置所有的map值为value;,设置一个辅助时间，并不实际改变所有的值
map<int,pair<int,int>> m;
int cut=0;
int map_value_time=-1;
int map_value_value=0;
void setvalue(int a,int b){
   cut++;
   m[a]={b,cut};
}

void setall(int a){
   map_value_time=cut;
   map_value_value=a;
}
int getvalue(int a){
    if(!m.count(a))return -1;
    auto item=m[a];
    if(item.second<=map_value_time)return map_value_value;
    return item.first;
}

void setall_show(){
    setvalue(3,1);
    setvalue(4,2);
    setvalue(6,5);
    setall(19);
    setvalue(18,9);
    cout<<getvalue(18)<<endl;
    setvalue(8,9);
    cout<<getvalue(8)<<endl;
}
int main()
{
    setall_show();
}