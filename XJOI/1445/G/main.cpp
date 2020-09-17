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

#define long long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 

const int N = 105;
const int M = 15;
const int BIN = 100;
const int INF = 0x3f3f3f3f;
int ter[N];
int dp[2][BIN][BIN];
int n,m;

void init(){
    scanf("%d%d",&n,&m);
    rep (i,n) {
        char s[M]; scanf("%s", s);
        rep (j,m) ter[i] |= (s[j] == 'H') << j;
    }
}

vector < int > poss,numw;
int len;

void makePoss() {
    rep (x,1 << m) {
        if ( ! (( x & (x>>1) ) || ( x & (x>>2) )) ) {
            poss.push_back(x);
            numw.push_back(0);
            rep (bw,m) numw[len] += (x >> bw) & 1;
            len++;
        }
    }
}

inline void checkMax(int& a,int b) {
    if (b > a) a = b;
}
#define CLEAR(bin) rep (i,BIN) rep (j,BIN) dp[bin][i][j] = -INF
void solve() {
    int cur = 0;
    CLEAR(cur);
    dp[cur][0][0] = 0;
    rep (i,n) {
        rep (idlls,len) {
            int lls = poss[idlls];
            if (i > 1 && (lls & ter[i - 2]) ) continue;
            rep (idls,len) {
                int ls = poss[idls];
                if (lls & ls) continue;
                if (dp[cur][idls][idlls] < 0) continue;
                if (i > 0 && (ls & ter[i - 1]) ) continue;

                rep (idpos,len) {
                    int pos = poss[idpos];
                    if (pos & ter[i]) continue;
                    if ( (pos & lls) || (pos & ls) ) continue;
                    checkMax(dp[cur ^ 1][idpos][idls] , dp[cur][idls][idlls] + numw[idpos]);
                }
            }
        }
        CLEAR(cur);
        cur ^= 1;
    }
    int ans = -1;
    rep (i,len) rep (j,len) checkMax(ans,dp[cur][i][j]);
    printf("%d\n",ans);
}

int main(){
    init();
    makePoss();
    solve(); 
    return 0;
}
