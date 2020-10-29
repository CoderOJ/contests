#include <bits/stdc++.h>
#define int long long
#define N 500005
using namespace std;
priority_queue<long long> q;
long long n,x,y,ans,tot;
signed main()
{
//  freopen("in.txt","r",stdin);
    scanf("%lld%lld%lld",&n, &x, &y);
    tot=1;
    for (long long i=1,now,cnt1,cnt2;i<=n;i++)
    {
        scanf("%lld",&now);
        cnt1=(now-1)/y;
        cnt2=(now-1)%y/x+1;
        tot+=cnt1;
        if (tot>=cnt2)
        {
            ans++;
            tot-=cnt2;
            q.push(cnt2);
        }
        else if ((!q.empty()) && q.top()>cnt2)
        {
            tot+=q.top()-cnt2;
            q.pop();
            q.push(cnt2);
            tot++;
        }
        else tot++;
    }
    printf("%lld\n", ans);
    return 0;
}
