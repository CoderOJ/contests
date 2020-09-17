#pragma GCC optimize(2)
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
#define see(a) std::cout << #a << "=" << (a) << std::endl
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
   
const int INF = 0x3f3f3f3f;
const char figure[10] = {
    (char)0b01110111,
    (char)0b00010010,
    (char)0b01011101,
    (char)0b01011011,
    (char)0b00111010,
    (char)0b01101011,
    (char)0b01101111,
    (char)0b01010010,
    (char)0b01111111,
    (char)0b01111011,
};
  
int __ctw[100000];
inline int _ctw(int x) {
    if (x == 0) return 1;
    int res = 0;
    while (x) {
        res++;
        x /= 10;
    }
    return res;
}
inline int ctw(int x) {return __ctw[x];}
  
int __ct[2560];
inline int _ct(int x) { //count bit(1) in x
    int res = 0 ;
    while (x) {
        res += (x & 1);
        x >>= 1;
    }
    return res;
}
inline int ct(int x) {return __ct[x];}
  
int __ctn[100000];
inline int _ctn(int x) { //count number of sticks used for figure x
    int res = 0;
    int len = ctw(x);
    rep(_,len) {
        res += ct(figure[ x % 10 ]);
        x /= 10;
    }
    return res;
}
inline int ctn(int x) { return __ctn[x]; }
  
inline int diff(int a, int b) { //count how diff a & b are
    int res = 0;
    int len = ctw(a);
    rep(_,len) {
        res += ct(figure[a % 10] ^ figure[b % 10]);
        a /= 10 ; b /= 10;
    }
    return res;
}
  
void init() {
    rep (i,100000) __ctw[i] = _ctw(i);
    rep (i,2560)   __ct [i] = _ct (i);
    rep (i,100000) __ctn[i] = _ctn(i);
}

int solve(int tot , int op , int wa , int wb , int wc , int a , int b , int c) {
    tot -= (op == 1) ? 2 : 1;
    int res = INF;
    see(res);
    int sta = pow(10,wa - 1) , eda = sta * 10;
    int stb = pow(10,wb - 1) , edb = stb * 10;
    sta -= (wa == 1); stb -= (wb == 1);
    for (int i=sta;i<eda;i++) {
        for (int j=stb;j<edb;j++) {
            int k = i + op * j;
            if (k < 0) break;
            if (ctw(k) != wc) {
                continue;
            }
            // cout << i << ' ' << j << ' ' << k << endl;
            if (ctn(i) + ctn(j) + ctn(k) != tot) continue;
            int nas = diff(a , i) + diff(b , j) + diff(c , k);
            if (nas < res)  {
                res = nas;
                see(res);
                cout << i << ' ' << j << ' ' << k << ' ' << res << endl;
            }
        }
    }
    return res;
}
  
int main(){
    init();

    int a , b , c;
    char op , trash;
    cin >> a >> op >> b >> trash >> c;
    int tot = ctn(a) + ctn(b) + ctn(c) + (op == '+' ? 2 : 1);
    int ad = solve(tot ,  1 , ctw(a) , ctw(b) , ctw(c) , a , b , c);
    int su = solve(tot , -1 , ctw(a) , ctw(b) , ctw(c) , a , b , c);
    int ans ;
    if (op == '+') ans = min(ad / 2 , (su + 1) / 2);
    else           ans = min((ad + 1) / 2 , su / 2);
    printf("%d\n",ans >= INF / 4 ? -1 : ans);
    return 0;
}
