#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500005;
int a[N];
signed main()
{
    int n,L,R,ans=0;
    scanf("%lld%lld%lld",&n,&L,&R);
    for(int i=1;i<=n;i++) scanf("%lld",a+i);
    for(int i=1;i<n;i++)
    {
        if(a[i]+a[i+1]>=L) continue;
        int x=L-a[i]-a[i+1],y=R-a[i+1]-a[i+2];
        if(x<y||i==n-1) ans+=x,a[i+1]+=x;
        else ans+=x,a[i]+=x-y,a[i+1]+=y;
    }
    //nc
    for(int i=1;i<n;i++) if(a[i]+a[i+1]<L||a[i]+a[i+1]>R) return printf("-1\n"),0;
    printf("%lld\n",ans);
    cerr << ans << endl;
    for(int i=1;i<=n;i++) printf("%lld ",a[i]);printf("\n");
    return 0;
}
