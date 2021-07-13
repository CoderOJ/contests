#include <bits/stdc++.h>

constexpr double tab[] = 
{
#include "tab.csh"
};
constexpr int tab_block = 450000;

double log_sum(int n) {
  double ans = tab[n / tab_block];
  int i = (n / tab_block) * tab_block + 1;
  for (; i+3<=n; i+=4)
    ans += std::log(1.0 * i * (i+1) * (i+2) * (i+3));
  for (;i<=n;i++)
    ans += std::log(i);
  return ans; }

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
