#include <bits/stdc++.h>
#include <cassert>
#include <random>
#include <vector>

const int N = 100;

std::vector<int> e[N];
int dis[N][N];
int n;

void dfs(int u, int f, int dis[], int d) {
  dis[u] = d;
  for (int v : e[u])
    if (v != f)
      dfs(v, u, dis, d + 1);
}

int main() {
  static std::mt19937 rd(std::random_device{}());

  int n = 5;
  std::cout << n << std::endl;

  for (int i = 0; i < n - 1; i++) {
    int u = i + 2;
    int v = rd() % (i + 1) + 1;
    e[u].push_back(v);
    e[v].push_back(u);
    std::cerr << u << " " << v << std::endl;
  }

  for (int i = 1; i <= n; i++)
    dfs(i, 0, dis[i], 0);

  while (true) {
    char c;
    std::cin >> c;
    if (c == '?') {
      int u, v;
      std::cin >> u >> v;
      assert(u + v > 3);
      std::cout << dis[u][v] << std::endl;
      std::cerr << "query: " << u << " " << v << " " << dis[u][v] << std::endl;
    } else {
      int d;
      std::cin >> d;
      std::cerr << "answer: " << d << " " << dis[1][2] << std::endl;
      assert(dis[1][2] == d);
      break;
    }
  }

  return 0;
}
