#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <ctime>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <bitset>
using namespace std;
#ifdef enable_ll
    #define int long long
#endif
#ifdef DEBUG
    #define out(u) cout<<u<<" "
    #define outln(u) cout<<u<<endl
    #define see(u) cout<<#u<<"="<<u<<" "
    #define seeln(u) cout<<#u<<"="<<u<<endl
    #define line cout<<"---------------------\n"
#else
    #define out(u)
    #define outln(u)
    #define see(u)
    #define seeln(u)
    #define line
#endif
#define m_p make_pair
#define pii pair<int,int>
#define piii pair<int,pii>
bool checkmin(int &a,int b){return (b<a ? a=b,1 : 0);}
bool checkmax(int &a,int b){return (b>a ? a=b,1 : 0);}
const int N=30005;
int n,m;
struct node
{
    double x[4];
    int id;
    void read()
    {
        for (int i=0;i<=3;++i) scanf("%lf",&x[i]);
    }
}s[N],t[N];
int typ;
bitset <N> B[N],now;
bool cmp(node a,node b)
{
    return a.x[typ]<b.x[typ];
}

void init()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        s[i].id=i;
        s[i].read();
        //scanf("%lf",&s[i]);
    }
    scanf("%d",&m);
    for (int i=1;i<=m;++i)
    {
        t[i].id=i;
        t[i].read();
        //scanf("%lf",t[i]);
    }
}

void subtask1()
{
    for (typ=0;typ<=3;++typ)
    {
        line;
        sort(s+1,s+n+1,cmp);
        sort(t+1,t+m+1,cmp);
        int cur=1;
        now.reset();
        for (int i=1;i<=m;++i)
        {
            while (cur<=n&&s[cur].x[typ]<=t[i].x[typ])
            {
                now[s[cur].id]=1;
                seeln(s[cur].id);
                ++cur;
            }
            typ ? B[t[i].id]&=now : B[t[i].id]=now;
        }
    }
    for (int i=1;i<=m;++i)
    {
        //cout<<B[i]<<endl;
        printf("%d\n",(int)B[i].count());
    }
}

void solve()
{
    subtask1();
}

#undef int
int main()
{
    init();
    solve();
    return 0;
}
