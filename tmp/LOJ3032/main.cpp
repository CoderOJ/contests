#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <numeric>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct frac_t
{
  int64_t x, y;
  frac_t(int64_t x = 0, int64_t y = 1) : x(x), y(y) {}

  frac_t operator+(int64_t rhs) const
  {
    return {x + y * rhs, y};
  }

  bool operator<(const frac_t &rhs) const
  {
    return static_cast<__int128_t>(x) * rhs.y <
           static_cast<__int128_t>(y) * rhs.x;
  }
};

std::ostream &operator<<(std::ostream &os, frac_t f)
{
  return os << f.x << "/" << f.y;
}

int main()
{
  int n = sc.next_int();
  int l = sc.next_int();

  std::vector<std::vector<int>> a(n, std::vector<int>(l));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < l; j++)
      a[i][j] = sc.next_int();

  std::vector<std::vector<frac_t>> brks;
  for (int i = 0; i < n; i++)
  {
    std::vector<frac_t> cur;

    int64_t bs =
        std::accumulate(a[i].begin(), a[i].end(), static_cast<int64_t>(0)) * n;
    int64_t br = bs / n;

    int64_t psum = 0;
    for (int j = 0; j < l; j++)
    {
      int64_t lb = psum / br + 1;
      int64_t rb = (psum + a[i][j] * n) / br + 1;
      for (int64_t k = lb; k < rb; k++)
        cur.emplace_back(frac_t(k * br - psum, a[i][j] * n) + j);
      psum += a[i][j] * n;
    }
    see(cur);

    brks.emplace_back(std::move(cur));
  }

  std::vector<bool>   used(n, false);
  std::vector<frac_t> ans;
  std::vector<int>    perm;

  for (int i = 0; i < n; i++)
  {
    int p = -1;
    for (int j = 0; j < n; j++)
      if (!used[j])
        if (p == -1 || brks[j][i] < brks[p][i])
          p = j;
    ans.push_back(brks[p][i]);
    used[p] = true;
    perm.push_back(p);
  }

  for (int i = 0; i < n - 1; i++)
    std::cout << ans[i].x << " " << ans[i].y << std::endl;
  for (int i = 0; i < n; i++)
    std::cout << perm[i] + 1 << " ";
  std::cout << std::endl;

  return 0;
}
