#include <bits/stdc++.h>

const int MOD = 1'000'000'007;
const int N   = 500'005;

using int_t = int;

int le_mr[N];
int ge_mr[N];
int n, m;

struct dp_t
{
  int   p;
  int   c;
  int_t v;
};

int_t cnt[26];
int_t v_cnt[26];

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++)
  {
    int l, r;
    scanf("%d%d", &l, &r);
    l -= 1, r -= 1;
    if (l < r)
      le_mr[l] = std::max(le_mr[l], r);     
    else
      ge_mr[r] = std::max(ge_mr[r], l);
  }

  std::vector<dp_t> le;
  std::vector<dp_t> ge;
  for (int c = 0; c < 26; c++)
  {
    ge.push_back({n - 1, c, 1});
    cnt[c] = 1;
  }

  for (int i = n - 2; i >= 0; i--)
  {
    {
      int_t cur = 0;
      for (int c = 0; c < 26; c++)
      {
        // printf("ge: %d %d\n", c, cur);
        ge.push_back({i, c, cur});
        v_cnt[c] = (v_cnt[c] + cur) % MOD;
        cur = (cur + cnt[c]) % MOD;
      }
    }
    {
      int_t cur = 0;
      for (int c = 25; c >= 0; c--)
      {
        // printf("le: %d %d\n", c, cur);
        le.push_back({i, c, cur});
        v_cnt[c] = (v_cnt[c] + cur) % MOD;
        cur = (cur + cnt[c]) % MOD;
      }
    }
    for (int i = 0; i < 26; i++)
    {
      cnt[i] = (cnt[i] + v_cnt[i]) % MOD;
      v_cnt[i] = 0;
    }
    {
      while (!le.empty() && le.back().p < le_mr[i])
      {
        auto b = le.back();
        le.pop_back();
        cnt[b.c] = (MOD + cnt[b.c] - b.v) % MOD;
      }
    }
    {
      while (!ge.empty() && ge.back().p < ge_mr[i])
      {
        auto b = ge.back();
        ge.pop_back();
        cnt[b.c] = (MOD + cnt[b.c] - b.v) % MOD;
      }
    }
  }

  int_t ans = 0;
  for (int i = 0; i < 26; i++)
    ans = (ans + cnt[i]) % MOD;

  std::cout << ans << std::endl;

  return 0;
}
