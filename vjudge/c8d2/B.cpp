#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
#include <bitset>
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
int mp;

void init(){
    rep (i,N * N) {
        char x;
        cin >> x;
        mp |= (x == '+') << i;      
    }
}

void rev(int& mp,int x,int y) {
    int st = x << 2;
    mp ^= ( (15 - (1 << y)) << st );
    mp ^= (1 + (1 << 4) + (1 << 8) + (1 << 12)) << y;
}

void solve() {
    int ans = 0x3f3f3f3f;
    int code ;
    rep (i, (1 << 16) ) {
        int w = 0;
        rep (j,16) w += ((i >> j) & 1);
        //cout << bitset < 32 > (mp) << endl;
        int cp = mp;
        rep (j,16) if ((i >> j) & 1) rev(cp , ((j >> 2)) , j & 3);
        //cout << bitset < 32 > (mp) << endl;
        if (cp != 0) continue;
        if (ans > w) {
            ans = w;
            code = i;
        }
    }
    printf("%d\n",ans);
    rep (i,16) if ((code >> i) & 1){
        printf("%d %d\n" , ((i >> 2)) + 1 , (i & 3) + 1);
    }
}

int main(){
    init();
    solve(); 
    return 0;
}
