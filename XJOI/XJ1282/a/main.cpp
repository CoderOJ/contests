#define ENABLE_LL
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
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; }};
Scanner sc(cin);

const int N = 300005;
int day[N];
int n, m;

struct Arr {
    int l,r,g;
};

Arr mz[N];
multiset <int> s;
int ans=0;

void Delete(int num) {
    while (num--) {
        if (s.empty()) return;
        multiset <int> :: iterator it;
        it = --s.end();
        ans += *it;
        s.erase(it);
    }
}

void Insert(int num) {
    multiset <int> :: iterator it;
    it = s.begin();
    if (num <= *it) return;
    s.erase(it);
    s.insert(num);
}

void init() {
    scanf(II,&n,&m);
    repa (i,n) day[i] = day[i-1] + sc.nextInt();
    repa (i,m) scanf(III,&mz[i].l,&mz[i].r,&mz[i].g);
}

void solve() {
    int posl=0;int posr=0;
    repa (i,m) {
        Delete(day[mz[i].l-1] - posl + 1);
        posl=day[mz[i].l-1]+1;
        posr=day[mz[i].r];
        if (posl>posr) continue;
        if (posr-posl+1 <= (int)s.size()) Insert(mz[i].g);
        else s.insert(mz[i].g);
    }
    Delete(s.size());
    printf(IN,ans);
    return ;
}

#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
