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

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second

struct Map {
    char a[4][4];
};

int n,m;
Map inital;
void init(){
    scanf("%d%d",&n,&m);
    rep (i,n) rep (j,m) cin >> inital.a[i][j];
}

void show(Map x) {
    rep (i,n) {
        rep (j,m) cout << x.a[i][j];
        puts("");
    }
}

bool canPlace(const Map& mp , int x , int y , int dir) {
    if (mp.a[x][y] != '.') return 0;
    if (dir == 0) { // h
        for (int i = y;i>=0;i--) {
            if (mp.a[x][i] == '*') break;
            if (mp.a[x][i] == '#') return 0;
        }
        for (int i = y;i<m;i++) {
            if (mp.a[x][i] == '*') break;
            if (mp.a[x][i] == '#') return 0;
        }
        return 1;
    }else { // v
        for (int i = x;i>=0;i--) {
            if (mp.a[i][y] == '*') break;
            if (mp.a[i][y] == '#') return 0;
        }
        for (int i=x;i<n;i++) {
            if (mp.a[i][y] == '*') break;
            if (mp.a[i][y] == '#') return 0;
        }
        return 1;
    }
}

void place(Map& mp , int x , int y , int dir) {
    if (dir == 0) { // h
        for (int i = y;i>=0;i--) {
            if (mp.a[x][i] == '*') break;
                mp.a[x][i] =  '*';
        }
        for (int i = y + 1;i<m;i++) {
            if (mp.a[x][i] == '*') break;
                mp.a[x][i] =  '*';
        }
    }else { // v
        for (int i = x;i>=0;i--) {
            if (mp.a[i][y] == '*') break;
                mp.a[i][y] =  '*';
        }
        for (int i = x + 1;i<n;i++) {
            if (mp.a[i][y] == '*') break;
                mp.a[i][y] =  '*';
        }
    }
}

bool dfs(Map mp) {
    //show(mp);
    rep (i,n) rep (j,m) rep (opt,2) {
        if (canPlace(mp , i , j  , opt)) {
            Map ty = mp;
            place(ty , i , j , opt);
            if (!dfs(ty)) return 1;
        }
    }
    return 0;
}

void solve () {
    int res = 0;
    rep (i,n) rep (j,m) rep (opt , 2){
        Map ty = inital;
        if (canPlace(ty , i , j , opt)) {
            place(ty , i , j , opt);
            res += !dfs(ty);
        }
    }
    cout << res << endl;
}

int main(){
    int T;
    scanf("%d",&T);
    repa (ks , T) {
        init() ;
        printf("Case #%d: ",ks);
        solve ();
    }
    return 0;
}
