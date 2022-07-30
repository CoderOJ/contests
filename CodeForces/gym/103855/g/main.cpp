#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <string>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 998'244'353;
using int_t       = cm::intm<MOD>;
using mu          = cm::math_util<int_t>;

void dft(std::vector<int_t> &a, int n)
{
  std::vector<int> rev(1 << n);
  rev[0] = 0;
  for (int i = 1; i < (1 << n); i++)
  {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (n - 1));
    if (i < rev[i])
      std::swap(a[i], a[rev[i]]);
  }

  auto get_ws = [](int l, int_t w) {
    std::vector<int_t> a(l);

    int_t cur_w = 1;
    for (int i = 0; i < l; i++)
    {
      a[i] = cur_w;
      cur_w *= w;
    }

    return a;
  };

  for (int l = 1; l < (1 << n); l <<= 1)
  {
    std::vector<int_t> ws = get_ws(l, int_t(3).pow((MOD - 1) / l / 2));
    for (int i = 0; i < (1 << n); i += l * 2)
      for (int j = 0; j < l; j++)
      {
        int_t c      = ws[j] * a[i + l + j];
        a[i + l + j] = a[i + j] - c;
        a[i + j]     = a[i + j] + c;
      }
  }
}

void idft(std::vector<int_t> &a, int n)
{
  std::reverse(a.begin() + 1, a.end());
  dft(a, n);

  int_t inv_n = int_t(1 << n).inv();
  for (auto &x: a)
    x *= inv_n;
}

std::vector<int_t> mul(std::vector<int_t> a, std::vector<int_t> b)
{
  int res_size = (int)a.size() + (int)b.size() - 1;

  int n = [](int s) {
    for (int i = 0;; i++)
      if ((1 << i) >= s)
        return i;
  }(res_size);

  a.resize(1 << n, 0);
  b.resize(1 << n, 0);

  dft(a, n);
  dft(b, n);
  for (int i = 0; i < (1 << n); i++)
    a[i] *= b[i];
  idft(a, n);

  a.resize(res_size);
  a.shrink_to_fit();
  return a;
}

int main()
{
  int n = sc.next_int();

  std::string s;
  s.reserve(n);
  for (int i = 0; i < n; i++)
    s += sc.next_char();

  std::vector<int> ws(n);
  for (int i = 0; i < n; i++)
    ws[i] = sc.next_int();

  auto solve = [](const std::string &s, const std::vector<int> &ws) {
    int n = (int)s.size();

    std::vector<int_t> pa(n, 0);
    std::vector<int_t> pb(n, 0);

    int_t pw = 0;
    for (int i = 0; i < n; i++)
    {
      if (s[i] == 'W')
      {
        pa[i]         = pw;
        pb[n - i - 1] = 1;
      }
      else
      {
        pw += ws[i];
      }
    }

    auto pr = mul(pa, pb);
    // see(pa);
    // see(pb);
    // see(pr);

    int_t ans = 0;
    for (int l = 2; l < n; l++)
    {
      int_t coef = int_t(2) / (int_t(l - 1) * l * (l + 1));
      int_t wsum = pr[n - 1 + l] - pr[n - 1 - l];
      ans += coef * wsum;
    }

    return ans;
  };

  auto ans0 = solve(s, ws);

  for (auto &&c: s)
    c = (c == 'W') ? 'B' : 'W';
  auto ans1 = solve(s, ws);

  std::cout << (ans0 + ans1) * mu::fac.get(n) << std::endl;

  return 0;
}
