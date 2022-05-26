#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <limits>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 200005, 205)

template <class Cmp>
struct heap_t
{
  std::priority_queue<int, std::vector<int>, Cmp> a, b;

  int64_t sum = 0;

  void insert(int x)
  {
    sum += x;
    a.emplace(x);
  }

  void erase(int x)
  {
    sum -= x;
    b.emplace(x);
  }

  int size() const
  {
    return static_cast<int>(a.size() - b.size());
  }

  bool empty() const
  {
    return size() == 0;
  }

  int top()
  {
    while (!b.empty() && a.top() == b.top())
    {
      a.pop();
      b.pop();
    }
    return a.top();
  }

  int pop()
  {
    while (!b.empty() && a.top() == b.top())
    {
      a.pop();
      b.pop();
    }
    int r = a.top();
    a.pop();
    sum -= r;
    return r;
  }
};

struct theap_t
{
  heap_t<std::greater<int>> a;
  heap_t<std::less<int>>    b;
  int                       k;

  void init(int k)
  {
    this->k = k;
  }

  void insert(int x)
  {
    a.insert(x);
    if (a.size() > k)
      b.insert(a.pop());
  }

  void erase(int x)
  {
    if (!b.empty() && x <= b.top())
    {
      b.erase(x);
    }
    else
    {
      a.erase(x);
      if (!b.empty())
        a.insert(b.pop());
    }
  }

  int64_t sum()
  {
    if (a.size() == k)
      return a.sum;
    else
      return std::numeric_limits<int64_t>::min() / 2;
  }
};

std::pair<int, int> a[N];
int                 n, k;

theap_t tp;
int     tl, tr;

void set_lr(int l, int r)
{
  see(l, r);
  while (tl > l)
    tp.insert(a[--tl].second);
  while (tr < r)
    tp.insert(a[tr++].second);
  while (tl < l)
    tp.erase(a[tl++].second);
  while (tr > r)
    tp.erase(a[--tr].second);
}

int64_t solve(int al, int ar, int bl, int br)
{
  if (al >= ar)
    return std::numeric_limits<int64_t>::min() / 2;
  else
  {
    int64_t ans = std::numeric_limits<int64_t>::min() / 2;

    int am  = al + (ar - al) / 2;
    int bml = std::max(bl, am + k), bmr = br;
    int bm = 0;

    if (std::abs(tr - bml) < std::abs(tr - bmr))
    {
      for (int i = bml; i < bmr; i++)
      {
        set_lr(am, i);
        int64_t cur = tp.sum() - (a[i - 1].first - a[am].first) * 2;
        if (cur > ans)
        {
          ans = cur;
          bm  = i;
        }
      }
    }
    else
    {
      for (int i = bmr - 1; i >= bml; i--)
      {
        set_lr(am, i);
        int64_t cur = tp.sum() - (a[i - 1].first - a[am].first) * 2;
        if (cur > ans)
        {
          ans = cur;
          bm  = i;
        }
      }
    }

    check_max(ans, solve(al, am, bl, bm + 1));
    check_max(ans, solve(am + 1, ar, bm, br));
    return ans;
  }
}

int main()
{
  n = sc.next_int();
  k = sc.next_int();
  tp.init(k);
  for (int i = 0; i < n; i++)
  {
    a[i].second = sc.next_int();
    a[i].first  = sc.next_int();
  }
  std::sort(a, a + n);
  std::cout << solve(0, n - k + 1, 1, n + 1) << std::endl;
  return 0;
}
