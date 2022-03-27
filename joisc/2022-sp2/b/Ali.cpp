#include "Ali.h"
#include <string>
#include <vector>
#include <iostream>

namespace 
{

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

const int N = 20005;
const int B = 20;

std::vector<int> e[N];

int dfn[N], dfn_cur;
int ord[N];

void dfs(int u, int f)
{
  dfn[u] = dfn_cur++;
  ord[dfn[u]] = 0;
  for (int v : e[u]) if (v != f) dfs(v, u);
  ord[dfn_cur++] = 1;
}

}

void Init(int N, std::vector<int> U, std::vector<int> V) 
{
  for (int i = 0; i < N; i++) e[i].clear();
  for (int i = 0; i < N - 1; i++) { 
    e[U[i]].push_back(V[i]); e[V[i]].push_back(U[i]); }
  dfn_cur = 0;
  dfs(0, 0);
  for (int i = 0; i < N; i++)
    SetID(i, dfn[i] + 1);
}

std::string SendA(std::string S) 
{
  int x = decode(S.substr(0, 10), 10);
  int y = decode(S.substr(10, 10), 10);
  int yyy = 0;
  if (x > y)
  {
    std::swap(x, y);
    yyy = 1;
  }

  // std::clog << "x = " << x << " y = " << y << std::endl;

  if (x == y)
  {
    std::string res(B, '0');
    for (int i = 0; i < B; i++)
      res[i] = ord[x * B + i] ? '1' : '0';
    return res;
  }
  else
  {
    std::string res(B + 10, '0');
    for (int i = 0; i < B; i++)
      res[i] = ord[x * B + i] ? '1' : '0';
    y = y * 2 + yyy;
    for (int i = 0; i < 10; i++)
      res[B + i] = ord[y * 10 + i] ? '1' : '0';

    info_t mid(0, 0);
    for (int i = (x + 1) * B; i < y * 10; i++)
      mid = join(mid, info_t(ord[i]));
    if (mid.r >= 31 && mid.l >= 31)
    {
      mid.l += mid.r - 31;
      mid.r = 31;
      res += "0";
      res += encode(mid.r, 5);
      res += encode(mid.l, 15);
    }
    else if (mid.r < 31)
    {
      res += "0";
      res += encode(mid.r, 5);
      res += encode(mid.l, 15);
    }
    else
    {
      res += "1";
      res += encode(mid.r, 15);
      res += encode(mid.l, 5);
    }
    return res;
  }
}
