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

const int N = 4;
int rp[N][N];
int goal[N][N];

void init(){
    rep (i,N) rep(j,N) {
        char x;
        cin >> x;
        rp[i][j] = x == 'b';
    }
}

const int mv[5][2] = {{0,0},{0,1},{0,-1},{-1,0},{1,0}};
void rev (int a[][N],int x,int y) {
    rep (dr,5) {
        int nx = x + mv[dr][0];
        int ny = y + mv[dr][1];
        if (0 <= nx && nx < N && 0 <= ny && ny < N) a[nx][ny] ^= 1;  
    }
}

int ans = 0x3f3f3f3f;
int ty[N][N];
void solve() {
    rep (bit , 16) {
        int step = 0;
        rep (i,N) rep(j,N) ty[i][j] = rp[i][j];
        rep (i,N) if (bit >> i & 1) rev(ty,0,i),step++;
        repa (i,N - 1) rep (j,N) if (ty[i - 1][j] != goal[i - 1][j]) rev(ty,i,j),step++;
        rep (i,N) if (ty[3][i] != goal[3][i]) goto nxt;
        ans = min(ans,step);
        nxt:;
    }
}

int main(){
    init();
    rep (i,N) rep(j,N) goal[i][j] = 0;
    solve();
    rep (i,N) rep(j,N) goal[i][j] = 1;
    solve();
    if (ans == 0x3f3f3f3f) puts("Impossible");
    else printf("%d\n",ans);
    return 0;
}
