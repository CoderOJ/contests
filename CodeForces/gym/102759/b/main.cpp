#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>

constexpr int N   = 200'005;
constexpr int INF = 0x3f3f3f3f;

int a[N], b[N], n, m;

using inter_t = std::pair<int, int>;
const inter_t ninter{-1, -1};

std::vector<inter_t> solve(int a[], int b[], int n, int m)
{
  std::vector<inter_t> res(n);

  a[n] = INF;
  b[m] = INF;

  static int b_max[N];
  static int b_min_id[N];
  b_max[0]    = -INF;
  b_min_id[0] = 0;
  for (int i = 0; i < m; i++)
  {
    b_max[i + 1]    = std::max(b_max[i], b[i]);
    b_min_id[i + 1] = b[i] < b[b_min_id[i]] ? i : b_min_id[i];
  }

  std::set<int> s;
  s.insert(b[b_min_id[m]]);

  int last_all_block = n;
  int last_all_free  = -1;

  for (int i = n - 1; i >= 0; i--)
  {
    while (s.begin() != s.end() && *s.begin() + a[i] >= 0)
      s.erase(s.begin());
    int wall_r = static_cast<int>(
        std::lower_bound(
            b_max, b_max + m + 1, 0, [&](int v, int) { return v + a[i] < 0; }) -
        b_max - 1);
    if (wall_r != 0)
    {
      int min_id = b_min_id[wall_r];
      s.insert(b[min_id]);
    }

    if (b_max[m] + a[i] < 0)
      last_all_block = i;
    if (b[b_min_id[m]] + a[i] >= 0)
      last_all_free = i;

    if (!s.empty() || last_all_free == -1)
      res[i] = ninter;
    else
      res[i] = {last_all_free, last_all_block};
  }

  return res;
}

int r_valid[N];

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  for (int j = 0; j < m; j++)
    scanf("%d", &b[j]);

  auto l_to_r = solve(a, b, n, m);

  std::reverse(a, a + n);
  std::reverse(b, b + m);
  auto r_to_l = solve(a, b, n, m);
  std::reverse(r_to_l.begin(), r_to_l.end());

  r_valid[0] = 0;
  for (int i = 0; i < n; i++)
    r_valid[i + 1] = r_valid[i] + (r_to_l[i] == ninter ? 0 : 1);

  int64_t ans = 0;
  for (int i = 0; i < n; i++)
    if (l_to_r[i] != ninter)
      ans += r_valid[l_to_r[i].second] - r_valid[l_to_r[i].first];

  std::cout << ans << std::endl;

  return 0;
}
