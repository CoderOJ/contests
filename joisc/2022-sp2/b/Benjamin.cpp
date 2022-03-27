#include "Benjamin.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

namespace {

std::string encode(int x, int n)
{
  std::string res(n, '0');
  for (int i = 0; i < n; i++)
    res[i] = (x & (1 << i)) ? '1' : '0';
  return res;
}
int decode(std::string s, int n)
{
  int res = 0;
  for (int i = 0; i < n; i++)
    if (s[i] == '1') res |= (1 << i);
  return res;
}

struct info_t
{
  int r = 0, l = 0;
  info_t() = default;
  info_t(int v) : r(v == 1), l(v == 0) {}
  info_t(int r, int l) : r(r), l(l) {}
};
info_t join(info_t lhs, info_t rhs)
{
  int sp = std::min(lhs.l, rhs.r);
  return {lhs.r + rhs.r - sp, lhs.l + rhs.l - sp};
}

const int B = 20;
int uu, vv;

}

std::string SendB(int N, int X, int Y) 
{
  if (X > Y) std::swap(X, Y);
  uu = X, vv = Y;

  // std::clog << "X = " << X << " Y = " << Y << std::endl;
  const int xb = X / B, yb = Y / B;
  const int yyb = Y / 10;
  if (yyb % 2 == 0)
    return encode(xb, 10) + encode(yb, 10);
  else
    return encode(yb, 10) + encode(xb, 10);
}

int Answer(std::string T) 
{
  // std::clog << T << std::endl;
  int ub = uu / B, vb = vv / B;
  // std::clog << "ub = " << ub << " vb = " << vb << std::endl;
  if (ub == vb)
  {
    std::vector<int> ord(B);
    for (int i = 0; i < B; i++)
      ord[i] = T[i] == '1' ? 1 : 0;
    int l = uu % B, r = vv % B;
    info_t res;
    for (int i = l; i < r; i++)
      res = join(res, ord[i]);
    return res.r + res.l;
  }
  else
  {
    vb = vv / 10;
    std::vector<int> ordl(B), ordr(10);
    for (int i = 0; i < B; i++)
      ordl[i] = T[i] == '1' ? 1 : 0;
    for (int i = 0; i < 10; i++)
      ordr[i] = T[B + i] == '1' ? 1 : 0;
    int l = uu % B, r = vv % 10;
    info_t le, ri;
    for (int i = l; i < B; i++) le = join(le, ordl[i]);
    for (int i = 0; i < r; i++) ri = join(ri, ordr[i]);
    char sig = T[B + 10];
    int cl, cr;
    if (sig == '0')
    {
      cl = decode(T.substr(B + 10 + 1, 5), 5);
      cr = decode(T.substr(B + 10 + 1 + 5, 15), 15);
    }
    else
    {
      cl = decode(T.substr(B + 10 + 1, 15), 15);
      cr = decode(T.substr(B + 10 + 1 + 15, 5), 5);
    }
    info_t mid(cl, cr);
    info_t ans = join(le, join(mid, ri));
    return ans.r + ans.l;
  }
}
