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

vector < pr > e;
void side(int k , int st) {
    repa (i,k - 1) e.push_back( pr(st , st + i) );
    for (int i = st + 1 ; i < st + k ; i++) rep (j,k - 1) e.push_back( pr(i , st + k + j) );
    for (int i = st + k ; i < st + k * 2  - 1; i += 2) e.push_back( pr(i , i + 1) );
}

void show(int k) {
    cout << 4 * k - 2 << ' ' << e.size() << endl;
    foreach(i,e) printf("%d %d\n",e[i].L , e[i].R);
}

int main(){
    int k;
    cin >> k;
    if (!(k & 1)) {
        puts("NO");
        return 0;
    }
    puts("YES");
    side (k,1);
    side (k,k * 2);
    e.push_back( pr(1 , k * 2) );
    show(k);
    return 0;
}
