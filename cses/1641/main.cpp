#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <map>
#include <unordered_map>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  std::unordered_map<int, int> mp;
  int n = sc.next_int(), x = sc.next_int();
  mp.reserve(n * 10);
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
      if (mp.count(x - a[i] - a[j]))
      {
        std::cout << mp[x - a[i] - a[j]] + 1 << " " << i + 1 << " " << j + 1 << std::endl;
        return 0;
      }
    mp[a[i]] = i;
  }

  puts("IMPOSSIBLE");
  return 0;
}

