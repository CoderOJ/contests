#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/string"

#include <numeric>

using hash_int_t = cm::intm<998244353>;
cm::scanner<cm::optimal_reader> sc(stdin);
constexpr int N = 30005;
char s[N];
int p_cnt[N], s_cnt[N];

int main()
{
  int T = sc.next_int();
  while (T--)
  {
    size_t n = sc.next_token(s) - s;
    std::fill(p_cnt, p_cnt + n, 0);
    std::fill(s_cnt, s_cnt + n, 0);
    cm::string::hash_mod<hash_int_t> hash(2333, s, s + n);

    for (size_t l = 1; l < n; l++)
      for (size_t i = 0; i + l < n; i += l)
      {
        size_t lc = std::min(cm::string::lcs(hash, i, hash, i + l), l - 1);
        size_t rc = std::min(cm::string::lcp(hash, i, hash, i + l), l);
        if (lc + rc >= l)
        {
          s_cnt[i - lc]++;
          s_cnt[i + rc - l + 1]--;
          p_cnt[i + l + l - lc]++;
          p_cnt[i + l + rc + 1]--;
        }
      }

    std::partial_sum(p_cnt, p_cnt + n, p_cnt);
    std::partial_sum(s_cnt, s_cnt + n, s_cnt);

    long long ans = 0;
    for (size_t i = 0; i < n; i++)
      ans += p_cnt[i] * s_cnt[i];
    printf("%lld\n", ans);
  }
  return 0;
}
