#include <bits/stdc++.h>

const int N = 100005;
int       a[N], b[N], n, m;

struct theap_t
{
  std::multiset<int> su, sd;
  int64_t            su_sum = 0;

  template <class InputIterator>
  void init(InputIterator begin, InputIterator end)
  {
    su.clear();
    su_sum = 0;
    sd     = std::multiset<int>(begin, end);
  }

  void insert(int x)
  {
    // printf("insert: %d\n", x);
    sd.insert(x);
    auto it = std::prev(sd.end());
    su.insert(*it);
    su_sum += *it;
    sd.erase(it);
  }

  void erase(int x)
  {
    // printf("erase: %d\n", x);
    if (x > *std::prev(sd.end()))
    {
      su.erase(su.find(x));
      su_sum -= x;
    }
    else
    {
      sd.erase(sd.find(x));
      auto it = su.begin();
      sd.insert(*it);
      su_sum -= *it;
      su.erase(it);
    }
  }
};

theap_t tp;
int     tl, tr;

void set_tlr(int l, int r)
{
  while (tl > l)
  {
    tl--;
    tp.insert(a[tl]);
  }
  while (tr < r)
  {
    tp.insert(a[tr]);
    tr++;
  }
  while (tl < l)
  {
    tp.erase(a[tl]);
    tl++;
  }
  while (tr > r)
  {
    tr--;
    tp.erase(a[tr]);
  }
}

int64_t g_ans = std::numeric_limits<int64_t>::min();

void dac(int ll, int lr, int rl, int rr)
{
  if (ll >= lr)
    return;

  int lm = ll + (lr - ll) / 2;

  int64_t cur_ans = std::numeric_limits<int64_t>::min();
  int     ans_id  = -1;

  int cl = std::max(rl, lm + 1), cr = rr;
  if (std::abs(tr - cl) < std::abs(tr - cr))
  {
    for (int i = cl; i < rr; i++)
    {
      set_tlr(lm, i);
      if (tp.su_sum > cur_ans)
      {
        cur_ans = tp.su_sum;
        ans_id  = i;
      }
    }
  }
  else
  {
    for (int i = cr - 1; i >= cl; i--)
    {
      set_tlr(lm, i);
      if (tp.su_sum > cur_ans)
      {
        cur_ans = tp.su_sum;
        ans_id  = i;
      }
    }
  }

  g_ans = std::max(g_ans, cur_ans);
  dac(ll, lm, rl, ans_id + 1);
  dac(lm + 1, lr, ans_id, rr);
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  for (int i = 0; i < m; i++)
    scanf("%d", &b[i]);
  tp.init(b, b + m);

  dac(0, n, 1, n + 1);
  std::cout << g_ans << std::endl;

  return 0;
}
