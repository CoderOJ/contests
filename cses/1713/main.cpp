#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 1000005, 1005)
int fac[N];

int main()
{
  for (int i = 2; i < N; i++)
    for (int j = i; j < N; j += i)
      if (fac[j] == 0)
        fac[j] = i;

  int n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int x = sc.next_int();
    int a = 1;
    while (x > 1)
    {
      int p = fac[x];
      int c = 1;
      while (x % p == 0)
      {
        x /= p;
        c++;
      }
      a *= c;
    }
    std::cout << a << std::endl;
  }
  return 0;
}

