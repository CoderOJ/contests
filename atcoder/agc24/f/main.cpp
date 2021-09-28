#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 21;

int n, k, s[1 << N], tr[1 << N][2];
int f[N][1 << N];

int main()
{
  n = sc.next_int();
  k = sc.next_int();

  for (int i = 0; i <= n; ++i)
    for (int x = 0; x < 1 << i; ++x)
      f[i][1 << i ^ x] = sc.next_char() - '0';

  s[0] = -1;
  for (int A = 1; A < 2 << n; ++A)
    s[A] = s[A >> 1] + 1;
  for (int A = 2; A < 2 << n; ++A)
    if (A >> (s[A] - 1) & 1)
    {
      tr[A][1] = A ^ 1 << s[A];
      tr[A][0] = tr[tr[A][1]][0];
    }
    else
    {
      tr[A][0] = A ^ 3 << (s[A] - 1);
      tr[A][1] = tr[tr[A][0]][1];
    }

  for (int i = n; i >= 1; --i)
  {
    for (int A = 1 << i; A < 2 << n; ++A)
    {
      if (!f[i][A])
        continue;
      int _ = A >> i, B = (A & ((1 << i) - 1)) ^ 1 << i;
      if (tr[B][0])
        f[s[tr[B][0]]][(_ << 1 ^ 1) << s[tr[B][0]] ^ tr[B][0]] += f[i][A];
      if (tr[B][1])
        f[s[tr[B][1]]][(_ << 1 ^ 0) << s[tr[B][1]] ^ tr[B][1]] += f[i][A];
      f[0][_] += f[i][A];
    }
  }

  int ans = 1;
  for (int A = 2; A < 2 << n; ++A)
    if (f[0][A] >= k && s[A] > s[ans])
      ans = A;

  int j = n;
  while (~ans >> j & 1) --j;
  while (j--) printf("%d", ans >> j & 1);
  puts("");

  return 0;
}
