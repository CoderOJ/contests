#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <cmath>
#include <limits>

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 200005;
const long long inf = std::numeric_limits<long long>::max() / 4;

[[noreturn]] void fail()
{
  puts("NO");
  exit(0);
}

long long lx = -inf, rx = inf, ly = -inf, ry = inf;
int n, l;

struct P
{
  long long t, x, y, k;
  int w;

  void input()
  {
    t = sc.next_long();
    long long p = sc.next_long(), q = sc.next_long();

    if ((t ^ p ^ q) & 1)
      fail();

    k = t / l, w = t % l;
    x = (p + q + t) / 2, y = (q - p + t) / 2;
  }
  bool operator<(const P &rhs) const
  {
    return w < rhs.w;
  }
} p[N];

long long idivfl(long long a, long long b)
{
  cm_assert(b != 0);
  if (b < 0) a = -a, b = -b;
  long long res = a / b;
  if (a % b != 0 && a < 0) res--;
  return res;
}

long long idivce(long long a, long long b)
{
  cm_assert(b != 0);
  if (b < 0) a = -a, b = -b;
  long long res = a / b;
  if (a % b != 0 && a > 0) res++;
  return res;
}

int main()
{
  n = sc.next_int();
  l = sc.next_int();
  for (int i = 1; i <= n; i++) p[i].input();
  std::sort(p + 1, p + n + 1);
  p[++n].k = -1, p[n].w = l;
  for (int i = 1; i <= n; i++)
  {
    long long k = p[i].k - p[i - 1].k;
    int w = p[i].w - p[i - 1].w;
    if (!k)
    {
      if (p[i].x - p[i - 1].x - w > 0 || p[i].x - p[i - 1].x < 0)
        fail();
      if (p[i].y - p[i - 1].y - w > 0 || p[i].y - p[i - 1].y < 0)
        fail();
    }
    else if (k > 0)
    {
      check_max(lx, idivce(p[i].x - p[i - 1].x - w, k));
      check_min(rx, idivfl(p[i].x - p[i - 1].x, k));
      check_max(ly, idivce(p[i].y - p[i - 1].y - w, k));
      check_min(ry, idivfl(p[i].y - p[i - 1].y,k));
    }
    else
    {
      k *= -1;
      check_max(lx, idivce(p[i - 1].x - p[i].x, k));
      check_min(rx, idivfl(p[i - 1].x - p[i].x + w, k));
      check_max(ly, idivce(p[i - 1].y - p[i].y, k));
      check_min(ry, idivfl(p[i - 1].y - p[i].y + w, k));
    }
  }

  if (lx > rx || ly > ry)
    fail();

  for (int i = 1; i <= n; i++)
  {
    long long dx = (p[i].x - p[i].k * lx) - (p[i - 1].x - p[i - 1].k * lx);
    long long  dy = (p[i].y - p[i].k * ly) - (p[i - 1].y - p[i - 1].k * ly);
    int t = p[i].w - p[i - 1].w;
    int x = 0, y = 0;

    while (t--)
    {
      if (x < dx)
      {
        ++x;
        if (y < dy)
          putchar('U'), ++y;
        else
          putchar('R');
      }
      else
      {
        if (y < dy)
          putchar('L'), ++y;
        else
          putchar('D');
      }
    }
  }
  puts("");
  return 0;
}
