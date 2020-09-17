#include <bits/stdc++.h>
using namespace std;

#ifdef ENABLE_LL
#define int long long
#endif

#define rep(i,n) for (int i=0;i<(int)(n);i++)
#define repa(i,n) for (int i=1;i<=(int)(n);i++)
#define repb(i,a,b) for (int i=a;i>=b;i--)
#define repi(i,a,b) for (int i=a;i<=b;i++)
#define repe(i,v) for (int i=0;i<(int)(v.size());i++)

#ifdef __LL
#define see(x) cout << #x << "=" << x << endl
#define ses(x) cout << #x << "=" << x << " "
#else
#define see(x)
#define ses(x)
#endif

#define L first
#define R second
template <class T> bool checkMin(T& a, T b) { return (a>b) ? (a=b,1) : (0); }
template <class T> bool checkMax(T& a, T b) { return (a<b) ? (a=b,1) : (0); }


inline char read() {
static const int IN_LEN = 1000000;
static char buf[IN_LEN], *s, *t;
return (s==t?t=(s=buf)+fread(buf,1,IN_LEN,stdin),(s==t?-1:*s++):*s++);
}
template <class T>
inline void read(T &x) {
static bool iosig;
static char c;
for (iosig=false, c=read(); !isdigit(c); c=read()) {
if (c == '-') iosig=true;
if (c == -1) return;
}
for (x=0; isdigit(c); c=read()) x=((x+(x<<2))<<1)+(c^'0');
if (iosig) x=-x;
}
const int OUT_LEN = 10000000;
char obuf[OUT_LEN], *ooh = obuf;
inline void print(char c) {
if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
*ooh++ = c;
}
template <class T>
inline void print(T x) {
static int buf[30], cnt;
if (x == 0) print('0');
else {
if (x < 0) print('-'), x = -x;
for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
while (cnt) print((char)buf[cnt--]);
}
}
inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }

const int N = 5000005;
int o[N], a[N];
int s[N], b[N];
int n;

void init() {
    read(n);
    rep (i,n) { read(o[i]); read(a[i]); }
    rep (i,n) s[i] = a[i];
    s[n] = 0; s[n+1] = 100000001;
    sort(s, s+n+2);
    b[0] = b[n+1] = 1;
    rep (i,n) a[i] = lower_bound(s, s+n+2, a[i]) - s;
}

void solve() {
    rep (i,n) {
        if (o[i] == 1) b[ a[i] ]=1;
        else if (o[i] == 2) {
            while (b[--a[i]] == 0) {}
            print( s[ a[i] ] ); print('\n');
        }else {
            while (b[++a[i]] == 0) {}
            print( s[ a[i] ] ); print('\n');
        }
    }
}

#ifdef ENABLE_LL
#undef int
#endif
int main() {
#ifdef ENABLE_LL
#define int long long
#endif
    init();
    solve();
    flush();
    return 0;
}
