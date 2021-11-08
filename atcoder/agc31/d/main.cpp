#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{

  struct perm_t : public std::vector<int>
  {
    using std::vector<int>::vector;

    perm_t inv() const
    {
      perm_t result(size());
      for (int i = 0; i < static_cast<int>(size()); i++)
        result[at(i)] = i;
      return result;
    }

    perm_t operator*(const perm_t &rhs) const
    {
      perm_t result(size());
      for (int i = 0; i < static_cast<int>(size()); i++)
        result[i] = rhs[at(i)];
      return result;
    }

    perm_t pow(int k) const
    {
      perm_t result(size()), a = *this;
      for (int i = 0; i < static_cast<int>(size()); i++)
        result[i] = i;
      for (; k; k >>= 1)
      {
        if (k & 1)
          result = result * a;
        a = a * a;
      }
      return result;
    }
  };

  int n = sc.next_int();
  int k = sc.next_int();
  perm_t p(n), q(n);
  for (int i = 0; i < n; i++)
    p[i] = sc.next_int() - 1;
  for (int i = 0; i < n; i++)
    q[i] = sc.next_int() - 1;
  auto P = p.inv();
  auto Q = q.inv();

  auto eval = [&](const std::string &s) {
    auto res = s[0] == 'p' ? p : s[0] == 'P' ? P : s[0] == 'q' ? q : Q;
    for (size_t i = 1; i < s.length(); i++)
      res = res * (s[i] == 'p' ? p : s[i] == 'P' ? P : s[i] == 'q' ? q : Q);
    return res;
  };

  perm_t ans;
  // clang-format off
  switch (k % 6)
  {
    case 0: ans = eval("QpqP").pow(k / 6 - 1) * eval("QppQPq") * eval("pQPq").pow(k / 6 - 1); break;
    case 1: ans = eval("QpqP").pow(k / 6) * eval("p") * eval("pQPq").pow(k / 6); break;
    case 2: ans = eval("QpqP").pow(k / 6) * eval("q") * eval("pQPq").pow(k / 6); break;
    case 3: ans = eval("QpqP").pow(k / 6) * eval("Pq") * eval("pQPq").pow(k / 6); break;
    case 4: ans = eval("QpqP").pow(k / 6) * eval("QPq") * eval("pQPq").pow(k / 6); break;
    case 5: ans = eval("QpqP").pow(k / 6) * eval("QpQPq") * eval("pQPq").pow(k / 6); break;
  }
  // clang-format on

  for (int i = 0; i < n; i++)
    std::cout << ans[i] + 1 << " ";

  return 0;
}
