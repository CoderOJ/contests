#include <bits/stdc++.h>

int read_int()
{
  int c = getchar();
  while (!std::isdigit(c))
    c = getchar();
  int r = 0;
  while (std::isdigit(c))
  {
    r = r * 10 + (c - '0');
    c = getchar();
  }
  return r;
}

const int N = 500005;

struct node_t
{
  int t, p;
  int x, y;
};

node_t p[N];
int n;

void disassociate_y()
{
  std::vector<int> ys;
  for (int i = 0; i < n; i++)
    ys.push_back(p[i].y);
  std::sort(ys.begin(), ys.end());
  for (int i = 0; i < n; i++)
    p[i].y = static_cast<int>(std::lower_bound(ys.begin(), ys.end(), p[i].y) - ys.begin());
}

struct bit_t
{
  int64_t a[N];

  void check_max(int p, int64_t v)
  {
    p += 1;
    for (; p < N; p += p & -p)
      a[p] = std::max(a[p], v);
  }

  int64_t max(int p)
  {
    p += 1;
    int64_t res = 0;
    for (; p; p -= p & -p)
      res = std::max(res, a[p]);
    return res;
  }
};

bit_t pre;
int64_t dp[N];
std::vector<std::pair<int, int64_t>> st[N];

int main()
{
  n = read_int();
  for (int i = 0; i < n; i++)
  {
    p[i].p = read_int();
    p[i].t = read_int();
    p[i].x = p[i].t + p[i].p;
    p[i].y = p[i].t - p[i].p;
  }
  disassociate_y();

  std::vector<int> x_id(n);
  for (int i = 0; i < n; i++) x_id[i] = i;
  std::stable_sort(x_id.begin(), x_id.end(), [](int x, int y) {
    return p[x].x != p[y].x ? p[x].x < p[y].x : p[x].y < p[y].y;
  });

  for (int i : x_id)
  {
    // printf("p[%d] = (%d, %d)\n", i, p[i].x, p[i].y);

    dp[i] = pre.max(p[i].y) + 1;
    if (i - 1 >= 0 && p[i - 1].x <= p[i].x && p[i - 1].y <= p[i].y)
    {
      st[i] = std::move(st[i - 1]);
      auto eval = [&](std::pair<int, int64_t> p) -> int64_t {
        return 1ll * (-2 * i) * p.first + p.second + 1ll * i * i;
      };
      while (st[i].size() >= 2)
      {
        int64_t val_i = eval(st[i][st[i].size() - 1]);
        int64_t val_ii = eval(st[i][st[i].size() - 2]);
        if (val_ii >= val_i) st[i].pop_back();
        else break;
      }
      dp[i] = std::max(dp[i], eval(st[i].back()));
    }
    int cx = i - 1;
    int64_t cy = dp[i] - 1 + 1ll * (i - 1) * (i - 1);
    while (st[i].size() >= 2)
    {
      const auto [ppx, ppy] = st[i][st[i].size() - 2];
      const auto [px, py] = st[i][st[i].size() - 1];
      if ((cy - py) * (px - ppx) > (py - ppy) * (cx - px)) st[i].pop_back();
      else break;
    }
    st[i].emplace_back(cx, cy);

    pre.check_max(p[i].y, dp[i]);
    // printf("dp[%d] = %ld\n", i, dp[i]);
  }

  std::cout << *std::max_element(dp, dp + n) << std::endl;

  return 0;
}
