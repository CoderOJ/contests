#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct exam_t
{
  long long a, b;
  int       l, r;

  long long calc()
  {
    return (a - b) * (a < b ? l : r);
  }
};

int main()
{
  int       n = sc.next_int();
  long long x = sc.next_int();

  std::vector<exam_t> a(n);
  for (int i = 0; i < n; i++)
  {
    a[i].b = sc.next_int();
    a[i].l = sc.next_int();
    a[i].r = sc.next_int();
  }
  std::sort(a.begin(), a.end(), [x](auto a, auto b) {
    return (x - a.b) * a.r + a.b * a.l > (x - b.b) * b.r + b.b * b.l;
  });

  long long l = 0, r = x * n;
  while (l < r)
  {
    long long m   = (l + r) / 2;
    long long c   = m;
    long long ans = 0;

    int un_id = n - 1;
    for (int i = 0; i < n; i++)
    {
      a[i].a = std::min(c, x);
      c      = c - a[i].a;
      if (a[i].a && a[i].a < x)
        un_id = i;
      ans += a[i].calc();
    }

    long long best = ans;
    for (int i = 0; i < n; i++)
    {
      long long cur = ans;
      cur -= a[i].calc();
      cur -= a[un_id].calc();
      std::swap(a[i].a, a[un_id].a);
      cur += a[i].calc();
      cur += a[un_id].calc();
      check_max(best, cur);
      std::swap(a[i].a, a[un_id].a);
    }
    if (best >= 0)
      r = m;
    else
      l = m + 1;
  }

  printf("%lld\n", l);

  return 0;
}
