#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define N 100010
#define ll long long
using namespace std;
int val[N<<2];
void insert(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R){val[u]++;return;}
    int mid=(l+r)>>1;
    if(L<=mid) insert(u<<1,l,mid,L,R);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R);
}
int main()
{
    long long n;
    scanf("%lld", &n);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
        insert(1,1,n,i,j);
    long long ans=0;
    for(int i=1;i<=n<<2;i++) ans+=val[i];
    printf("%lld\n",ans);
    return 0;
}
