#include <bits/stdc++.h>
using namespace std;

std::mt19937 rd(std::chrono::steady_clock::now().time_since_epoch().count());
int get(int n) { return rd() % n + 1; }

int main() {
  constexpr int P = 1e9;
  constexpr int N = 1e9;
  constexpr int M = 1e9;
  printf("%d %d %d\n", get(P), get(N), get(M));
  return 0;
}
