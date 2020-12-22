#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
typedef pair<int, int> pii;
int n, L, p, t[N], opt[N], best;
int mx[N << 2], mi[N << 2], tag[N << 2];
pii px[N];
char s[10];
int
solve(int T)
{
  int l = p, r = p;
  for (int i = n; i >= 1; i--) {
    if (T < t[i] - t[i - 1])
      continue;
    if (opt[i]) {
      if (r == L) {
        l--;
        l = max(l, 0);
      } else {
        l--;
        r--;
        l = max(l, 0);
      }
    } else {
      if (l == 0) {
        r++;
        r = min(r, L);
      } else {
        l++;
        r++;
        r = min(r, L);
      }
    }
    if (l > r)
      return -1;
  }
  return r;
}
void
up(int x)
{
  mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
  mi[x] = min(mi[x << 1], mi[x << 1 | 1]);
}
void
upnd(int x, int k)
{
  mx[x] += k;
  mi[x] += k;
  tag[x] += k;
}
void
push_down(int x)
{
  upnd(x << 1, tag[x]);
  upnd(x << 1 | 1, tag[x]);
  tag[x] = 0;
}
void
build(int x, int l, int r)
{
  if (l == r) {
    mx[x] = mi[x] = p;
    return;
  }
  int mid = (l + r) >> 1;
  tag[x] = 0;
  build(x << 1, l, mid);
  build(x << 1 | 1, mid + 1, r);
  up(x);
}
void
update(int x, int l, int r, int L, int R, int k)
{
  if (L > r || l > R)
    return;
  if (L <= l && r <= R) {
    upnd(x, k);
    return;
  }
  int mid = (l + r) >> 1;
  push_down(x);
  update(x << 1, l, mid, L, R, k);
  update(x << 1 | 1, mid + 1, r, L, R, k);
  up(x);
}
int
get_l(int x, int l, int r, int R)
{
  if (l > R)
    return 0;
  if (mi[x] > 0)
    return 0;
  if (l == r)
    return l;
  int t, mid = (l + r) >> 1;
  push_down(x);
  t = get_l(x << 1 | 1, mid + 1, r, R);
  if (!t)
    t = get_l(x << 1, l, mid, R);
  return t;
}
int
get_r(int x, int l, int r, int R)
{
  // cout<<x<<' '<<mx[x]<<'\n';
  if (l > R)
    return 0;
  if (mx[x] < L)
    return 0;
  if (l == r)
    return l;
  int t, mid = (l + r) >> 1;
  push_down(x);
  t = get_r(x << 1 | 1, mid + 1, r, R);
  if (!t)
    t = get_r(x << 1, l, mid, R);
  return t;
}
int
get_bl(int x, int l, int r, int R)
{
  if (l > R)
    return 0;
  if (mi[x] >= 0)
    return 0;
  if (l == r)
    return l;
  int t, mid = (l + r) >> 1;
  push_down(x);
  t = get_bl(x << 1 | 1, mid + 1, r, R);
  if (!t)
    t = get_bl(x << 1, l, mid, R);
  return t;
}
int
get_br(int x, int l, int r, int R)
{
  if (l > R)
    return 0;
  if (mx[x] <= L)
    return 0;
  if (l == r)
    return l;
  int t, mid = (l + r) >> 1;
  push_down(x);
  t = get_br(x << 1 | 1, mid + 1, r, R);
  if (!t)
    t = get_br(x << 1, l, mid, R);
  return t;
}
namespace baoli {
pii Ans;
void
solve()
{
  if (::solve(1000000001) != -1) {
    puts("infinity");
    return;
  }
  for (int i = t[n]; i >= 0; i--) {
    for (int j = L; j >= 0; j--) {
      int pos = j;
      for (int k = 1; k <= n; k++) {
        if (t[k] >= t[k - 1] + i + 1)
          continue;
        if (opt[k])
          pos++, pos = min(L, pos);
        else
          pos--, pos = max(0, pos);
      }
      if (pos == p)
        return (void)(cout << i << ' ' << j << '\n');
    }
  }
}
}
int
main()
{
  // srand(time(0));
  scanf("%d%d%d", &n, &L, &p);
  px[n + 1].first = -1;
  t[0] = -1000000010;
  best = -1;
  build(1, 1, n);
  for (int i = 1; i <= n; i++) {
    scanf("%s%d", s, &t[i]);
    opt[i] = (s[0] == '+');
    px[i] = std::make_pair(t[i] - t[i - 1], i);
  } 
  if (solve(1000000001) != -1) {
    puts("infinity");
    return 0;
  }
  sort(px + 1, px + 1 + n);
  for (int i = 1; i <= n; i++) {
    int t_l = get_l(1, 1, n, n);
    int t_r = get_r(1, 1, n, n);
    if (t_l == 0 && t_r == 0)
      best = max(best, px[i].first - 1);
    else if (t_l > t_r) {
      int lim = get_bl(1, 1, n, t_l);
      if (lim == 0)
        best = max(best, px[i].first - 1);
      else {
        if (t_r > lim)
          best = max(best, px[i].first - 1);
      }
    } else {
      //先到L
      int lim = get_br(1, 1, n, t_r);

      if (lim == 0)
        best = max(best, px[i].first - 1);
      else {
        if (t_l > lim)
          best = max(best, px[i].first - 1);
      }
    }
    // change
    int pos = i;
    while (pos < n && px[pos + 1].first == px[pos].first)
      pos++;
    for (int j = i; j <= pos; j++) {
      if (opt[px[j].second])
        update(1, 1, n, 1, px[j].second, -1);
      else
        update(1, 1, n, 1, px[j].second, 1);
    }
    i = pos;
  }
  printf("%d %d\n", best, solve(best));
  return 0;
}
