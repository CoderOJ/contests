#include "/home/jack/cm/debug"
# include "City_lib.h"
#include <algorithm>
#include <utility>
#include <vector>

const int    kMaxN     = 250000;
const int    kMaxDepth = 18;
const double kRatio    = 1.05;

static std::vector<int> graph[kMaxN];
static std::vector<int> widths;

static int lf[kMaxN], rg[kMaxN], last_id;

void SetWidths()
{
  int w = 1;
  widths.clear();
  widths.push_back((int)w);
  int times = kMaxDepth + 1;
  while (times > 0)
  {
    int w2 = static_cast<int>(w * kRatio);
    if (w == w2)
      ++w2;
    widths.push_back(w2);
    if (w2 > kMaxN)
    {
      --times;
    }
    w = w2;
  }
}

int ceiling(int w)
{
  return *(lower_bound(widths.begin(), widths.end(), w));
}

void visit(int p, int rt)
{
  lf[p] = last_id++;
  for (int q : graph[p])
    if (q != rt)
      visit(q, p);
  rg[p] = last_id = lf[p] + ceiling(last_id - lf[p]);
}

void Encode(int N, int A[], int B[])
{
  SetWidths();
  for (int i = 0; i < N - 1; ++i)
  {
    graph[A[i]].push_back(B[i]);
    graph[B[i]].push_back(A[i]);
  }
  last_id = 0;
  visit(0, -1);
  for (int i = 0; i < N; ++i)
  {
    int wc = static_cast<int>(std::distance(
        widths.begin(),
        std::lower_bound(widths.begin(), widths.end(), rg[i] - lf[i])));

    long long code = static_cast<long long>(lf[i]) * widths.size() + wc;
    see(i, code);
    Code(i, code);
  }
}

void InitDevice()
{
  SetWidths();
}

std::pair<int, int> range(long long code)
{
  int left = (int)(code / widths.size());
  int w    = widths[(int)(code % widths.size())];
  return {left, left + w};
}

int Answer(long long S, long long T)
{
  std::pair<int, int> X = range(S), Y = range(T);
  if (Y.first <= X.first && X.second <= Y.second)
    return 0;
  if (X.first <= Y.first && Y.second <= X.second)
    return 1;
  return 2;
}
