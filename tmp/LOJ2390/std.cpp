#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>

template<typename T> bool ckmax(T &a, const T &b) {
  return b > a ? a = b, 1 : 0;
}
template<typename T> bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}

using ll = long long;

const int MN = 3e2 + 10;
const int INF = 0x3f3f3f3f;
const ll INFL = 0x3f3f3f3f3f3f3f3f;

struct pt {
public:
  int x, y;
  void in() {
    scanf("%d%d", &x, &y);
  }
  bool operator < (const pt &o) const {
    return y < o.y || !(o.y < y) && x < o.x;
  }
};
struct dat {
public:
  int l, r, m;
  dat &operator += (const dat &o) {
    return ckmax(l, o.l), ckmax(r, o.r), ckmax(m, o.m), *this;
  }
  bool ok() {
    return l < INF && r < INF && m < INF;
  }
  int operator()() const {
    return std::max(l + r, m);
  }
};
struct event {
public:
  int t;
  dat v;
  bool operator > (const event &o) const {
    return t > o.t;
  }
};

int R, C, N, U, D;
ll ans = INFL;
pt a[MN];
dat v[MN][MN];
std::vector<event> t;

int main() {
  scanf("%d%d%d", &R, &C, &N);

  for (int i = 0; i < N; ++i)
    a[i].in();

  std::sort(a, a + N);

  for (int i = 0; i < N; ++i) {
    std::multiset<int> q;
    int m = -1;

    for (int j = i; j < N; ++j)
      q.insert(a[j].x);

    for (auto nx = q.begin(), it = nx++; nx != q.end(); it = nx++)
      ckmax(m, *nx - *it - 1);

    for (int j = N - 1; j >= i; --j) {
      v[i][j + 1] = {*q.begin() - 1, R - *std::prev(q.end()), m};
      auto it = q.erase(q.find(a[j].x));

      if (it != q.begin() && it != q.end())
        ckmax(m, *it - *std::prev(it) - 1);
    }

    v[i][i] = {INF, INF, INF};
  }

  v[N][N] = {INF, INF, INF};

  for (int i = 0; i + 1 < N; ++i)
    if (a[i].y < a[i + 1].y) {
      for (int j = i + 1; j < N; ++j)
        if (a[j].y > a[j - 1].y)
          t.push_back({a[j].y - a[i].y - 1, v[i + 1][j]}); //t is the last moment of time, before this new (worse) thing takes over
    }

  std::sort(t.begin(), t.end(), std::greater<event>());

  for (int i = 0, j; i < N; i = j) {
    for (j = i + 1; j < N && a[i].y == a[j].y; ++j);

    dat val = v[0][j];
    U = a[i].y - 1; //sliding window perspective. AKA. U = U, D = U+D (shift)

    for (int k = 0, id = 0; k < N || id < t.size();) {
      D = -1;

      if (k < N)
        ckmax(D, C + U - a[k].y);

      if (id < t.size())
        ckmax(D, t[id].t);

      if (val.ok())
        ckmin(ans, (ll)std::max(U, D) + val());

      if (k < N && D == C + U - a[k].y)
        val += v[k + 1][N], ++k;

      if (id < t.size() && D == t[id].t)
        val += t[id].v, ++id;
    }

    if (val.ok())
      ckmin<ll>(ans, U + val());
  }

  printf("%lld\n", ans);
  return 0;
}