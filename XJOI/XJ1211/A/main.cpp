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
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a < b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a > b ? a=b,1 : 0); }

typedef map < string , int > Dir;

struct Node {
    Dir d;
    Node() {d.clear(); }
};
Node dir[105];

int cnt;
int n;
const int R = 0;

int insert(int pos, string s) {
    if (!dir[pos].d.count(s)) dir[pos].d[s] = cnt++;
    return dir[pos].d[s];
}

void init() {
    cnt = 1;
    scanf(I,&n);
    rep (i,n) {
        string f; 
        cin >> f;
        string pos;
        int u = R;
        foreach(i,f) {
            if (f[i] == '/') {
                u = insert(u,pos);
                pos = "";
            } else {
                pos += f.substr(i,1);
            }
        }
        insert(u,pos);
    }
}

typedef Dir::iterator It;
void print(int dep , int pos) {
    for (It it=dir[pos].d.begin(); it!=dir[pos].d.end(); it++) {
        if (it->first == "") continue;
        rep (i,dep) {
            putchar('|');
            rep (_,4) putchar((i == dep - 1) ? '-' : ' ');
        }
        cout << it->first << endl;
        print(dep + 1 , it->second);
    }
}

void solve() {
    print(0,R);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
