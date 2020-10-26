#include <algorithm>
#include <iostream>
#include <cstdio>
#define LL long long
#define lson (k << 1)
#define rson ((k << 1) | 1)
using namespace std;
int n, q, pos, val;
const int N = 100010;
int tr[N << 2];
inline int read() {
    int res = 0;
    char ch = getchar();
    bool XX = false;
    for (; !isdigit(ch); ch = getchar()) (ch == '-') && (XX = true);
    for (; isdigit(ch); ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ 48);
    return XX ? -res : res;
}
int GCD(int a, int b) { return b ? GCD(b, a % b) : a; }
void pushup(int k) { tr[k] = GCD(tr[lson], tr[rson]); }
void build(int k, int l, int r) {
    if (l == r) {
        tr[k] = read();
        return;
    }
    int mid = (l + r) >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    pushup(k);
}
void change(int k, int l, int r, int pos, int v) {
    if (l == r) {
        tr[k] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        change(lson, l, mid, pos, v);
    else
        change(rson, mid + 1, r, pos, v);
    pushup(k);
}
int find(int k, int l, int r, int a, int b) {
    if (l == r)
        return l;
    int x = GCD(a, tr[lson]), y = GCD(b, tr[rson]), mid = (l + r) >> 1;
    if (x <= y)
        return find(lson, l, mid, a, y);
    else
        return find(rson, mid + 1, r, x, b);
}
LL suan1(int k, int l, int r, int pos, int v) {
    if (l == r)
        return GCD(tr[k], v);
    int a = GCD(tr[rson], v), b = GCD(tr[lson], a), mid = (l + r) >> 1;
    if (pos <= mid)
        return suan1(lson, l, mid, pos, a);
    else if (a == b)
        return (LL)(mid - l + 1) * a + suan1(rson, mid + 1, r, pos, v);
    else
        return suan1(lson, l, mid, pos, a) + suan1(rson, mid + 1, r, pos, v);
}
LL suan2(int k, int l, int r, int pos, int v) {
    if (l == r)
        return GCD(tr[k], v);
    int a = GCD(tr[lson], v), b = GCD(tr[rson], a), mid = (l + r) >> 1;
    if (mid + 1 <= pos)
        return suan2(rson, mid + 1, r, pos, a);
    else if (a == b)
        return (LL)suan2(lson, l, mid, pos, v) + (LL)(r - mid) * a;
    else
        return suan2(lson, l, mid, pos, v) + suan2(rson, mid + 1, r, pos, a);
}
int main() {
    cin >> n >> q;
    build(1, 1, n);
    while (q--) {
        pos = read();
        val = read();
        change(1, 1, n, pos, val);
        pos = find(1, 1, n, 0, 0);
        printf("%lld\n", suan1(1, 1, n, pos, 0) + suan2(1, 1, n, pos, 0) - tr[1]);
    }
    return 0;
}
