#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int() - 1;
  std::vector<int> pos(n + 1);
  for (int i = 0; i < n; i++)
    pos[a[i]] = i;
  pos[n] = -1;

  auto get = [&](int val)
  {
    if (val < 0 || val >= n) return 0;
    return static_cast<int>(pos[val] > pos[val + 1]);
  };

  int ans = 0;
  for (int i = 0; i < n; i++) ans += get(i);

  for (int i = 0; i < m; i++)
  {
    int x = sc.next_int() - 1;
    int y = sc.next_int() - 1;
    ans -= get(a[x]) + get(a[y]);
    if (a[x] - 1 != a[y]) ans -= get(a[x] - 1);
    if (a[y] - 1 != a[x]) ans -= get(a[y] - 1);
    std::swap(a[x], a[y]); std::swap(pos[a[x]], pos[a[y]]);
    ans += get(a[x]) + get(a[y]);
    if (a[x] - 1 != a[y]) ans += get(a[x] - 1);
    if (a[y] - 1 != a[x]) ans += get(a[y] - 1);
    std::cout << ans << std::endl;
  }
  return 0;
}

