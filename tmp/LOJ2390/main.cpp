#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <limits>
#include <queue>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

template <class Cmp>
struct que_t
{
  std::vector<std::pair<int64_t, int>> que;
  size_t                               ql = 0;

  int l = 0, r = 0;

  que_t(size_t n)
  {
    que.reserve(n);
  }

  void push(int64_t x)
  {
    while (que.size() > ql && Cmp()(que.back().first, x))
      que.pop_back();
    que.emplace_back(x, r++);
  }

  void pop()
  {
    if (que[ql].second == l)
      ql++;
    l++;
  }

  int64_t max()
  {
    return que[ql].first;
  }
};

CONSTRAINT(N, 305, 20)

std::pair<int64_t, int64_t> a[N];

int64_t r, c;
int     n;

int64_t ml[N][N], mr[N][N], mg[N][N];

void init()
{
  for (int i = 0; i < n; i++)
  {
    ml[i][i] = std::numeric_limits<int64_t>::max();
    mr[i][i] = std::numeric_limits<int64_t>::max();
    mg[i][i] = std::numeric_limits<int64_t>::max();
    std::set<int64_t>      s{-1, c};
    std::multiset<int64_t> sg{c};
    for (int j = i; j < n; j++)
    {
      ml[i][j + 1] = std::min(ml[i][j], a[j].second);
      mr[i][j + 1] = std::min(mr[i][j], c - a[j].second - 1);

      auto [it, vl] = s.insert(a[j].second);
      if (vl)
      {
        if (it != s.begin())
          sg.insert(a[j].second - *std::prev(it) - 1);
        if (std::next(it) != s.end())
          sg.insert(*std::next(it) - a[j].second - 1);
        if (it != s.begin() && std::next(it) != s.end())
          sg.erase(sg.find(*std::next(it) - *std::prev(it) - 1));
      }

      mg[i][j + 1] = *sg.rbegin();
    }
  }
}

int64_t solve(int64_t rw)
{
  struct info_t
  {
    int64_t pos;
    int64_t ml, mr, mg;
  };

  std::vector<info_t> p;
  int64_t             pos = -1;
  for (int l = 0, r = 0; l != n;)
  {
    if (r == n || a[l].first + rw < a[r].first)
    {
      pos = a[l].first + rw;
      l++;
    }
    else
    {
      pos = a[r].first;
      r++;
    }

    if (l == r && l != n)
      return std::numeric_limits<int64_t>::max();

    // see(l, r, pos, ml[l][r], mr[l][r], mg[l][r]);
    if (!p.empty() && p.back().pos == pos)
      p.pop_back();
    p.push_back({pos, ml[l][r], mr[l][r], mg[l][r]});
  }

  int64_t ans = std::numeric_limits<int64_t>::max();

  que_t<std::less<int64_t>> ql(p.size());
  que_t<std::less<int64_t>> qr(p.size());
  que_t<std::less<int64_t>> qg(p.size());
  auto                      it_end = std::prev(p.end());
  for (auto itl = p.begin(), itr = itl; itl != it_end; itl++)
  {
    while (itr != it_end && (itl == itr || itr->pos - itl->pos < r))
    {
      ql.push(itr->ml);
      qr.push(itr->mr);
      qg.push(itr->mg);
      itr++;
    }
    if (itr->pos - itl->pos >= r)
    {
      see(itl->pos, itr->pos, qg.max(), ql.max(), qr.max());
      check_min(ans, std::max(qg.max(), ql.max() + qr.max()));
    }
    ql.pop();
    qr.pop();
    qg.pop();
  }

  see(ans);
  if (ans == std::numeric_limits<int64_t>::max())
    return ans;
  else
    return ans + (rw - 1);
}

int main()
{
  r = sc.next_int();
  c = sc.next_int();
  n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    a[i].first  = sc.next_int() - 1;
    a[i].second = sc.next_int() - 1;
  }
  std::sort(a, a + n);
  a[n].first = std::numeric_limits<int64_t>::max();
  init();

  int64_t ans = std::numeric_limits<int64_t>::max();

  std::vector<int64_t> vals;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      vals.push_back(a[j].first - a[i].first + 1);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      vals.push_back(a[i].first + (r - a[j].first - 1) + 1);
  for (int i = 0; i + 1 < n; i++)
    vals.push_back(a[i + 1].first - a[i].first);
  vals.push_back(r);

  std::sort(vals.begin(), vals.end());
  vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
  see(vals);

  int64_t best_key = 0;
  for (int64_t i : vals)
    if (check_min(ans, solve(i)))
      best_key = i;
  for (int64_t i = std::max(0l, best_key - 10); i <= best_key + 10; i++)
    check_min(ans, solve(i));

  std::cout << ans << std::endl;

  return 0;
}
