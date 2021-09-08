#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <vector>
#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

#define int long long 

constexpr int N = 100005;
int k, n, m, a[N];
std::pair<int,int> max_assign[N];
std::vector<std::pair<int,int>> add[N], mul[N];
int type[N];

struct fac_t
{
  int a = 0, b = 1;
  fac_t() =default;
  fac_t(int a) : a(a), b(1) {}
  fac_t(int a, int b) : a(a), b(b) {}
  bool operator< (const fac_t &rhs) const
  { return (__int128_t)(a) * rhs.b < (__int128_t)(rhs.a) * b; }
  friend std::ostream& operator<< (std::ostream& out, const fac_t x) {
    out << "(" << x.a << ", " << x.b << ")"; return out; }
};

signed main()
{
  k = sc.next_int();
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < k; i++)
    a[i] = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int type = sc.next_int(), pos = sc.next_int() - 1, b = sc.next_int(); ::type[i] = type;
    if (type == 1) check_max(max_assign[pos], std::make_pair(b, i));
    else if (type == 2) add[pos].emplace_back(b, i);
    else mul[pos].emplace_back(b, i);
  }

  std::vector<std::pair<fac_t, int>> ops;
  for (int i = 0; i < k; i++) if (max_assign[i].first >= a[i])
    add[i].emplace_back(max_assign[i].first - a[i], max_assign[i].second);
  for (int i = 0; i < k; i++) {
    for (auto x : mul[i]) ops.emplace_back(x.first, x.second);
    std::sort(add[i].begin(), add[i].end(), std::greater<std::pair<int,int>>());
    int cur = a[i];
    for (auto x : add[i]) { ops.emplace_back(fac_t(cur + x.first, cur), x.second); cur += x.first; } }

  std::sort(ops.begin(), ops.end(), std::greater<std::pair<fac_t,int>>());
  if ((int)ops.size() < m) m = ops.size();
  std::sort(ops.begin(), ops.begin() + m, [](auto x, auto y) { return type[x.second] < type[y.second]; });
  std::cout << m << std::endl;
  for (int i = 0; i < m; i++) std::cout << ops[i].second + 1 << " ";
  std::cout << std::endl;
  return 0;
}

