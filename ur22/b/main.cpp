#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cstring>
#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

struct basis_t
{
  static constexpr int BIT_LIM = 20;

  int p[BIT_LIM];

  basis_t()
  { memset(p, 0, sizeof(p)); }

  void insert(int x)
  {
    for (int i = BIT_LIM - 1; i >= 0; --i)
      if ((x >> i) & 1)
      {
        if (p[i] == 0)
        {
          p[i] = x;
          break;
        }
        x ^= p[i];
      }
  }

  int getMax(int res)
  {
    for (int i = BIT_LIM - 1; i >= 0; --i)
      check_max(res, res ^ p[i]);
    return res;
  }
};

int main()
{
  int n = sc.next_int();
  int k = sc.next_int();
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  for (int i = 0; i < n; i++)
    b[i] = sc.next_int();

  std::vector<int> anss;
  anss.reserve(n * (n + 1) / 2);
  for (int i = 0; i < n; i++)
  {
    basis_t bs;
    int cur_xor = 0;
    for (int j = i; j < n; j++)
    {
      bs.insert(b[j] ^ a[j]);
      cur_xor ^= a[j];
      anss.push_back(bs.getMax(cur_xor));
    }
  }

  see(anss);

  std::nth_element(anss.begin(), anss.begin() + k - 1, anss.end());
  std::cout << anss[k - 1] << std::endl;

  return 0;
}
