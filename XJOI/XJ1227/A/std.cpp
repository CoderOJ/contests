include<cstdio>
#include<algorithm>
using namespace std;
#define ri register int
#define ll long long
int n,m,q[300005],h=1,t;
ll ans[300005],a[300005];
struct node
{
    int id;
    ll k;
}b[300005];
inline bool cmp(node a,node b)
{
    return a.k>b.k;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(ri i=1;i<=n;i++)
    {
        scanf("%lld",a+i);
        while(h<t&&(a[q[t]]-a[q[t-1]])*(i-q[t])>=(a[i]-a[q[t]])*(q[t]-q[t-1]))t--;
        q[++t]=i;
    }
    for(ri i=1;i<=m;i++)scanf("%lld",&b[i].k),b[i].id=i;
    sort(b+1,b+m+1,cmp);
    for(ri i=1;i<=m;i++)
    {
        while(h<t&&(ll)-b[i].k*(q[h+1]-q[h])>=a[q[h+1]]-a[q[h]])h++;
        ans[b[i].id]=(ll)b[i].k*q[h]+a[q[h]];
    }
    for(ri i=1;i<=m;i++)printf("%lld\n",ans[i]);
}
