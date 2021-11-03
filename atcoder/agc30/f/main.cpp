#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int MOD = 1000000007;
using int_t = cm::intm<MOD>;

CONSTRAINT(N, 605, 55)

int n;
int v[N];
int clr[N];
int_t f_[2][N][N];

int main()
{
  n = sc.next_int();
  for (int i = 1; i <= 2 * n; i++)
    v[i] = sc.next_int();

  for (int i = 1; i <= n; i++)
  {
    int k = (v[2 * i - 1] != -1) + (v[2 * i] != -1);
    if (k == 2)
      clr[v[2 * i - 1]] = clr[v[2 * i]] = 2;
    else if (k == 1)
    {
      if (v[2 * i - 1] != -1)
        clr[v[2 * i - 1]] = 1;
      if (v[2 * i] != -1)
        clr[v[2 * i]] = 1;
    }
  }

  f_[1][0][0] = 1;
  n <<= 1;

  for (int i = n; i; i--)
  {
    auto of = f_[(i + 1) & 1], nf = f_[i & 1];
    if (clr[i] == 2)
      memcpy(nf, of, 4 * N * N);
    else if (clr[i] == 1)
    {
      memset(nf, 0, 4 * N * N);
      for (int j = 0; j <= n; j++)
        for (int k = 0; k <= n; k++)
        {
          if (j < n)
            nf[j + 1][k] = nf[j + 1][k] + of[j][k];
          if (k)
            nf[j][k - 1] = nf[j][k - 1] + of[j][k];
        }
    }
    else if (clr[i] == 0)
    {
      memset(nf, 0, 4 * N * N);
      for (int j = 0; j <= n; j++)
        for (int k = 0; k <= n; k++)
        {
          if (k < n)
            nf[j][k + 1] = nf[j][k + 1] + of[j][k];
          if (k)
            nf[j][k - 1] = nf[j][k - 1] + of[j][k];
          if (j)
            nf[j - 1][k] = nf[j - 1][k] + 1LL * j * of[j][k];
        }
    }
  }

  auto ans = f_[1][0][0];
  for (int i = 1, cnt = 0; i <= n / 2; i++)
    if (v[2 * i - 1] == -1 && v[2 * i] == -1)
      ans = ans * ++cnt;

  std::cout << ans << std::endl;
}
