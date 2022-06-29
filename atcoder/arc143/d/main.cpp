#include <cstdio>
#include <functional>
#include <iostream>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::tuple<int, int>>> e(n);
  std::vector<int> uu(m), vv(m);
  for (int i = 0; i < m; i++)
    std::cin >> uu[i];
  for (int i = 0; i < m; i++)
    std::cin >> vv[i];

  for (int i = 0; i < m; i++) {
    int u = uu[i] - 1;
    int v = vv[i] - 1;
    e[u].emplace_back(v, i);
    e[v].emplace_back(u, i);
  }

  std::vector<int> rev(m, 0);
  std::vector<int> dep(n, -1);

  std::function<void(int, int)> dfs = [&](int u, int d) {
    dep[u] = d;
    for (const auto &[v, ei] : e[u])
      if (dep[v] == -1) {
        rev[ei] = 1;
        dfs(v, d + 1);
      }
  };

  for (int i = 0; i < n; i++)
    if (dep[i] == -1)
      dfs(i, 0);

  for (int i = 0; i < m; i++)
    putchar_unlocked('0' + (rev[i] ^ (dep[uu[i] - 1] < dep[vv[i] - 1])));
  puts("");
}
