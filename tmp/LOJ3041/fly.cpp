#include "minerals.h"
#include <vector>
#include <iostream>
using namespace std;
vector<int>l, r;
int pre = 0;
void work(vector<int> &X, vector<int> &Y, bool fullx) {
  // cerr<<"[ ";for(int v:X) cerr<<v<<" ";cerr<<"], [ ";for(int v:Y) cerr<<v<<" ";cerr<<"]"<<endl;
  if (X.size() == 1 && Y.size() == 1) {
    Answer(X[0], Y[0]);
    return;
  }

  int n = X.size(), mid = min((int)((n + 1) * 0.38), n - 1);
  vector<int>xl, xr, yl, yr;

  for (int i = 0; i < mid; i++)
    xl.push_back(X[i]);

  for (int i = mid; i < n; i++)
    xr.push_back(X[i]);

  for (int v : xl)
    pre = Query(v);

  if (fullx)
    xl.swap(xr);

  for (int v : Y) {
    if (yl.size() == xl.size()) {
      yr.push_back(v);
      continue;
    }

    if (yr.size() == xr.size()) {
      yl.push_back(v);
      continue;
    }

    int u = Query(v);

    if (u == pre)
      yl.push_back(v);
    else
      yr.push_back(v), pre = u;
  }

  work(xl, yl, 1), work(xr, yr, 0);
}
void Solve(int n) {
  for (int i = 1; i <= 2 * n; i++) {
    if (Query(i) == l.size() + 1)
      l.push_back(i);
    else
      r.push_back(i);
  }

  pre = n;
  work(l, r, 1);
}
