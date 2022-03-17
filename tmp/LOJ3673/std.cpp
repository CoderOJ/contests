#include <bits/stdc++.h>
#define pb push_back
#define lowbit(x) ((x)&(-(x)))
template <typename _Tp>void read(_Tp &x) {
  char ch(getchar());
  bool f(false);

  while (!isdigit(ch))
    f |= ch == 45, ch = getchar();

  x = ch & 15, ch = getchar();

  while (isdigit(ch))
    x = x * 10 + (ch & 15), ch = getchar();

  if (f)
    x = -x;
}
template <typename _Tp, typename... Args>void read(_Tp &t, Args &...args) {
  read(t);
  read(args...);
}
template <typename _Tp>inline void chmin(_Tp &a, const _Tp &b) {
  a = a < b ? a : b;
}
const int N = 200005, NC = (1 << 19) + 5;
typedef long long ll;
const ll INF = 4557430888798830399LL;
ll a[N], v[N];
int t[N], O[N], L[N], R[N], pool[N * 21], *P = pool;
inline int X(int i) {
  return t[i];
}
inline ll Y(int i) {
  return v[i];
}
inline ll cross(int x1, ll y1, int x2, ll y2) {
  return x1 * y2 - x2 * y1;
}
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
namespace DS1 {
struct HULL {
  int *_q, _l, _r;
  inline void init(int n) {
    _q = P, _l = 0, _r = -1, P += n;
  }
  inline void push(int i) {
    if (_l != _r + 1 && X(i) == X(_q[_r])) {
      if (Y(i) >= Y(_q[_r]))
        return;

      while (_r - _l + 1 >= 2 &&
        cross(X(i) - X(_q[_r - 1]), Y(i) - Y(_q[_r - 1]), X(_q[_r]) - X(_q[_r - 1]),
          Y(_q[_r]) - Y(_q[_r - 1])) >= 0)
        --_r;

      _q[++_r] = i;
      return;
    }

    while (_r - _l + 1 >= 2 &&
      cross(X(i) - X(_q[_r - 1]), Y(i) - Y(_q[_r - 1]), X(_q[_r]) - X(_q[_r - 1]),
        Y(_q[_r]) - Y(_q[_r - 1])) >= 0)
      --_r;

    _q[++_r] = i;
  }
  inline ll getmn(int i) {
    if (_l == _r + 1)
      return 1e18;

    while (_r - _l + 1 >= 2 &&
      -1LL * X(_q[_l])*i + Y(_q[_l]) >= -1LL * X(_q[_l + 1])*i + Y(_q[_l + 1]))
      ++_l;

    return -1LL * X(_q[_l]) * i + Y(_q[_l]);
  }
} f[NC];
void build(int l, int r, int u) {
  f[u].init(r - l + 1);

  for (int i = l; i <= r; ++i)
    f[u].push(i);

  if (l == r)
    return;

  int mid = (l + r) >> 1;
  build(l, mid, ls(u)), build(mid + 1, r, rs(u));
}
int search(int k, ll C, int l, int r, int u) {
  if (l == r)
    return l;

  int mid = (l + r) >> 1;
  ll lft = f[ls(u)].getmn(k);
  return lft <= C ? search(k, C, l, mid, ls(u)) : search(k, C, mid + 1, r, rs(u));
}
}
std::vector<int> V[N];
struct BIT {
  ll c[N];
  void add(int x, ll C) {
    for (; x < N; x += lowbit(x))
      c[x] += C;
  }
  ll ask(int x) {
    ll ans = 0;

    for (; x; x -= lowbit(x))
      ans += c[x];

    return ans;
  }
  inline ll ask(int l, int r) {
    return ask(r) - ask(l - 1);
  }
} tr1, tr2;
struct node {
  ll v;
  int t;
};
namespace DS2 {
int cnt[NC], fir[NC];
ll sum[NC], s[NC], mn[NC];
int tag1[NC];
ll tag2[NC];
inline void upd1(int u, int C) {
  tag1[u] += C, mn[u] += 1LL * C * fir[u], s[u] += 1LL * C * sum[u];
}
inline void upd2(int u, ll C) {
  tag2[u] = C, tag1[u] = 0, mn[u] = cnt[u] ? C : INF, s[u] = 1LL * C * cnt[u];
}
inline void pushdown(int u) {
  if (tag2[u] != -1)
    upd2(ls(u), tag2[u]), upd2(rs(u), tag2[u]), tag2[u] = -1;

  if (tag1[u])
    upd1(ls(u), tag1[u]), upd1(rs(u), tag1[u]), tag1[u] = 0;
}
void Modify(int x, ll C, int l, int r, int u) {
  if (!fir[u] || x < fir[u])
    fir[u] = x;

  chmin(mn[u], C), ++cnt[u], sum[u] += x, s[u] += C;

  if (l == r)
    return;

  int mid = (l + r) >> 1;
  pushdown(u);
  x <= mid ? Modify(x, C, l, mid, ls(u)) : Modify(x, C, mid + 1, r, rs(u));
}
void Update(int L, int R, ll C, int l, int r, int u) {
  if (L <= l && r <= R)
    return upd2(u, C);

  int mid = (l + r) >> 1;
  pushdown(u);

  if (L <= mid)
    Update(L, R, C, l, mid, ls(u));

  if (R > mid)
    Update(L, R, C, mid + 1, r, rs(u));

  s[u] = s[ls(u)] + s[rs(u)], mn[u] = std::min(mn[ls(u)], mn[rs(u)]);
}
ll ask(int L, int R, int l, int r, int u) {
  if (L <= l && r <= R)
    return s[u];

  int mid = (l + r) >> 1;
  pushdown(u);
  return (L <= mid ? ask(L, R, l, mid, ls(u)) : 0) + (R > mid ? ask(L, R, mid + 1,
        r, rs(u)) : 0);
}
int search(ll C, int l, int r, int u) {
  if (l == r)
    return l;

  int mid = (l + r) >> 1;
  pushdown(u);

  if (mn[rs(u)] < C)
    return search(C, mid + 1, r, rs(u));
  else
    return search(C, l, mid, ls(u));
}
}
int main() {
  memset(DS2::tag2, -1, sizeof(DS2::tag2)), memset(DS2::mn, 63, sizeof(DS2::mn));
  int n, q;
  read(n, q);

  for (int i = 1; i <= n; ++i)
    read(a[i]);

  int cur = 0, pos = 0;

  for (int i = 1, opt; i <= q; ++i) {
    read(opt), O[i] = opt;

    if (opt == 1)
      ++pos, read(v[pos]), t[pos] = cur;
    else if (opt == 2)
      ++cur;
    else if (opt == 3)
      read(L[i], R[i]);
  }

  if (pos) {
    DS1::build(1, pos, 1);

    for (int i = 1; i <= n; ++i)
      if (DS1::f[1].getmn(i) <= a[i])
        V[DS1::search(i, a[i], 1, pos, 1)].pb(i);
  }

  for (int i = 1; i <= n; ++i)
    tr1.add(i, a[i]), tr2.add(i, i);

  int POS = 0;
  cur = 0;

  for (int i = 1; i <= q; ++i) {
    if (O[i] == 1) {
      ++POS;
      int p = DS2::mn[1] >= v[POS] ? 0 : DS2::search(v[POS], 1, n, 1);

      if (p < n)
        DS2::Update(p + 1, n, v[POS], 1, n, 1);

      for (auto i : V[POS])
        tr1.add(i, -a[i]), tr2.add(i, -i), DS2::Modify(i, v[POS], 1, n, 1);
    } else if (O[i] == 2)
      ++cur, DS2::upd1(1, 1);
    else {
      int l = L[i], r = R[i];
      printf("%lld\n", tr1.ask(l, r) + tr2.ask(l, r)*cur + DS2::ask(l, r, 1, n, 1));
    }
  }

  return 0;
}