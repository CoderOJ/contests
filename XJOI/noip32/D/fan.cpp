#pragma GCC optimize(2, 3, "Ofast")
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
#endif /* SCANNER_H_ */
// PARSER: end local header '/home/jack/code/creats/Scanner.h'
// PARSER: begin local header '/home/jack/code/creats/base.h'
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
// PARSER: end local header '/home/jack/code/creats/base.h'
// PARSER: begin local header '/home/jack/code/creats/log.h'
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
// PARSER: end local header '/home/jack/code/creats/log.h'
// PARSER: begin local header '/home/jack/code/creats/loop.h'
#ifndef LOOP_H_
#define LOOP_H_ 1

#define repe(a, b) for (int a = 0; a < (int)b.size(); a++)
#define rep(i, n) for (int i = 0; i < n; i++)
#define repa(i, n) for (int i = 1; i <= n; i++)
#define repi(i, a, b) for (int i = a; i <= b; i++)
#define repb(i, a, b) for (int i = a; i >= b; i--)

#endif /* LOOP_H_ */
// PARSER: end local header '/home/jack/code/creats/loop.h'
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
// PARSER: end local header '/home/jack/code/creats/body.h'
#define double long double
#define _DPair_AK_IOI_FOR_1482698412_TIMES_ !
#define _TrainDriver_AK_IOI_FOR_1010291609_TIMES_ "%.2Lf"
#define _xyf007_AK_IOI_FOR_110861811_TIMES_ "/home/jack/code/Math/Poly/main.h"
#define _xyf007_AK_IOI_FOR_88803598_TIMES_ "/home/jack/code/creats/Graph.h"
#define _xyf007_AK_IOI_FOR_1694230426_TIMES_ "/home/jack/code/creats/Intm.h"
#define _TrumpConstructChina_AK_IOI_FOR_1024957025_TIMES_ "/home/jack/code/creats/STree.h"
#define _SevenDawns_AK_IOI_FOR_229618766_TIMES_ "/home/jack/code/creats/Tree.h"
#define _XXY_AK_IOI_FOR_262026554_TIMES_ #define
#define _zhouchenyuan_AK_IOI_FOR_95694559_TIMES_ #include
#define _hahazhou_AK_IOI_FOR_566965399_TIMES_ %
#define _TrumpConstructChina_AK_IOI_FOR_2100880736_TIMES_ &
#define _DragonInBed_AK_IOI_FOR_1402095734_TIMES_ &&
#define _TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_ (
#define _xYix_AK_IOI_FOR_573398315_TIMES_ )
#define _quest_AK_IOI_FOR_77574280_TIMES_ *
#define _DragonInBed_AK_IOI_FOR_525090119_TIMES_ ++
#define _rayleigh_AK_IOI_FOR_1424014129_TIMES_ +=
#define _qy_AK_IOI_FOR_455217855_TIMES_ ,
#define _Flying2018_AK_IOI_FOR_862725109_TIMES_ -
#define _fAKe_AK_IOI_FOR_122262044_TIMES_ -=
#define _Clovers_AK_IOI_FOR_1918690274_TIMES_ .
#define _DPair_AK_IOI_FOR_1708922970_TIMES_ /
#define _Clovers_AK_IOI_FOR_1481425600_TIMES_ 0
#define _Clovers_AK_IOI_FOR_431155640_TIMES_ 1
#define _shenmadongdong_AK_IOI_FOR_1840430665_TIMES_ 10005
#define _xYix_AK_IOI_FOR_2078483973_TIMES_ :
#define _WH_AK_IOI_FOR_604477577_TIMES_ ;
#define _SevenDawns_AK_IOI_FOR_130882885_TIMES_ <
#define _fAKe_AK_IOI_FOR_1362107475_TIMES_ =
#define _DPair_AK_IOI_FOR_1355072424_TIMES_ >
#define _hahazhou_AK_IOI_FOR_550466775_TIMES_ >=
#define _quest_AK_IOI_FOR_95419856_TIMES_ ?
#define _Point_King_AK_IOI_FOR_664658011_TIMES_ MULTIPLE_TEST_CASES_WITHOUT_T
#define _SevenDawns_AK_IOI_FOR_152029492_TIMES_ MULTIPLE_TEST_CASES_WITH_T
#define _DragonInBed_AK_IOI_FOR_879844210_TIMES_ My
#define _ZK_AK_IOI_FOR_206256057_TIMES_ N
#define _DPair_AK_IOI_FOR_2000033307_TIMES_ [
#define _XXY_AK_IOI_FOR_478227449_TIMES_ ]
#define _517_AK_IOI_FOR_1439785439_TIMES_ a
#define _REM_001_AK_IOI_FOR_1990135450_TIMES_ ans
#define _rayleigh_AK_IOI_FOR_836142550_TIMES_ begins
#define _Point_King_AK_IOI_FOR_87042435_TIMES_ break
#define _wuyiqi_AK_IOI_FOR_1874480195_TIMES_ code
#define _SevenDawns_AK_IOI_FOR_106030798_TIMES_ const
#define _qy_AK_IOI_FOR_390271333_TIMES_ cur
#define _qy_AK_IOI_FOR_1015014744_TIMES_ cur_have
#define _REM_001_AK_IOI_FOR_989490635_TIMES_ double
#define _zhoukangyang_AK_IOI_FOR_539398985_TIMES_ else
#define _hahazhou_AK_IOI_FOR_1041970667_TIMES_ full
#define _REM_001_AK_IOI_FOR_1753796212_TIMES_ full_cnt
#define _RuiR_AK_IOI_FOR_1655714095_TIMES_ here
#define _TrainDriver_AK_IOI_FOR_1382158589_TIMES_ i
#define _MYY_AK_IOI_FOR_1571120419_TIMES_ if
#define _xyf007_AK_IOI_FOR_1888699476_TIMES_ inc
#define _DragonInBed_AK_IOI_FOR_23191530_TIMES_ init
#define _SevenDawns_AK_IOI_FOR_1923400459_TIMES_ inline
#define _zhoukangyang_AK_IOI_FOR_1046994768_TIMES_ int
#define _TrumpConstructChina_AK_IOI_FOR_1931795874_TIMES_ k
#define _XXY_AK_IOI_FOR_1584475068_TIMES_ long
#define _hahazhou_AK_IOI_FOR_519645369_TIMES_ m
#define _ZK_AK_IOI_FOR_1620529320_TIMES_ n
#define _DragonInBed_AK_IOI_FOR_1115364227_TIMES_ pos
#define _xyf007_AK_IOI_FOR_1803081964_TIMES_ preInit
#define _Point_King_AK_IOI_FOR_2105342204_TIMES_ printf
#define _devinWang_AK_IOI_FOR_1520752260_TIMES_ rem
#define _zjjws_AK_IOI_FOR_107881622_TIMES_ rep
#define _Clovers_AK_IOI_FOR_94158900_TIMES_ sc
#define _DragonInBed_AK_IOI_FOR_137908341_TIMES_ solve
#define _WH_AK_IOI_FOR_938240885_TIMES_ static_cast
#define _Wallace_AK_IOI_FOR_1020529550_TIMES_ t
#define _Clovers_AK_IOI_FOR_623479626_TIMES_ void
#define _REM_001_AK_IOI_FOR_1569043394_TIMES_ while
#define _SmilingKnight_AK_IOI_FOR_444059537_TIMES_ {
#define _fAKe_AK_IOI_FOR_167908422_TIMES_ }
_DPair_AK_IOI_FOR_1708922970_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_zhouchenyuan_AK_IOI_FOR_95694559_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1024957025_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_zhouchenyuan_AK_IOI_FOR_95694559_TIMES_
_SevenDawns_AK_IOI_FOR_229618766_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_zhouchenyuan_AK_IOI_FOR_95694559_TIMES_
_xyf007_AK_IOI_FOR_88803598_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_zhouchenyuan_AK_IOI_FOR_95694559_TIMES_
_xyf007_AK_IOI_FOR_1694230426_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_zhouchenyuan_AK_IOI_FOR_95694559_TIMES_
_xyf007_AK_IOI_FOR_110861811_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_XXY_AK_IOI_FOR_262026554_TIMES_
_SevenDawns_AK_IOI_FOR_152029492_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_XXY_AK_IOI_FOR_262026554_TIMES_
_Point_King_AK_IOI_FOR_664658011_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_XXY_AK_IOI_FOR_262026554_TIMES_
_zhoukangyang_AK_IOI_FOR_1046994768_TIMES_
_XXY_AK_IOI_FOR_1584475068_TIMES_
_XXY_AK_IOI_FOR_1584475068_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_quest_AK_IOI_FOR_77574280_TIMES_
_quest_AK_IOI_FOR_77574280_TIMES_
_DragonInBed_AK_IOI_FOR_879844210_TIMES_
_wuyiqi_AK_IOI_FOR_1874480195_TIMES_
_rayleigh_AK_IOI_FOR_836142550_TIMES_
_RuiR_AK_IOI_FOR_1655714095_TIMES_
_quest_AK_IOI_FOR_77574280_TIMES_
_quest_AK_IOI_FOR_77574280_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_Clovers_AK_IOI_FOR_623479626_TIMES_
_xyf007_AK_IOI_FOR_1803081964_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_SmilingKnight_AK_IOI_FOR_444059537_TIMES_
_fAKe_AK_IOI_FOR_167908422_TIMES_
_SevenDawns_AK_IOI_FOR_106030798_TIMES_
_zhoukangyang_AK_IOI_FOR_1046994768_TIMES_
_ZK_AK_IOI_FOR_206256057_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_shenmadongdong_AK_IOI_FOR_1840430665_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_zhoukangyang_AK_IOI_FOR_1046994768_TIMES_
_517_AK_IOI_FOR_1439785439_TIMES_
_DPair_AK_IOI_FOR_2000033307_TIMES_
_ZK_AK_IOI_FOR_206256057_TIMES_
_XXY_AK_IOI_FOR_478227449_TIMES_
_qy_AK_IOI_FOR_455217855_TIMES_
_ZK_AK_IOI_FOR_1620529320_TIMES_
_qy_AK_IOI_FOR_455217855_TIMES_
_hahazhou_AK_IOI_FOR_519645369_TIMES_
_qy_AK_IOI_FOR_455217855_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1931795874_TIMES_
_qy_AK_IOI_FOR_455217855_TIMES_
_Wallace_AK_IOI_FOR_1020529550_TIMES_
_qy_AK_IOI_FOR_455217855_TIMES_
_REM_001_AK_IOI_FOR_1753796212_TIMES_
_qy_AK_IOI_FOR_455217855_TIMES_
_hahazhou_AK_IOI_FOR_1041970667_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_Clovers_AK_IOI_FOR_623479626_TIMES_
_DragonInBed_AK_IOI_FOR_23191530_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_SmilingKnight_AK_IOI_FOR_444059537_TIMES_
_ZK_AK_IOI_FOR_1620529320_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_Clovers_AK_IOI_FOR_94158900_TIMES_
_Clovers_AK_IOI_FOR_1918690274_TIMES_
_ZK_AK_IOI_FOR_1620529320_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_hahazhou_AK_IOI_FOR_519645369_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_Clovers_AK_IOI_FOR_94158900_TIMES_
_Clovers_AK_IOI_FOR_1918690274_TIMES_
_ZK_AK_IOI_FOR_1620529320_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1931795874_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_Clovers_AK_IOI_FOR_94158900_TIMES_
_Clovers_AK_IOI_FOR_1918690274_TIMES_
_ZK_AK_IOI_FOR_1620529320_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_Wallace_AK_IOI_FOR_1020529550_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_DPair_AK_IOI_FOR_1482698412_TIMES_
_Clovers_AK_IOI_FOR_94158900_TIMES_
_Clovers_AK_IOI_FOR_1918690274_TIMES_
_ZK_AK_IOI_FOR_1620529320_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_zjjws_AK_IOI_FOR_107881622_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_TrainDriver_AK_IOI_FOR_1382158589_TIMES_
_qy_AK_IOI_FOR_455217855_TIMES_
_ZK_AK_IOI_FOR_1620529320_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_hahazhou_AK_IOI_FOR_1041970667_TIMES_
_rayleigh_AK_IOI_FOR_1424014129_TIMES_
_517_AK_IOI_FOR_1439785439_TIMES_
_DPair_AK_IOI_FOR_2000033307_TIMES_
_TrainDriver_AK_IOI_FOR_1382158589_TIMES_
_XXY_AK_IOI_FOR_478227449_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_Clovers_AK_IOI_FOR_94158900_TIMES_
_Clovers_AK_IOI_FOR_1918690274_TIMES_
_ZK_AK_IOI_FOR_1620529320_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_REM_001_AK_IOI_FOR_1753796212_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1931795874_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_hahazhou_AK_IOI_FOR_1041970667_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_quest_AK_IOI_FOR_77574280_TIMES_
_ZK_AK_IOI_FOR_1620529320_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1931795874_TIMES_
_hahazhou_AK_IOI_FOR_566965399_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_hahazhou_AK_IOI_FOR_1041970667_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_fAKe_AK_IOI_FOR_167908422_TIMES_
_SevenDawns_AK_IOI_FOR_1923400459_TIMES_
_Clovers_AK_IOI_FOR_623479626_TIMES_
_xyf007_AK_IOI_FOR_1888699476_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_zhoukangyang_AK_IOI_FOR_1046994768_TIMES_
_TrumpConstructChina_AK_IOI_FOR_2100880736_TIMES_
_517_AK_IOI_FOR_1439785439_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_SmilingKnight_AK_IOI_FOR_444059537_TIMES_
_517_AK_IOI_FOR_1439785439_TIMES_
_DragonInBed_AK_IOI_FOR_525090119_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_517_AK_IOI_FOR_1439785439_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_517_AK_IOI_FOR_1439785439_TIMES_
_hahazhou_AK_IOI_FOR_550466775_TIMES_
_ZK_AK_IOI_FOR_1620529320_TIMES_
_quest_AK_IOI_FOR_95419856_TIMES_
_517_AK_IOI_FOR_1439785439_TIMES_
_Flying2018_AK_IOI_FOR_862725109_TIMES_
_ZK_AK_IOI_FOR_1620529320_TIMES_
_xYix_AK_IOI_FOR_2078483973_TIMES_
_517_AK_IOI_FOR_1439785439_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_fAKe_AK_IOI_FOR_167908422_TIMES_
_Clovers_AK_IOI_FOR_623479626_TIMES_
_DragonInBed_AK_IOI_FOR_137908341_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_SmilingKnight_AK_IOI_FOR_444059537_TIMES_
_zhoukangyang_AK_IOI_FOR_1046994768_TIMES_
_DragonInBed_AK_IOI_FOR_1115364227_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_Clovers_AK_IOI_FOR_1481425600_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_zhoukangyang_AK_IOI_FOR_1046994768_TIMES_
_devinWang_AK_IOI_FOR_1520752260_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_Clovers_AK_IOI_FOR_1481425600_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_zjjws_AK_IOI_FOR_107881622_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_TrainDriver_AK_IOI_FOR_1382158589_TIMES_
_qy_AK_IOI_FOR_455217855_TIMES_
_hahazhou_AK_IOI_FOR_519645369_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_SmilingKnight_AK_IOI_FOR_444059537_TIMES_
_zhoukangyang_AK_IOI_FOR_1046994768_TIMES_
_qy_AK_IOI_FOR_390271333_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1931795874_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_REM_001_AK_IOI_FOR_989490635_TIMES_
_REM_001_AK_IOI_FOR_1990135450_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_REM_001_AK_IOI_FOR_1753796212_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_REM_001_AK_IOI_FOR_1569043394_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_Clovers_AK_IOI_FOR_431155640_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_SmilingKnight_AK_IOI_FOR_444059537_TIMES_
_zhoukangyang_AK_IOI_FOR_1046994768_TIMES_
_qy_AK_IOI_FOR_1015014744_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_517_AK_IOI_FOR_1439785439_TIMES_
_DPair_AK_IOI_FOR_2000033307_TIMES_
_DragonInBed_AK_IOI_FOR_1115364227_TIMES_
_XXY_AK_IOI_FOR_478227449_TIMES_
_Flying2018_AK_IOI_FOR_862725109_TIMES_
_devinWang_AK_IOI_FOR_1520752260_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_MYY_AK_IOI_FOR_1571120419_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_qy_AK_IOI_FOR_390271333_TIMES_
_hahazhou_AK_IOI_FOR_550466775_TIMES_
_qy_AK_IOI_FOR_1015014744_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_SmilingKnight_AK_IOI_FOR_444059537_TIMES_
_qy_AK_IOI_FOR_390271333_TIMES_
_fAKe_AK_IOI_FOR_122262044_TIMES_
_qy_AK_IOI_FOR_1015014744_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_REM_001_AK_IOI_FOR_1990135450_TIMES_
_rayleigh_AK_IOI_FOR_1424014129_TIMES_
_WH_AK_IOI_FOR_938240885_TIMES_
_SevenDawns_AK_IOI_FOR_130882885_TIMES_
_REM_001_AK_IOI_FOR_989490635_TIMES_
_DPair_AK_IOI_FOR_1355072424_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_qy_AK_IOI_FOR_1015014744_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_517_AK_IOI_FOR_1439785439_TIMES_
_DPair_AK_IOI_FOR_2000033307_TIMES_
_DragonInBed_AK_IOI_FOR_1115364227_TIMES_
_XXY_AK_IOI_FOR_478227449_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_xyf007_AK_IOI_FOR_1888699476_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_DragonInBed_AK_IOI_FOR_1115364227_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_devinWang_AK_IOI_FOR_1520752260_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_Clovers_AK_IOI_FOR_1481425600_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_fAKe_AK_IOI_FOR_167908422_TIMES_
_zhoukangyang_AK_IOI_FOR_539398985_TIMES_
_SmilingKnight_AK_IOI_FOR_444059537_TIMES_
_REM_001_AK_IOI_FOR_1990135450_TIMES_
_rayleigh_AK_IOI_FOR_1424014129_TIMES_
_WH_AK_IOI_FOR_938240885_TIMES_
_SevenDawns_AK_IOI_FOR_130882885_TIMES_
_REM_001_AK_IOI_FOR_989490635_TIMES_
_DPair_AK_IOI_FOR_1355072424_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_qy_AK_IOI_FOR_390271333_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_DPair_AK_IOI_FOR_1708922970_TIMES_
_517_AK_IOI_FOR_1439785439_TIMES_
_DPair_AK_IOI_FOR_2000033307_TIMES_
_DragonInBed_AK_IOI_FOR_1115364227_TIMES_
_XXY_AK_IOI_FOR_478227449_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_devinWang_AK_IOI_FOR_1520752260_TIMES_
_rayleigh_AK_IOI_FOR_1424014129_TIMES_
_qy_AK_IOI_FOR_390271333_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_Point_King_AK_IOI_FOR_87042435_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_fAKe_AK_IOI_FOR_167908422_TIMES_
_fAKe_AK_IOI_FOR_167908422_TIMES_
_MYY_AK_IOI_FOR_1571120419_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_Wallace_AK_IOI_FOR_1020529550_TIMES_
_DragonInBed_AK_IOI_FOR_1402095734_TIMES_
_devinWang_AK_IOI_FOR_1520752260_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_SmilingKnight_AK_IOI_FOR_444059537_TIMES_
_devinWang_AK_IOI_FOR_1520752260_TIMES_
_fAKe_AK_IOI_FOR_1362107475_TIMES_
_Clovers_AK_IOI_FOR_1481425600_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_xyf007_AK_IOI_FOR_1888699476_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_DragonInBed_AK_IOI_FOR_1115364227_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_fAKe_AK_IOI_FOR_167908422_TIMES_
_Point_King_AK_IOI_FOR_2105342204_TIMES_
_TrumpConstructChina_AK_IOI_FOR_1917443856_TIMES_
_TrainDriver_AK_IOI_FOR_1010291609_TIMES_
_qy_AK_IOI_FOR_455217855_TIMES_
_REM_001_AK_IOI_FOR_1990135450_TIMES_
_xYix_AK_IOI_FOR_573398315_TIMES_
_WH_AK_IOI_FOR_604477577_TIMES_
_fAKe_AK_IOI_FOR_167908422_TIMES_
_fAKe_AK_IOI_FOR_167908422_TIMES_
