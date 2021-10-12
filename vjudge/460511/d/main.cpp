#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int get_rem1(const std::vector<int> &a)
{
  int cnt1 = 0, cnt0 = 0;
  for (int x: a)
  {
    if (x == 0)
    {
      cnt0++;
      if (cnt0 == 3)
        cnt0 = 1;
    }
    else
    {
      if (cnt0)
        cnt0--;
      else
        cnt1++;
    }
  }
  return cnt1 - cnt0;
}

int get_rem0(const std::vector<int> &a)
{
  int cnt0 = 0, cnt1 = 0;
  for (int x: a)
  {
    if (x == 1)
    {
      cnt1++;
      if (cnt1 == 3)
        cnt1 = 1;
    }
    else
    {
      if (cnt1)
        cnt1--;
      else
        cnt0++;
    }
  }
  return cnt1 - cnt0;
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();
    for (int i = 0; i < n; i++)
    {
      std::vector<int> p, s;
      for (int j = 0; j < i; j++) p.push_back(a[j] > a[i]);
      for (int j = i + 1; j < n; j++) s.push_back(a[j] > a[i]);
      int pl = get_rem0(p), pr = get_rem1(p);
      int sl = get_rem0(s), sr = get_rem1(s);
      putchar(pl + sl <= 0 && pr + sr >= 0 ? '1' : '0');
    }
    puts("");
  }
  return 0;
}

