// PARSER: begin local header '/home/jack/code/creats/gpl.h'
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
// PARSER: end local header '/home/jack/code/creats/gpl.h'

// PARSER: begin local header '/home/jack/code/creats/Scanner.h'

#ifndef _LIB_SCANNER
#define _LIB_SCANNER 1
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
  inline bool isWS(char t) { return t == ' ' || t == '\n'; }
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
#endif /* _LIB_SCANNER */
// PARSER: end local header '/home/jack/code/creats/Scanner.h'
// PARSER: begin local header '/home/jack/code/creats/base.h'
#ifndef _LIB_BASE
#define _LIB_BASE 1

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

#endif /* _LIB_BASE */
// PARSER: end local header '/home/jack/code/creats/base.h'
// PARSER: begin local header '/home/jack/code/creats/log.h'
#ifndef _LIB_LOG
#define _LIB_LOG 1

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

#endif /* _LIB_LOG */
// PARSER: end local header '/home/jack/code/creats/log.h'
// PARSER: begin local header '/home/jack/code/creats/loop.h'
#ifndef _LIB_LOOP
#define _LIB_LOOP 1

#define repe(a, b) for (int a = 0; a < (int)b.size(); a++)
#define rep(i, n) for (int i = 0; i < n; i++)
#define repa(i, n) for (int i = 1; i <= n; i++)
#define repi(i, a, b) for (int i = a; i <= b; i++)
#define repb(i, a, b) for (int i = a; i >= b; i--)

#endif /* _LIB_LOOP */
// PARSER: end local header '/home/jack/code/creats/loop.h'

// #include "/home/jack/code/creats/STree.h"
// PARSER: begin local header '/home/jack/code/creats/Tree.h'
#ifndef _LIB_TREE
#define _LIB_TREE

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

#endif /* _LIB_TREE */
// PARSER: end local header '/home/jack/code/creats/Tree.h'
// #include "/home/jack/code/creats/Graph.h"
// PARSER: begin local header '/home/jack/code/creats/Intm.h'

// Integer under mod

#ifndef _LIB_INTM
#define _LIB_INTM

namespace Intm {
class Intm
{
private:
  static unsigned long long MOD;
  static unsigned long long k;
  unsigned long long a;

public:
  inline static void setMod(const unsigned long long _MOD)
  {
    MOD = _MOD;
    k = (unsigned long long)(-1) / _MOD;
  }
  inline static void getModSub(unsigned long long& a)
  {
    if (a >= MOD)
      a -= MOD;
  }
  inline static void getMod(unsigned long long& a)
  {
    a = a - (unsigned long long)((__uint128_t(k) * a) >> 64) * MOD;
  }
  inline static unsigned long long power(unsigned long long a,
                                         unsigned long long b)
  {
    unsigned long long r = 1;
    while (b) {
      if (b & 1)
        getMod(r *= a);
      getMod(a *= a);
      b >>= 1;
    }
    return r;
  }

  Intm() { a = 0; }
  Intm(unsigned long long _a)
    : a(_a)
  {
    getMod(a);
  }
  Intm& operator+=(const Intm b)
  {
    a += b.a;
    getModSub(a);
    return *this;
  }
  Intm operator+(const Intm b) const
  {
    Intm R(a);
    return (R += b);
  }
  Intm& operator-=(const Intm b)
  {
    a += MOD - b.a;
    getModSub(a);
    return *this;
  }
  Intm operator-(const Intm b) const
  {
    Intm R(a);
    return (R -= b);
  }
  Intm& operator*=(const Intm b)
  {
    a *= b.a;
    getMod(a);
    return *this;
  }
  Intm operator*(const Intm b) const
  {
    Intm R(a);
    return (R *= b);
  }
  Intm& operator/=(const Intm b)
  {
    a *= power(b.a, MOD - 2);
    getMod(a);
    return *this;
  }
  Intm operator/(const Intm b) const
  {
    Intm R(a);
    return (R /= b);
  }
  Intm pow(int e) { return Intm(power(a, e)); }
  operator int()
  {
    getModSub(a);
    return (int)a;
  }
};
unsigned long long Intm::MOD;
unsigned long long Intm::k;
}

#endif /* _LIB_INTM */
// PARSER: end local header '/home/jack/code/creats/Intm.h'

#include <bits/stdc++.h>

// PARSER: begin local header '/home/jack/code/creats/body.h'
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
#ifdef _LIB_SCANNER
  T = sc.nextInt();
#else
  scanf("%d", &T);
#endif /* _LIB_SCANNER */
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
// PARSER: end local header '/home/jack/code/creats/body.h'

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

using namespace Tree;
typedef Intm::Intm Int;
const int N = 200005;
TreeLca<N> T;

Int fac[N];

void
preInit()
{
  Int::setMod(998244353);
  fac[0] = 1;
  repa(i, N - 1) fac[i] = fac[i - 1] * Int(i);
}

Int
nCr(int n, int r)
{
  return fac[n] / fac[r] / fac[n - r];
}

void
init()
{
  int n = sc.n();
  rep(i, n - 1)
  {
    int u = sc.n(), v = sc.n();
    T.addEdge(u, v);
  }
  T.initLca(1);
}

void
solve()
{
  int q = sc.n();
  while (q--) {
    int u = sc.n(), v = sc.n();
    int l = T.lca(u, v);
    int x = T.d[u] - T.d[l], y = T.d[v] - T.d[l];
    printf("%u\n", static_cast<unsigned>(nCr(x + y, x) / Int(2).pow(x + y)));
  }
}
