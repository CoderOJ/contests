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
// #include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/log.h"
// #include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
// #include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

typedef long long LL;
typedef unsigned long long ULL;

constexpr LL GEN_HELP = (1LL << 40) - 1;

constexpr int BIT = 14;
constexpr int SHIFT_2 = BIT;
constexpr int SHIFT_3 = BIT + BIT;
constexpr int N = 1 << BIT;
constexpr int BASE = N - 1;
constexpr LL BASE1 = N - 1;
constexpr LL BASE2 = BASE1 << BIT;
constexpr LL BASE3 = BASE2 << BIT;
constexpr LL MOD = 1000000007;
ULL a1[N], a2[N], a3[N];

constexpr __uint128_t MOD_K = static_cast<ULL>(-1) / MOD;
inline void checkMod(ULL& a) {
  a -= (ULL)((MOD_K * a) >> 64) * MOD;
}

int
main()
{
  int T = sc.n();
  LL x = sc.n();
  std::mt19937_64 rd(sc.n());

  a1[0] = a2[0] = a3[0] = 1;
  for (int i = 1; i < N; ++i)
    checkMod( a1[i] = a1[i - 1] * x );
  ULL base_2 = a1[BASE] * x % MOD;
  for (int i = 1; i < N; ++i)
    checkMod( a2[i] = a2[i - 1] * base_2 );
  ULL base_3 = a2[BASE] * base_2 % MOD;
  for (int i = 1; i < N; ++i)
    checkMod( a3[i] = a3[i - 1] * base_3 );

  ULL k,res1,ans=0;
  while (T--) {
    k = rd() & GEN_HELP;
    res1 = a1[k & BASE1];
#define     res2  a2[(k & BASE2) >> SHIFT_2]
#define     res3  a3[(k & BASE3) >> SHIFT_3]
    checkMod( res1 *= res2 );
    checkMod( res1 *= res3 );
    if (res1>=MOD) { res1-=MOD; }
    ans ^= res1;
  }
  printf("%lld\n", ans);
  return 0;
}
