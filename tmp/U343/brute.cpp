#include <bits/stdc++.h>

int n;

int get_fac(int x)
{
  for (int i = n - 1; i >= 1; i--)
    if (x % i == 0)
      return i;
  return 1;
}

std::vector<int> split(int x)
{
  int c = get_fac(x); x /= c;
  int b = get_fac(x); x /= b;
  int a = get_fac(x); x /= a;
  return {a, b, c};
}

int main(int argc, char **argv)
{
  assert(argc == 2);

  sscanf(argv[1], "%d", &n);

  for (int a = 1; a < n; a++)
    for (int b = 1; b < n; b++)
      for (int c = 1; c < n; c++)
      {
        std::vector<int> cc{a, b, c};
        std::vector<int> rr = split(a * b * c);
        if (cc < rr)
        {
          printf("{%d, {3, %d, %d, %d}},\n", n, a, b, c);
          return 0;
        }
      }

  printf("{%d, {-1}},\n", n);

  return 0;
}
