#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 200000 + 5;
constexpr int M = 256;
constexpr int THRE = 255;
int x[N], y[N], cnt[M][M], s[N], a[N], ans;
int n, m;

void block_modify(int tm, int k, int v)
{
  int bl = x[k] + y[k], *c = cnt[bl];
  int l = (tm + x[k]) % bl, r = (tm - 1) % bl;
  if (l <= r)
    for (int i = l; i <= r; i++)
      c[i] += v;
  else
  {
    for (int i = 0; i <= r; i++)
      c[i] += v;
    for (int i = l; i < bl; i++)
      c[i] += v;
  }
}

int block_query(int Tm)
{
  int res = 0;
  for (int i = 2; i <= THRE; i++)
    res += cnt[i][Tm % i];
  return res;
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 1; i <= n; i++)
  {
    x[i] = sc.next_int();
    y[i] = sc.next_int();
  }

  for (int i = 1; i <= m; i++)
  {
    int opt = sc.next_int();
    int k = sc.next_int();

    if (opt == 1)
    {
      if (THRE < x[k] + y[k])
      {
        for (int j = i + x[k]; j <= m; j += x[k] + y[k])
        {
          a[j]++;
          if (j + y[k] <= m)
            a[j + y[k]]--;
        }
      }
      else
        block_modify(i, k, 1);
      s[k] = i;
    }
    else
    {
      if (THRE < x[k] + y[k])
      {
        for (int j = s[k] + x[k]; j <= m; j += x[k] + y[k])
        {
          a[j]--;
          if (j + y[k] <= m)
            a[j + y[k]]++;
          if (j < i && j + y[k] >= i)
            ans--;
        }
      }
      else
        block_modify(s[k], k, -1);
    }

    ans += a[i];
    printf("%d\n", ans + block_query(i));
  }
  return 0;
}
