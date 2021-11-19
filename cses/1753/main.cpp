#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1000005;
char s[N], t[N];

int main()
{
  using int_t = cm::intm<1019260817>;

  int n = static_cast<int>(sc.next_token(s) - s);
  int m = static_cast<int>(sc.next_token(t) - t);

  cm::string::hash_mod<int_t> hs(19260817, s, s + n);
  cm::string::hash_mod<int_t> ht(19260817, t, t + n);

  int cnt = 0;
  for (int i = 0; i + m <= n; i++)
    if (hs.get_hash(i, i + m) == ht.get_hash(0, m))
      cnt++;

  std::cout << cnt << std::endl;

  return 0;
}

