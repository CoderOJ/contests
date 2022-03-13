#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
#include <map>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 300'005;

char s[N];
int  n;

int main()
{
  sc.next_token(s);
  n = (int)std::strlen(s);

  std::map<std::pair<int, int>, int> cnt;
  std::map<std::pair<int, int>, int> cnta;
  std::map<std::pair<int, int>, int> cntb;
  std::map<std::pair<int, int>, int> cntc;
  std::map<std::pair<int, int>, int> cntab;
  std::map<std::pair<int, int>, int> cntbc;
  std::map<std::pair<int, int>, int> cntac;

  int a = 0;
  int b = 0;
  int c = 0;

  int64_t ans = 0;

  auto update = [&](int &x) {
    ans += x;
    x += 1;
  };

  for (int i = 0; i <= n; i++)
  {
    update(cnt[{a - b, a - c}]);
    update(cnta[{a, b - c}]);
    update(cntb[{b, a - c}]);
    update(cntc[{c, a - b}]);
    update(cntab[{a, b}]);
    update(cntbc[{b, c}]);
    update(cntac[{a, c}]);
    if (s[i] == 'a')
      a += 1;
    else if (s[i] == 'b')
      b += 1;
    else
      c += 1;
  }

  std::cout << ans << std::endl;

  return 0;
}
