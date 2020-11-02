#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn=5E5+5;
int n,k;
ll a[maxn],b[maxn];
inline int read()
{
    char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    int s=ch-'0';ch=getchar();
    while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();}
    return s;
}
inline bool check(ll x)
{
    for(int i=1;i<=n;++i)
        b[i]=b[i-1]+a[i]-x;
    int tot=0;
    for(int i=0;i<=n;++i)
        for(int j=i;j;--j)
        {
            if(b[j-1]>b[j])
            {
                swap(b[j],b[j-1]);
                ++tot;
                if(tot>=k)
                    return true;
            }
            else
                break;
        }
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
    n=read(),k=read();
    ll maxx=0;
    for(int i=1;i<=n;++i)
    {
        a[i]=read();
        a[i]*=10000;
        maxx=max(maxx,a[i]);
    }
    ll l=1,r=maxx,mid;
    while(l<r)
    {
        mid=(l+r)/2;
        if(check(mid))
            r=mid;
        else
            l=mid+1;
    }
    cout<<fixed<<setprecision(3)<<(long double)(l)/10000<<endl;
    return 0;
}
