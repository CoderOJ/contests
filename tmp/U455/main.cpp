#include <bits/stdc++.h>

const int64_t INF = 1e15;
const int N = 100005;
int64_t x[N], y[N], w[N], c[N];
int n, m;

struct node_t
{
  int64_t w;
  mutable int64_t c;
};

struct node_cmp_w
{
  bool operator()(node_t lhs, node_t rhs) const
  {
    return lhs.w > rhs.w;
  }
};

std::priority_queue<node_t, std::vector<node_t>, node_cmp_w> que_a;
std::priority_queue<node_t, std::vector<node_t>, node_cmp_w> que_b;
int64_t ans = 0;

void add_a(int64_t x)
{
  int64_t cur = INF;
  if (!que_b.empty())
  {
    cur = que_b.top().w + x;
    que_b.top().c -= 1;
    if (que_b.top().c == 0)
      que_b.pop();
  }
  ans += cur;
  que_a.push({-cur - x, 1});
}

void add_b(int64_t y, int64_t w, int64_t c)
{
  int cnt = 0;
  while (!que_a.empty() && cnt < c)
  {
    const auto &[tw, tc] = que_a.top();
    int64_t cur = tw + y + w;
    if (cur < 0)
    {
      int64_t cur_cnt = std::min(tc, c - cnt);
      cnt += cur_cnt;
      ans += cur * cur_cnt;
      que_a.top().c -= cur_cnt;
      if (que_a.top().c == 0)
        que_a.pop();
      que_b.push({-cur - y + w, cur_cnt});
    }
    else break;
  }
  if (cnt > 0) que_a.push({-y - w, cnt});
  if (c - cnt > 0) que_b.push({-y + w, c - cnt});
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) 
  {
    scanf("%" SCNi64, &x[i]);
  }
  int64_t cnt_b = 0;
  for (int i = 0; i < m; i++) 
  {
    scanf("%" SCNi64 "%" SCNi64 "%" SCNi64, &y[i], &w[i], &c[i]);
    cnt_b += c[i];
  }
  if (cnt_b < n)
  {
    puts("-1");
  }
  else
  {
    int ia = 0, ib = 0;
    while (ia < n || ib < m)
    {
      if (ia < n && (ib == m || x[ia] < y[ib])) add_a(x[ia]), ia++;
      else add_b(y[ib], w[ib], c[ib]), ib++;
    }
    printf("%" SCNi64 "\n", ans);
  }
  return 0;
}
