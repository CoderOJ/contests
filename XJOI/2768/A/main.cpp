#include <bits/stdc++.h>

constexpr double tab[] = 
{
#include "tab.csh"
};
constexpr int tab_block = 450000;

double log_sum_lr(int l, int r) {
  double ans = 0;
  int i = l;
  for (; i+2<=r; i+=3)
    ans += log(1.0 * i * (i + 1) * (i + 2));
  for (; i<=r; i++)
    ans += log(i);
  return ans; }

double log_sum(int n) {
  int rem = n % tab_block;
  if (rem <= tab_block / 2) return tab[n / tab_block] + log_sum_lr((n / tab_block) * tab_block + 1, n);
  else return tab[n / tab_block + 1] - log_sum_lr(n + 1, (n / tab_block + 1) * tab_block); }

std::mt19937 rd(20050610);
double calc() {
  int a, b; std::cin >> a >> b;
  // int a = rd() % 1000000000, b = rd() % 1000000000;
  if (a < b) std::swap(a, b);
  return log_sum(a) - log_sum(a - b) - log_sum(b); }

int main() 
{
  for (int i=0; i<100; ++i) {
    double x = calc(), y = calc();
    if (std::abs(x - y) < 1e-8) { puts("2"); }
    else if (x < y) puts("0");
    else puts("1");
  }
  return 0;
}
