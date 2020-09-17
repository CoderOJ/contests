#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=105;
const int inf=100000000;
int a[1009];
void checkmin(int &a,int b){if (b<a) a=b;}
int ran(int l,int r)
{
    return 1LL*rand()*rand()%(r-l+1)+l;
}

void file()
{
    freopen("in","w",stdout);
}

void init()
{
    srand(time(0));
    //ios::sync_with_stdio(0);
    int n=10;
    cout<<n<<endl;
    for (int i=1;i<=n;++i)
    {
        int x=rand()%10;
        if (x==0) a[i]=0;
        else a[i]=1;
    }
    for (int i=1;i<=10000;++i)
    {
        int x=ran(1,n);
        int nxt=(x==n ? 1 : x+1);
        if (a[x]>0) --a[x],++a[nxt];
    }
    for (int i=1;i<=n;++i) cout<<a[i]<<" ";
    cout<<endl;
}

void solve()
{

}

#undef int
int main()
{
    file();
    init();
    solve();
    return 0;
}
