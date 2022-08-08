#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

const int N = 500005;
const uint64_t seed = 30181002220301;
const uint64_t i_seed = 10223959459385209797ull;

char s[N];
int f[N];
int n, q;

uint64_t ph[N];
uint64_t isp[N];

int main()
{
  scanf("%d%d", &n, &q);
  scanf("%s", s);
  for (int i = 1; i <= n; i++)
    scanf("%d", &f[i]);

  {
    isp[0] = 1;
    for (int i = 0; i + 1 <= n; i++)
      isp[i + 1] = isp[i] * i_seed;
  }
  {
    uint64_t cp = 1;
    ph[0] = 0;
    for (int i = 0; i + 1 <= n; i++)
    {
      ph[i + 1] = ph[i] + s[i] * cp;
      cp *= seed;
    }
  }

  int lim = (n <= 5000) ? n : 50;

  __gnu_pbds::gp_hash_table<uint64_t, int> sub_cnt[5005];
  for (int i = 1; i <= n; i++)
  {
    uint64_t ch = 0;
    for (int j = i - 1; j >= 0 && (i - j) <= lim; j--)
    {
      ch = s[j] + seed * ch;
      sub_cnt[i - j][ch] += 1;
    }
  }

  for (int i = 0; i < q; i++)
  {
    int l, r;
    scanf("%d%d", &l, &r);
    l -= 1;

    uint64_t lrh = (ph[r] - ph[l]) * isp[l];
    int64_t ans = 0;
    if (r - l > lim)
      ans += f[1];
    else
      ans += f[sub_cnt[r - l][lrh]];

    uint64_t ch = 0;
    for (int p = r - 1; p > l && (r - p) <= lim; p--)
    {
      ch = s[p] + seed * ch;
      uint64_t lh = (ph[l + (r - p)] - ph[l]) * isp[l];
      if (lh == ch)
        ans += f[sub_cnt[r - p][ch]];
    }

    printf("%" SCNi64 "\n", ans);
  }

  return 0;
}
