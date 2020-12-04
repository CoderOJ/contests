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
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"

// Integer under mod

#ifndef INTM_H_
#define INTM_H_

namespace Intm {

typedef unsigned int uint32;
typedef unsigned long long uint64;

template<uint32 MOD>
struct Intm
{
  static inline uint32 _mod_red(uint32 a) { return a >= MOD ? a - MOD : a; }
  static inline void _mod_red_set(uint32& a) { a = a >= MOD ? a - MOD : a; }

  static inline uint32 power(uint32 a, uint32 b)
  {
    uint32 res = 1;
    while (b) {
      if (b & 1)
        res = 1ull * res * a % MOD;
      a = 1ull * a * a % MOD;
      b >>= 1;
    }
    return res;
  }

  static inline uint32 inv(uint32 a) { return power(a, MOD - 2); }

  inline uint32 get_2(uint32 _n)
  {
    uint32 u2 = 1, res = 0;
    while (u2 < _n) {
      u2 <<= 1;
      ++res;
    }
    return res;
  }

  uint32 a;
  Intm(uint32 a = 0)
    : a(a)
  {}
  inline Intm operator+(const Intm B) const { return Intm(_mod_red(a + B.a)); }
  inline Intm& operator+=(const Intm B)
  {
    _mod_red_set(a += B.a);
    return *this;
  }
  inline Intm operator-(const Intm B) const
  {
    return Intm(_mod_red(MOD + a - B.a));
  }
  inline Intm& operator-=(const Intm B)
  {
    _mod_red_set(a += MOD - B.a);
    return *this;
  }
  inline Intm operator*(const Intm B) const
  {
    return Intm(static_cast<uint64>(a) * B.a % MOD);
  }
  inline Intm& operator*=(const Intm B)
  {
    a = static_cast<uint64>(a) * B.a % MOD;
    return *this;
  }
  inline Intm operator/(const Intm B) const
  {
    return Intm(1ull * a * inv(B.a) % MOD);
  }
  inline Intm& operator/=(const Intm B)
  {
    a = 1ull * a * inv(B.a) % MOD;
    return *this;
  }
  inline bool operator<(const Intm B) const { return a < B.a; }
  inline Intm pow(uint32 k) const { return Intm(power(a, k)); }
  inline Intm inv() const { return Intm(inv(a)); }
  inline operator uint32() { return a; }
};
}

#endif /* INTM_H_ */
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

const int MOD = 1000000007;
typedef Intm::Intm<MOD> Int;
const int N = 1048576;
int n, l, r;

int get_2(int u) {
  int res = 0;
  while (u) {
    res++; u >>= 1; }
  return res; }

void fwt(Int a[], int n) {
  for (int l=1; l<n; l<<=1) {
    for (int i=0; i<n; i+=2*l) {
      for (int j=0; j<l; ++j) {
        int x=i+j, y=i+l+j;
        Int u=a[x], v=a[y];
        a[x] = (u+v);
        a[y] = (u-v);
} } } } 

Int a[N];
void preInit() { } void init() { } void solve() { 
  n = sc.nlm(MOD-1); l = sc.n(); r = sc.n();
  int m = 1 << get_2(r);
  repi (i,l,r) a[i] = 1;
  fwt(a,m);
  rep (i,m) a[i] = a[i].pow(n);
  fwt(a,m);
  printf("%u", static_cast<unsigned>(a[0] / Int(m)));
}
