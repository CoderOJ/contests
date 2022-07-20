#include<bits/stdc++.h>
#define lch (i << 1)
#define rch ((i << 1) | 1)
using namespace std;
const int mn = 200005, mod = 1e9 + 7;
struct node{
    int x, v;
    bool operator <(const node p) const{return v < p.v;}
}a[mn];
struct seg{
    int x, p;
    bool operator <(const seg b) const {return x < b.x;}
}h[mn];
struct range{
    int l, r;
    bool operator <(const range x) const{return r == x.r ? l < x.l : r < x.r;}
}rng[mn];
int mins[mn << 2], maxs[mn << 2], f[mn << 2];
void modify(int i, int L, int R, int p, int x)
{
    if(L == R)
    {
        mins[i] = maxs[i] = x;
        f[i] += x, f[i] %= mod;
        return;
    }
    int mid = (L + R) >> 1;
    if(p <= mid) modify(lch, L, mid, p, x);
    else modify(rch, mid + 1, R, p, x);
    mins[i] = min(mins[lch], mins[rch]);
    maxs[i] = max(maxs[lch], maxs[rch]);
    f[i] = (f[lch] + f[rch]) % mod;
}
int get_min(int i, int L, int R, int l, int r)
{
    if(L == l && R == r)
        return mins[i];
    int mid = (L + R) >> 1;
    if(r <= mid) return get_min(lch, L, mid, l, r);
    else if(l > mid) return get_min(rch, mid + 1, R, l, r);
    else return min(get_min(lch, L, mid, l, mid), get_min(rch, mid + 1, R, mid + 1, r));
}
int get_max(int i, int L, int R, int l, int r)
{
    if(L == l && R == r)
        return maxs[i];
    int mid = (L + R) >> 1;
    if(r <= mid) return get_max(lch, L, mid, l, r);
    else if(l > mid) return get_max(rch, mid + 1, R, l, r);
    else return max(get_max(lch, L, mid, l, mid), get_max(rch, mid + 1, R, mid + 1, r));
}
int get_sum(int i, int L, int R, int l, int r)
{
    if(L == l && r == R) return f[i];
    int mid = (L + R) >> 1;
    if(r <= mid) return get_sum(lch, L, mid, l, r);
    else if(l > mid) return get_sum(rch, mid + 1, R, l, r);
    else return (get_sum(lch, L, mid, l, mid) + get_sum(rch, mid + 1, R, mid + 1, r)) % mod;
}
int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].x, &a[i].v), h[i] = (seg) {a[i].x, i};
    sort(h + 1, h + 1 + n);
    for(int i = 1; i <= n; i++)
        a[h[i].p].x = i;
    sort(a + 1, a + n + 1);
    memset(mins, 0x3f, sizeof mins);
    for(int i = 1; i <= n; i++)
    {
        if(a[i].x + 1 <= n)
            rng[i].l = get_min(1, 1, n, a[i].x + 1, n);
        else rng[i].l = i;
        rng[i].l = min(rng[i].l, i);
        modify(1, 1, n, a[i].x, i);
    }
    memset(maxs, 0, sizeof maxs);
    for(int i = n; i; i--)
    {
        if(a[i].x - 1 >= 1) rng[i].r = get_max(1, 1, n, 1, a[i].x - 1);
        else rng[i].r = i;
        rng[i].r = max(rng[i].r, i);
        modify(1, 1, n, a[i].x, i);
    }
    memset(f, 0, sizeof f);
    sort(rng + 1, rng + 1 + n);
    int ans = 0;
    for(int i = n; i; i--)
    {
        int tmp = 0;
        if(rng[i].r == n) ++tmp;
        tmp += get_sum(1, 1, n, 1, min(rng[i].r + 1, n));
        tmp %= mod;
        modify(1, 1, n, rng[i].l, tmp);
        if(rng[i].l == 1) ans += tmp, ans %= mod;
    }
    printf("%d\n", ans);
}
