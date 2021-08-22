#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <vector>
#define setIO(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define closefile fclose(stdin), fclose(stdout)
#define m_p make_pair
#define sz(x) (int)x.size()
#define see(x)
#define seeln(x) 
#define out(x) 
#define outln(x)
#define outarr(x, l, r)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define gc() getchar()
//#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
template <class T> void read(T &x)
{
    x = 0; int c = gc(); int flag = 0;
    while (c < '0' || c > '9') flag |= (c == '-'), c = gc();
    while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
    if (flag) x = -x;
}
template <class T> bool checkmax(T &a, T b){return a < b ? a = b, 1 : 0;}
template <class T> bool checkmin(T &a, T b){return b < a ? a = b, 1 : 0;}
#define e0 first
#define e1 second
const int N = 1005;
int n;
int x[N], y[N], used[N];
ll gcd(ll a, ll b){return b ? gcd(b, a % b) : a;}
struct node
{
    int x, y, id;
    node(int x = 0, int y = 0, int id = 0):x(x), y(y), id(id){}
    bool operator < (const node &rhs) const
    {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }
}seq[N];
 
void init()
{
    scanf("%d", &n);
    int sx = 0, sy = 0;
    for (int i = 1; i <= n; ++i)
    {
        used[i] = 0;
        scanf("%d%d", &x[i], &y[i]);
        sx += x[i], sy += y[i];
    }
    int pn = 0;
    for (int i = 1; i <= n; ++i)
    {
        int X = x[i] * n - sx, Y = y[i] * n - sy;
        if (X == 0 && Y == 0) used[i] = 1;
        seq[++pn] = node(X, Y, i);
    }
    map<pii, vector<int>> Map;
    for (int i = 1; i <= pn; ++i)
    {
        if (seq[i].x < 0 || (seq[i].x == 0 && seq[i].y < 0)) Map[m_p(seq[i].x, seq[i].y)].push_back(seq[i].id);
    }
    for (int i = 1; i <= pn; ++i)
    {
        if (seq[i].x > 0 || (seq[i].x == 0 && seq[i].y > 0))
        {
            vector<int> &w = Map[m_p(-seq[i].x, -seq[i].y)];
            if (!w.empty())
            {
                used[i] = used[w.back()] = 1;
                w.pop_back();
            }
        }
    }
    int m = 0;
    for (int i = 1; i <= n; ++i) if (!used[i]) x[++m] = x[i], y[m] = y[i];
    n = m;
}
 
__int128 a[N];
bool check(pll K)
{
    for (int i = 1; i <= n; ++i) a[i] = (__int128)x[i] * K.e1 + (__int128)y[i] * K.e0;
    sort(a + 1, a + n + 1);
    //for (int i = 1; i <= n; ++i) printf("%lld ", (ll)a[i]); printf("\n");
    if (n & 1)
    {
        __int128 p = a[(n + 1) / 2] * 2;
        for (int i = 1; i <= n / 2; ++i) if (a[i] + a[n + 1 - i] != p) return 0;
        return 1;
    }
    else
    {
        __int128 p = a[1] + a[n];
        for (int i = 1, j = n; i <= j; ++i, --j) if (a[i] + a[j] != p) return 0;
        return 1;
    }
}
 
bool checkinf()
{
    for (int i = 1; i <= n; ++i) a[i] = y[i];
    sort(a + 1, a + n + 1);
    if (n & 1)
    {
        __int128 p = a[(n + 1) / 2] * 2;
        for (int i = 1; i <= n / 2; ++i) if (a[i] + a[n + 1 - i] != p) return 0;
        return 1;
    }
    else
    {
        __int128 p = a[1] + a[n];
        for (int i = 1, j = n; i <= j; ++i, --j) if (a[i] + a[j] != p) return 0;
        return 1;
    }
}
 
void solve()
{
    if (n <= 2)
    {
        printf("-1\n");
        return;
    }
    int sx = 0, sy = 0;
    for (int i = 1; i <= n; ++i) sx += x[i], sy += y[i];
    map<pll, int> Map;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            ll A = sx + sx - (ll)n * (x[i] + x[j]), B = (ll)n * (y[i] + y[j]) - sy - sy;
            if (B == 0) continue;
            ll g = gcd(abs(A), abs(B));
            A /= g, B /= g;
            if (A == 0) B = 1;
            else if (A < 0) A = -A, B = -B;
            Map[m_p(A, B)]++;
        }
    }
    int ans = 0;
    for (auto &p : Map)
    {
        if (p.second >= n / 2)
        {
            if (check(p.first)) ++ans;
        }
    }
    if (checkinf()) ++ans;
    printf("%d\n", ans);
}
 
int main()
{
    //setIO("");
    int t; scanf("%d", &t); while (t--)
    {
        init();
        solve();
    }
    return 0;
}
