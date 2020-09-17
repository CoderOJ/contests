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

const int N = 20;
const string keys[N] = {"3","4","5","6","7","8","9","10","J","Q","K","A","2"};
map < string, int > conv;

struct State {
    int a[13];
    State () { memset(a,0,sizeof(a)); }

    int size() {
        int res=0; rep (i,13) res += a[i];
        return res;
    }

    bool adj(int l, int r) {
        repi (i,l,r-1) if (!a[i]) return 0;
        return 1;
    }

    State dec(int l, int r) {
        State res = *this;
        repi (i,l,r-1) res.a[i] --;
        return res;
    }

    int countSingle() {
        int res=0; rep (i,13) res+= (a[i]==1);
        return res;
    }

    int countCouple() {
        int res=0; rep (i,13) res+= (a[i]==3);
        return res;
    }

    int countTriple() {
        int res=0; rep (i,13) res+= (a[i]==4);
        return res;
    }
};

State origin;

void init() {
    rep (i,13) conv[ keys[i] ] = i;
    int n = sc.nextInt();
    rep (i,n) origin.a[ conv[sc.next()] ]++;
}

bool jury(State u) {
    if (u.size()<=1) return 1;
    if (u.countSingle() <= u.countCouple() + 2*u.countTriple() + 1) return 1;
    repi (s,0,11) repi (t,s+5,12) {
        if (u.adj(s,t)) if (jury(u.dec(s,t))) return 1;
    }
    return 0;
}

void solve() {
    puts(jury(origin) ? "Yes" : "No" );
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
