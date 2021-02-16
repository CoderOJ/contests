#include <vector>
#include <string>
#include <cstring>

#include "/home/jack/code/creats/log.h"

class EnergyGameOnGrid {
private:
  static constexpr int N = 2005;
  int n, m, r1,c1, r2,c2;
  enum GridState {
    Empty,
    Wall
  } grid[N][N];
  struct Node { int x, y, t; };
  std::vector<Node> d[N];
  int dis[N][N][4];


  void gen(const std::vector<int>& p) {
    memset(grid, Empty, sizeof(grid));
    long long x = n + 2 * m + 3 * r1 + 4 * c1 + 5 * r2 + 6 * c2;
    for (std::size_t i=0; i<p.size(); i+=5) {
      for (int j=p[i]; j<=p[i+2]; ++j) {
        for (int k=p[i+1]; k<=p[i+3]; ++k) {
          x = (x * 1103515245 + 12345) % 2147483648; 
          grid[j][k] = static_cast<GridState>(x < p[i+4]); } } }
    grid[r1][c1] = grid[r1][c1] = Empty;
    // for (int i=0;i<n;++i) logArray(grid[i], grid[i]+m);
  }

public:
  std::string isReachable(int n, int m, const std::vector<int>& p, 
                          int r1, int c1, int r2, int c2, int E) {

    this->n = n; this->m = m;
    this->r1 = r1; this->c1 = c1; this->r2 = r2; this->c2 = c2;
    gen(p);

    if (r1 == r2 && c1 == c2) { return "Possible"; }     

    auto update_dis = [this](const Node& u, int w) {
      see(u.x, u.y, u.t, w);
      if (dis[u.x][u.y][u.t] < w) {
        dis[u.x][u.y][u.t] = w;
        d[w].push_back(u); } };

    constexpr std::pair<int, int> deta[]{{0,1}, {1,0}, {0,-1}, {-1,0}};

    memset(dis, -1, sizeof(dis));
    for (int i=1;i<=E;++i) d[i].push_back({r1,c1,-1});
    for (int i=E;i>0;--i) {
      for (std::size_t j=0; j<d[i].size(); ++j) {
        const int x=d[i][j].x, y=d[i][j].y, t=d[i][j].t;
        see(i, x, y, t);
        if (x == r2 && y == c2) { return "Possible"; }
        if (t != -1) if (dis[x][y][t] == i) {
          update_dis({x+deta[t].first, y+deta[t].second, t}, i-1); }
        if (grid[x][y] == Empty) {
          { int vy = std::max(y-i, 0);   update_dis({x, vy, 0}, y-vy); }
          { int vx = std::max(x-i, 0);   update_dis({vx, y, 1}, x-vx); }
          { int vy = std::min(y+i, m-1); update_dis({x, vy, 2}, vy-y); }
          { int vx = std::min(x+i, n-1); update_dis({vx, y, 3}, vx-x); } } } }

    return "Impossible"; 
  }
};
