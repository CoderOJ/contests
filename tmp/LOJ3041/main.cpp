#include "minerals.h"
#include <vector>

bool get(int x)
{
  static int last = 0;

  int cur = Query(x);
  if (cur == last)
    return false;
  else
  {
    last = cur;
    return true;
  }
}

const int N = 45000;
const int M = 1000;

double pb[M][M];
double dp[N];
int    sp[N];

void init()
{
  for (int i = 1; i < M; i++)
  {
    pb[i][0] = 0;
    for (int j = 1; j <= i; j++)
      pb[i][j] = (1.0 * j / i) * (1 + pb[i - 1][j - 1]);
  }

  auto get_pb = [](int n, int r) {
    int f = n / M + 1;
    return pb[n / f][r / f];
  };

  dp[1] = 0;
  for (int i = 2; i < N; i++)
  {
    dp[i] = 0x3f3f3f3f;
    int s = i / 200 + 1;
    for (int j = 1; j <= i / 2; j += s)
    {
      double v = i - get_pb(i, j) - get_pb(i, i - j) + j + dp[j] + dp[i - j];
      if (v < dp[i])
      {
        dp[i] = v;
        sp[i] = j;
      }
    }
  }
}

void solve(const std::vector<int> &l,
           const std::vector<int> &r,
           int                     n,
           bool                    is_in)
{
  if (n == 1)
  {
    Answer(l[0], r[0]);
  }
  else
  {
    const int s = sp[n];

    std::vector<int> vl0(l.begin(), l.begin() + s);
    std::vector<int> vl1(l.begin() + s, l.end());
    std::vector<int> vr0;
    std::vector<int> vr1;

    for (int x : vl0)
      get(x);
    for (int x : r)
    {
      if (vr0.size() == vl0.size())
        vr1.push_back(x);
      else if (vr1.size() == vl1.size())
        vr0.push_back(x);
      else
      {
        if (get(x) == is_in)
          vr0.push_back(x);
        else
          vr1.push_back(x);
      }
    }

    solve(vl0, vr0, s, !is_in);
    solve(vl1, vr1, n - s, is_in);
  }
}

void Solve(int n)
{
  init();

  std::vector<int> l, r;
  for (int i = 1; i <= n * 2; i++)
    (get(i) ? l : r).push_back(i);

  solve(l, r, n, true);
}
