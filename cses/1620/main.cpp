#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long
  int n = sc.next_int();
  int t = sc.next_int();

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) a[i] = sc.next_int();

  int l = 1, r = 1e18;
  while (l < r)
  {
    int mid = (l + r) / 2;
    int cnt = 0;
    for (int x: a) 
    {
      cnt += mid / x;
      if (cnt >= t) break;
    }
    if (cnt >= t) r = mid;
    else l = mid + 1;
  }

  std::cout << l << std::endl;

  return 0;
}

