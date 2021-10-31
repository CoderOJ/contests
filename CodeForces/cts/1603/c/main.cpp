#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int T = sc.next_int();
  for (int i = 0; i < T; i++)
  {
    constexpr int MOD = 998244353;
    using int_t = cm::intm<MOD>;

    int n = sc.next_int();
    std::vector<int> a(n);
    for (int &x : a)
      x = sc.next_int();

    std::vector<int> lim(n), cnt(n);
    int_t ans = 0, cur = 0;
    for (int i = 0; i < n; i++)
    {
      lim[i] = a[i];
      cnt[i] = 1;
      cur += 1ll * (i + 1) * (cnt[i] - 1);
      for (int j = i - 1; j >= 0; j--)
      {
        see(j, lim[j], lim[j + 1]);
        cur -= 1ll * (j + 1) * (cnt[j] - 1);
        cnt[j] = (a[j] + lim[j + 1] - 1) / lim[j + 1];
        cur += 1ll * (j + 1) * (cnt[j] - 1);
        if (!check_min(lim[j], a[j] / cnt[j]))
          break;
      }
      ans += cur;
      see(cur, cnt, lim);
    }

    std::cout << ans << std::endl;
  }
  return 0;
}
