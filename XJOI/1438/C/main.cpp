#include <bitset>
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
typedef pair < int , int > pr; typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; } char nextChar(){ char r; ist>>r; return r;} }; Scanner sc(cin);
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } }
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }

const int N = 18;
int a[N];
int n;

void init() {
    scanf(I,&n);
    rep (i,n) scanf(I,&a[i]); 
}

bool g(int a, int b) {
    return (a>>b) & 1;
}

class Bit {
public:
    int a[N*N];

    Bit () { memset(a, 0, sizeof(a)); }

    void operator |= (Bit B) {
        rep (i,N*N) a[i] |= B.a[i];
    }

    Bit  operator << (int x) {
        Bit res;
        rep (i,N*N-x) res.a[i+x] = a[i];
        return res;
    }

    Bit  operator & (Bit B) {
        Bit res;
        rep (i,N*N) res.a[i] = a[i] & B.a[i];
        return res;
    }
    
    int& operator [] (int index) {
        return a[index];
    } 
};

Bit get(int x) {
    see(bitset<N>(x));
    Bit res;
    res[0] = 1;
    rep (i,n) if (g(x, i)) res |= (res << a[i]);
    return res;
}

void solve() {
    int sum=0; rep(i,n) sum += a[i];
    int ans = 0;
    ALERT(sum&1, "No Solution");
    rep (i, (1<<n)) {
        int sum0=0; rep (j,n) if(g(i,j)) sum0 += a[j];
        if ( !(sum0+sum0==sum) ) continue;
        Bit res = get(i) & get(i ^ ((1<<n)-1));
        rep (j,sum0) if (res[j] && res[sum0-j]) checkMax(ans, j*(sum0-j));
    }
    ALERT(ans==0, "No Solution");
    printf(IN,ans);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
try { 

#ifndef CUSTOM_MAIN
#ifdef MULTIPLE_TEST_CASES_WITH_T

int T; scanf("%d",&T); while(T--) {init(); solve();}

#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T

while(1) {try{init(); } catch(bool t){return 0;} solve(); }

#else

init(); solve();

#endif
#endif
#endif

} catch (const char* s) { return 0; }
    return 0;
}

