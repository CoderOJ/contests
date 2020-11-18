// code by Jacder Zhang
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
#ifndef _LIB_LOOP
#define _LIB_LOOP 1

#define repe(a, b) for (int a = 0; a < (int)b.size(); a++)
#define rep(i, n) for (int i = 0; i < n; i++)
#define repa(i, n) for (int i = 1; i <= n; i++)
#define repi(i, a, b) for (int i = a; i <= b; i++)
#define repb(i, a, b) for (int i = a; i >= b; i--)

#endif /* _LIB_LOOP */
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

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

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

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

const int N = 1000005;
const int C = 11;

struct Point
{
  int x, y;
  Point (int x=0, int y=0) : x(x), y(y)
  { }
};

struct Line
{
  int k, b;
  Line (int k=0, int b=0) : k(k), b(b)
  { }

  int eval(int x)
  { return k * x + b; }

  double intersect(Line& B)
  {
    double dy = b - B.b;
    double dx = B.k - k;
    return dy / dx;
  }

  void log()
  {
    see(k, b);
  }

  static Line resolv(Point a, int k)
  { return Line(k, a.y - a.x * k); }
};

struct Lmin
{
  std::vector <Line> cand;
  int sz;
  Lmin () : sz(0)
  { }

  void insert(Line A)
  {
    while (sz > 0)
    {
      Line P  = cand[sz-1];
      if (P.k >= A.k) { sz--; cand.pop_back(); continue; }
      if (sz > 1) {
        Line PP = cand[sz-2];
        double int_pp = A.intersect( PP );
        double int_p  = A.intersect( P  );
        if (int_pp <= int_p) { sz--; cand.pop_back(); continue; }
      }
      break;
    }
    cand.push_back(A); sz++;
  }

  int get(int x)
  {
    if (sz == 0) { return 0x3f3f3f3f; }
    while (sz > 1)
    {
      Line P  = cand[sz-1];
      Line PP = cand[sz-2];
      if (P.eval(x) >= PP.eval(x)) { sz--; cand.pop_back(); continue; }
      break;
    }
    return cand[sz-1].eval(x);
  }
};

Lmin go[C][C];
int n, max_c;
int skip[N], cost[N];
int ans[N];

void preInit()
{ }

void init()
{
  n = sc.n(); max_c = sc.n();
  rep (i,n) { skip[i] = sc.n(); cost[i] = sc.n(); }
}

void solve()
{
  memset(ans, 0x3f, sizeof(ans));
  // see("Process begin");
  ans[0] = 0;
  rep (i,n)
  {
    repa (j,max_c) { checkMin(ans[i], go[j][i%j].get(i/j) ); }
    if (ans[i] != 0x3f3f3f3f)
    {
      // see(i, skip[i], cost[i], i/skip[i], ans[i]);
      Line A = Line::resolv( Point(i/skip[i],ans[i]), cost[i] );
      // A.log();
      go[ skip[i] ][ i%skip[i] ].insert( A );
    }
  }
  repa (j, max_c) { checkMin(ans[n], go[j][n%j].get(n/j) ); }
  repa (i,n) printf("%d ", (ans[i] == 0x3f3f3f3f) ? -1 : ans[i]);
}
