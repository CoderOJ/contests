#include <bits/stdc++.h>
#ifndef UTIL_H_
#define UTIL_H_ 1

#include <vector>
#include <type_traits>

namespace Temps {

template<class T>
inline bool
checkMin(T& a, T b)
{ return (b < a ? a = b, 1 : 0); }

template<class T>
inline bool
checkMax(T& a, T b)
{ return (a < b ? a = b, 1 : 0); }

template <class IntType, typename = typename
          std::enable_if<std::is_integral<IntType>::value>::type>
IntType
gcd(const IntType a, const IntType b) {
  return b == 0 ? a : gcd(b, a % b); }

template <class ForwardIterator, class OutputIterator>
void dissociate(ForwardIterator __begin, ForwardIterator __end, OutputIterator __dest) {
  std::vector <typename std::iterator_traits<ForwardIterator>::value_type> values(__begin, __end); 
  std::sort(values.begin(), values.end()); std::unique(values.begin(), values.end()); 
  while (__begin != __end) {
    *__dest = static_cast<typename std::iterator_traits<OutputIterator>::value_type>(
              std::distance(values.begin(), std::lower_bound(values.begin(), values.end(), *__begin)));
    __dest++; __begin++; } }

}

using Temps::checkMin;
using Temps::checkMax;

#if __has_include(<utility>)
template <class A, class B> inline __attribute__((always_inline)) 
std::pair<A,B> operator+ (const std::pair<A,B> &lhs, const std::pair<A,B> &rhs) {
  return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second); }
template <class A, class B> inline __attribute__((always_inline)) 
std::pair<A,B> operator- (const std::pair<A,B> &lhs, const std::pair<A,B> &rhs) {
  return std::make_pair(lhs.first - rhs.first, lhs.second - rhs.second); }
template <class A, class B> inline __attribute__((always_inline)) 
std::pair<A,B>& operator+= (std::pair<A,B> &lhs, const std::pair<A,B> &rhs) {
  lhs.first += rhs.first; lhs.second += rhs.second; return lhs; }
template <class A, class B> inline __attribute__((always_inline)) 
std::pair<A,B>& operator-= (std::pair<A,B> &lhs, const std::pair<A,B> &rhs) {
  lhs.first -= rhs.first; lhs.second -= rhs.second; return lhs; }
#endif

#endif /* UTIL_H_ */
long long solve(int,int,int,int,std::vector<int>,int);
long long distance(int,int);
constexpr int N = 2005;
std::map<int, long long> dp[N];

std::map<std::pair<int,int>, long long> mem;
long long query(int u, int v) {
  if (u > v) std::swap(u, v);
  if (mem.find(std::make_pair(u,v)) != mem.end())
    return mem[std::make_pair(u,v)];
  return mem[std::make_pair(u,v)] = distance(u, v); }

long long solve(int n, int x, int y, int q, std::vector<int> P, int L) {
  P.insert(P.begin(), x);
  dp[0][y] = 0;
  for (int i=0; i<q; i++) {
    for (const auto [u,x]: dp[i]) {
      checkMax(dp[i+1][u], x + query(P[i], P[i+1]));
      checkMax(dp[i+1][P[i]], x + query(u, P[i+1])); } }
  long long ans = 0;
  for (const auto [u,x]: dp[q]) checkMax(ans, x);
  return ans; }
