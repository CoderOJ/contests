#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define m_p make_pair
#define sz(x) (int)x.size()
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" ";cerr<<endl;
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define gc() getchar()
//char buf[1<<23],*p1=buf,*p2=buf;
//#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
template <class T> void read(T &x)
{
    x=0; char c=gc(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=gc();
    while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=gc();
    if (flag) x=-x;
}
template <class T> T _max(T a,T b){return a>b ? a : b;}
template <class T> T _min(T a,T b){return a<b ? a : b;}
template <class T> bool checkmax(T &a,T b){return b>a ? a=b,1 : 0;}
template <class T> bool checkmin(T &a,T b){return b<a ? a=b,1 : 0;}
const int N=100050;
int n,k,q;
int arr[13][N];
bitset <4096> a[N];
void init()
{
    read(n); read(k); read(q);
    for (int i=1;i<=k;++i)
    {
        for (int j=1;j<=n;++j)
        {
            read(arr[i][j]);
        }
    }
    for (int S=0;S<(1<<k);++S)
    {
        for (int i=0;i<k;++i)
        {
            if (S>>i&1) a[i+1][S]=1;
        }
    }
}
 
bool valid(int num,int pos,int now)
{
    int S=0;
    for (int i=1;i<=k;++i)
    {
        if (arr[i][pos]>=num) S|=(1<<(i-1));
    }
    if (a[now][S]) return 1;
    else return 0;
}
 
void solve()
{
    int opt,x,y;
    int cnt=k;
    while (q--)
    {
        //for (int i=1;i<=cnt;++i) cout<<a[i]<<" ";cout<<endl;
        read(opt); read(x); read(y);
        if (opt==1)
        {
            ++cnt;
            a[cnt]=a[x]|a[y];
        }
        else if (opt==2)
        {
            ++cnt;
            a[cnt]=a[x]&a[y];
        }
        else
        {
            int ans=0;
            for (int i=1;i<=k;++i)
            {
                if (valid(arr[i][y],y,x))
                {
                    checkmax(ans,arr[i][y]);
                }
            }
            printf("%d\n",ans);
        }
    }
}
 
int main()
{
    init();
    solve();
    return 0;
}
