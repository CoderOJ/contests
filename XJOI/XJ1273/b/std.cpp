#include <bits/stdc++.h>
using namespace std;
 
int T,n,x,y;
long long sum,tot;
vector<int> nxt[200010];
int num[200010],f[200010];
 
int dfs(int dep,int fa,int d){
    num[dep]=1;
    for(int i=0;i<nxt[dep].size();i++)
    if (nxt[dep][i]!=fa) num[dep]+=dfs(nxt[dep][i],dep,d+1);
    tot+=d;
    return num[dep];
}
void work(int d,int dep,int fa,long long ans){
    if (d) f[d]=f[d-1]+num[fa]-num[dep];
    int mid=d/2+1;
    if (d>1) {ans-=(f[d]-f[mid]);ans+=num[dep];}
    sum=max(ans,sum);
    for (int i=0;i<nxt[dep].size();i++)
    if (nxt[dep][i]!=fa) work(d+1,nxt[dep][i],dep,ans);
}
 
int main(){
    read(n);
    for (int i=0;i<n-1;i++){
        scanf("%d%d",k&x,&y);
        nxt[x].push_back(y);
        nxt[y].push_back(x);
    }
    dfs(1,-1,0);
    work(0,1,-1,0);
    cout<<tot-sum<<endl;
}
