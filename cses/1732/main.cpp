#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1000005;
char s[N];

int main()
{
  using int_t = cm::intm<1019260817>;
  int n = static_cast<int>(sc.next_token(s) - s);  
  cm::string::hash_mod<int_t> hs(19491001, s, s + n);
  for (int i = 1; i < n; i++)
    if (hs.get_hash(0, i) == hs.get_hash(n - i, n))
      printf("%d ", i);
  return 0;
}

