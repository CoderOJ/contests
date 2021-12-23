#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const double eps = 1e-10;
const int    N   = 400'005;

int n, m, q, cnt, p[N], a[N], b[N];

struct element_t
{
  int i, d;

  element_t() = default;
  element_t(int i, int d) : i(i), d(d) {}

  double get()
  {
    return 1.0 * p[i] * a[i] / (a[i] + b[i] - d) / (a[i] + b[i] - d + 1);
  }
};

bool operator<(element_t u, element_t v)
{
  if (std::abs(u.get() - v.get()) < eps)
    return u.i < v.i;
  return u.get() < v.get();
}

std::set<element_t> min, max;
double              ans;

void update()
{
  if (!min.empty())
  {
    element_t u = *min.begin();
    int       i = u.i;
    max.erase((element_t){i, 0});
    min.erase((element_t){i, 1});
    ans -= u.get();
    b[i]--;
    cnt--;
    max.insert((element_t){i, 0});
    if (b[i] > 0)
      min.emplace(i, 1);
  }
  while (!max.empty() && cnt < m)
  {
    element_t u = *max.rbegin();
    int       i = u.i;
    max.erase((element_t){i, 0});
    min.erase((element_t){i, 1});
    ans += u.get();
    b[i]++;
    cnt++;
    min.insert((element_t){i, 1});
    if (b[i] < a[i])
    {
      max.insert((element_t){i, 0});
    }
  }
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  q = sc.next_int();
  for (int i = 0; i < n; i++)
    p[i] = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  for (int i = 0; i < n; i++)
    max.insert((element_t){i, 0});
  update();

  for (int _ = 0; _ < q; _++)
  {
    const int opt = sc.next_int();
    const int i   = sc.next_int() - 1;
    max.erase({i, 0});
    min.erase({i, 1});
    ans -= 1.0 * p[i] * b[i] / (a[i] + b[i]);
    a[i] += opt == 1 ? 1 : -1;
    ans += 1.0 * p[i] * b[i] / (a[i] + b[i]);
    if (b[i] > 0)
    {
      b[i]--;
      cnt--;
      ans -= ((element_t){i, 0}).get();
    }

    if (b[i] < a[i])
      max.emplace(i, 0);
    if (b[i] > 0)
      min.emplace(i, 1);
    update();
    printf("%.9f\n", ans);
  }
  return 0;
}
