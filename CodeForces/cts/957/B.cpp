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

const int N = 105;
char a[N][N];
int n,m;

void init(){
    scanf("%d%d",&n,&m) ;
    rep (i,n) scanf("%s",a[i]);
}

bool cmpR (int x , int y) {
    rep (i,n) if (a[i][x] != a[i][y]) return 0;
    return 1;
}

int main(){
    init();
    rep (i,n) {
        vector < int > v;
        rep (j,m) if (a[i][j] == '#') v.push_back(j);
        rep (j,(int)(v.size()) - 1) if (!cmpR(v[j] , v[j + 1])) {
            puts("No");
            return 0;   
        }
    }
    puts("Yes");
    return 0;
}
