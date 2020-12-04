// Copyright (C) 2020 JacderZhang
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#ifndef SCANNER_H_
#define SCANNER_H_ 1
#include <stdio.h>
#include <stdlib.h>
class Scanner
{
private:
  static const int BUFFER_SIZE = 10000;
  char buff[BUFFER_SIZE];
  int buffPos, buffLim;

public:
  Scanner()
  {
    buffLim = fread(buff, 1, BUFFER_SIZE, stdin);
    buffPos = 0;
  }

private:
  inline void flushBuff()
  {
    buffLim = fread(buff, 1, BUFFER_SIZE, stdin);
    if (buffLim == 0) {
      buff[buffLim++] = '\n';
    }
    buffPos = 0;
  }
  inline bool isWS(char t) { return t <= ' '; }
  inline bool isDig(char t) { return t >= '0' && t <= '9'; }
  void nextPos()
  {
    buffPos++;
    if (buffPos == buffLim) {
      flushBuff();
    }
  }
#define getChar() buff[buffPos]
public:
  inline char getchar()
  {
    char ch = getChar();
    nextPos();
    return ch;
  }
  inline void next(char* s)
  {
    while (isWS(getChar())) {
      nextPos();
    }
    while (!isWS(getChar())) {
      *s = getChar();
      s++;
      nextPos();
    }
    *s = '\0';
  }
  inline void nextLine(char* s)
  {
    while (getChar() != '\n') {
      nextPos();
    }
    if (getChar() == '\n') {
      nextPos();
    }
    while (getChar() != '\n') {
      *s = getChar();
      s++;
      buffPos++;
    }
    *s = '\0';
  }
  inline int nextInt()
  {
    while (!isDig(getChar()) && getChar() != '-') {
      nextPos();
    }
    int sign = (getChar() == '-') ? nextPos(), -1 : 1;
    int res = 0;
    while (isDig(getChar())) {
      res = res * 10 + getChar() - '0';
      nextPos();
    }
    return res * sign;
  }
  inline long long nextLong()
  {
    while (!isDig(getChar()) && getChar() != '-') {
      nextPos();
    }
    long long sign = (getChar() == '-') ? nextPos(), -1 : 1;
    long long res = 0;
    while (isDig(getChar())) {
      res = res * 10 + getChar() - '0';
      nextPos();
    }
    return res * sign;
  }
  inline int n()
  {
    while (getChar() < '0' || getChar() > '9') {
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff();
      }
    }
    int res = 0;
    while (getChar() >= '0' && getChar() <= '9') {
      res = res * 10 + (getChar() - '0');
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff();
      }
    }
    return res;
  }
  inline long long nl()
  {
    while (getChar() < '0' || getChar() > '9') {
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff();
      }
    }
    long long res = 0;
    while (getChar() >= '0' && getChar() <= '9') {
      res = res * 10 + (getChar() - '0');
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff();
      }
    }
    return res;
  }
  inline long long nlm(const int MOD)
  {
    while (getChar() < '0' || getChar() > '9') {
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff();
      }
    }
    long long res = 0;
    while (getChar() >= '0' && getChar() <= '9') {
      res = (res * 10 + (getChar() - '0')) % MOD;
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff();
      }
    }
    return res;
  }
  inline double nextDouble()
  {
    while (isWS(getChar())) {
      nextPos();
    }
    int sign = (getChar() == '-') ? nextPos(), -1 : 1;
    double res = 0;
    while (isDig(getChar())) {
      res = res * 10 + getChar() - '0';
      nextPos();
    }
    if (getChar() == '.') {
      nextPos();
      double ep = 1;
      while (isDig(getChar())) {
        ep *= 0.1;
        res += ep * (getChar() - '0');
        nextPos();
      }
    }
    return sign * res;
  }
  inline char nextChar()
  {
    while (isWS(getChar()))
      nextPos();
    char res = getChar();
    nextPos();
    return res;
  }
#undef getChar
};
Scanner sc;
#endif /* SCANNER_H_ */
#ifndef LOG_H_
#define LOG_H_ 1

#include <iostream>

#ifdef __LOCALE__
template<typename T>
void
__ses(T a)
{
  std::cout << a << " ";
}
template<typename T, typename... Args>
void
__ses(T a, Args... b)
{
  std::cout << a << " ";
  __ses(b...);
}
#define ses(...)                                                               \
  {                                                                            \
    std::cout << #__VA_ARGS__ << " = ";                                        \
    __ses(__VA_ARGS__);                                                        \
  }
#define see(...)                                                               \
  {                                                                            \
    ses(__VA_ARGS__);                                                          \
    std::cout << std::endl;                                                    \
  }
#define slog(format, ...) printf(format, __VA_ARGS__)
#else
#define see(...)
#define ses(...)
#define slog(format, ...)
#endif

template<class _Type>
void
logArray(_Type a[], int n)
{
  for (int i = 0; i < n; ++i)
    std::cout << a[i] << ' ';
  std::cout << std::endl;
}

#endif /* LOG_H_ */
#ifndef LOOP_H_
#define LOOP_H_ 1

#define repe(a, b) for (int a = 0; a < (int)b.size(); a++)
#define rep(i, n) for (int i = 0; i < n; i++)
#define repa(i, n) for (int i = 1; i <= n; i++)
#define repi(i, a, b) for (int i = a; i <= b; i++)
#define repb(i, a, b) for (int i = a; i >= b; i--)

#endif /* LOOP_H_ */
#ifndef BASE_H_
#define BASE_H_ 1

template<class T>
inline bool
checkMin(T& a, T b)
{
  return (a > b ? a = b, 1 : 0);
}
template<class T>
inline bool
checkMax(T& a, T b)
{
  return (a < b ? a = b, 1 : 0);
}

#endif /* BASE_H_ */
// #include "/home/jack/code/creats/STree.h"
#ifndef TREE_H_
#define TREE_H_

#include <cstring>
#include <iterator>

namespace Tree {

template<int N>
class TreeBase
{
public:
  int ef[N], en[N * 2], ev[N * 2], ec;
  TreeBase()
  {
    memset(ef, -1, sizeof(ef));
    memset(en, -1, sizeof(en));
    ec = 0;
  }
  void addEdge(int u, int v)
  {
    en[ec] = ef[u];
    ef[u] = ec;
    ev[ec] = v;
    ec++;
    en[ec] = ef[v];
    ef[v] = ec;
    ev[ec] = u;
    ec++;
  }

  class Edges
  {
  protected:
    int id;
    const TreeBase* th;

  public:
    Edges(int id, const TreeBase* th)
      : id(id)
      , th(th)
    {}
    class iterator : public std::iterator<std::input_iterator_tag, int>
    {
    protected:
      int eid;
      const TreeBase* th;

    public:
      iterator(int _eid, const TreeBase* th)
        : eid(_eid)
        , th(th)
      {}
      iterator& operator++()
      {
        eid = th->en[eid];
        return *this;
      }
      bool operator!=(iterator b) const { return eid != b.eid; }
      int operator*() const { return eid; }
    };
    iterator begin() { return iterator(id, th); }
    iterator end() { return iterator(-1, th); }
  };
  Edges getEdges(int u) { return Edges(ef[u], this); }

  class Nodes
  {
  protected:
    int id;
    const TreeBase* th;

  public:
    Nodes(int id, const TreeBase* th)
      : id(id)
      , th(th)
    {}
    class iterator : public std::iterator<std::input_iterator_tag, int>
    {
    protected:
      int eid;
      const TreeBase* th;

    public:
      iterator(int _eid, const TreeBase* th)
        : eid(_eid)
        , th(th)
      {}
      iterator& operator++()
      {
        eid = th->en[eid];
        return *this;
      }
      bool operator!=(iterator b) const { return eid != b.eid; }
      int operator*() const { return th->ev[eid]; }
    };
    iterator begin() { return iterator(id, th); }
    iterator end() { return iterator(-1, th); }
  };
  Nodes getNodes(int u) { return Nodes(ef[u], this); }
};

template<int N>
class TreeDfn : virtual public TreeBase<N>
{
protected:
  int dfnCnt;

public:
  using TreeBase<N>::ev;
  using TreeBase<N>::getNodes;

  int dfnL[N], dfnR[N];
  TreeDfn() { dfnCnt = 0; }
  void getDfn(int u, int f = 0)
  {
    dfnL[u] = dfnCnt++;
    auto vs = getNodes(u);
    for (auto v : vs)
      if (v != f) {
        getDfn(v, u);
      }
    dfnR[u] = dfnCnt;
  }
};

template<int N>
class TreeLca : virtual public TreeBase<N>
{
protected:
  static const int B = 24;

public:
  using TreeBase<N>::ev;
  using TreeBase<N>::getNodes;
  int fa[N][B], d[N];

  TreeLca()
  {
    memset(fa, 0, sizeof(fa));
    memset(d, 0, sizeof(d));
  }
  void initLca(int u, int f = 0)
  {
    d[u] = d[f] + 1;
    fa[u][0] = f;
    for (int i = 0; i < B - 1; i++) {
      fa[u][i + 1] = fa[fa[u][i]][i];
    }
    auto vs = getNodes(u);
    for (auto v : vs)
      if (v != f) {
        initLca(v, u);
      }
  }
  int up(int u, int d)
  {
    for (int i = 0; i < B; i++) {
      if ((d >> i) & 1) {
        u = fa[u][i];
      }
    }
    return u;
  }
  int lca(int u, int v)
  {
    if (d[u] < d[v]) {
      int tmp = u;
      u = v;
      v = tmp;
    }
    u = up(u, d[u] - d[v]);
    for (int i = B - 1; i >= 0; i--) {
      if (fa[u][i] != fa[v][i]) {
        u = fa[u][i];
        v = fa[v][i];
      }
    }
    return u == v ? u : fa[u][0];
  }
};

}

#endif /* TREE_H_ */
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#ifndef _BODY_MAIN
#define _BODY_MAIN 1

#ifndef CUSTOM_MAIN
void
preInit();
void
init();
void
solve();
int32_t
main()
{
  preInit();
#ifdef MULTIPLE_TEST_CASES_WITH_T
  int T;
#ifdef SCANNER_H_
  T = sc.nextInt();
#else
  scanf("%d", &T);
#endif /* SCANNER_H_ */
  while (T--) {
    init();
    solve();
  }
#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T
  while (1) {
    try {
      init();
    } catch (bool t) {
      return 0;
    }
    solve();
  }
#else
  init();
  solve();
#endif /* MULTIPLE_TEST_CASES_WITHOUT_T  */
#endif /* MULTIPLE_TEST_CASES_WITH_T */
  return 0;
}
#endif /* CUSTOM_MAIN */

#endif /* _BODY_MAIN */
// #define int long long

/** My code begins here **/

using namespace Tree;
const int N = 50005;
TreeLca<N> T;
std::vector< std::pair<int,int> > es[N];
int dp[N][2], n, m;

int getUp(int uu, int aa) {
  if (uu == aa) { return 0; }
  int u = uu, s = -1;
  int res = 0;
  while (u != aa) {
    res += dp[u][0];
    if (s != -1) { res -= std::max(dp[s][0], dp[s][1]); } 
    s = u; u = T.fa[u][0]; }
  res -= std::max(dp[s][0], dp[s][1]); 
  return res; }


void dfs(int u, int f) {
  dp[u][0] = dp[u][1] = 0;
  auto vs = T.getNodes(u);
  for (int v: vs) if (v!=f) { dfs(v,u); dp[u][0] += std::max(dp[v][0], dp[v][1]); }
  for (auto p: es[u]) { checkMax(dp[u][1], dp[u][0] + getUp(p.first, u) + getUp(p.second, u) + 1); }
  see(u, dp[u][0], dp[u][1]);
}

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); T.addEdge(u,v); }
  T.initLca(1);
  rep (i,m) { int u=sc.n(), v=sc.n(); es[T.lca(u,v)].push_back( std::make_pair(u,v) ); }
} void solve() {
  dfs(1,0);
  printf("%d\n", std::max(dp[1][0], dp[1][1])) ;
}
