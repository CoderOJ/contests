#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

void init();
void solve();
int main(){
try { 

#ifndef CUSTOM_MAIN
#ifdef MULTIPLE_TEST_CASES_WITH_T

int T; scanf("%d",&T); while(T--) {init(); solve();}

#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T

while(1) {try{init(); } catch(bool t){return 0;} solve(); }

#else

init(); solve();

#endif
#endif
#endif

} catch (const char* s) { return 0; }
    return 0;
}

#ifdef ENABLE_LL
#define int long long
#endif

#ifdef ENABLE_LL
#define I "%lld"
#define II "%lld%lld"
#define III "%lld%lld%lld"
#define IIII "%lld%lld%lld%lld"
#define IN "%lld\n"
#define IIN "%lld%lld\n"
#define IIIN "%lld%lld%lld\n"
#define IIIIN "%lld%lld%lld%lld\n"
#else
#define I "%d"
#define II "%d%d"
#define III "%d%d%d"
#define IIII "%d%d%d%d"
#define IN "%d\n"
#define IIN "%d%d\n"
#define IIIN "%d%d%d\n"
#define IIIIN "%d%d%d%d\n"
#endif

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr; typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; } char nextChar(){ char r; ist>>r; return r;} }; Scanner sc(cin);
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } }
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }

#define inf 0x3f3f3f3f
const int N=11000;
int n,q,vi[110][110][30],dp[110];
char s[110];
int len[30][30];
vector <int> tr[30][30];

void init() {
    scanf("%d",&n);
    repa (i,n) {
        char ch[5];
        scanf("%s",ch);
        tr[ch[1]-'A'][ch[2]-'A'].push_back(ch[0]-'A');
    }
    rep (i,26) rep (j,26) {
        sort(tr[i][j].begin(),tr[i][j].end());
        len[i][j]=unique(tr[i][j].begin(),tr[i][j].end())-tr[i][j].begin();
    }
}

void solve() {
    scanf("%d",&q);
    while (q--) {
        scanf("%s",s+1);
        int m=strlen(s+1);
        repa (i,m) repa (j,m) rep (k,26) vi[i][j][k]=0;
        repa (i,m) vi[i][i][s[i]-'A']=1;
        repi (l,2,m) repa (i,m-l+1) {
            int j=i+l-1;
            repi (k,i,j-1) {
                rep (p, 26) {
                    if (!vi[i][k][p]) continue;
                    rep (q,26) {
                        if (!vi[k+1][j][q]) continue;
                        for (int h=0;h<len[p][q];h++)
                          vi[i][j][tr[p][q][h]]|=1;
                    }
                }
            }
        }
        repa (i,m) dp[i]=inf;
        dp[0]=0;
        repa (i,m) rep (j,i) {
            if (!vi[j+1][i]['S'-'A']) continue;
            dp[i]=min(dp[i],dp[j]+1);
        }
        if (dp[m]==inf) printf("NIE\n");
        else printf(IN,dp[m]);
    }
}
