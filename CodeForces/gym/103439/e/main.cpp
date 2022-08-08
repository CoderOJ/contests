#include <bits/stdc++.h>
#include <limits>
#include <list>

const int INF = std::numeric_limits<int>::max() / 2;
const int N   = 105;
const int GN  = N * N;

char ms[N][N], mt[N][N];
int  n, m;

int c_id[N][N];

void dfs_set_cid(int ux, int uy, int c)
{
  static const std::pair<int, int> det[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  c_id[ux][uy] = c;
  for (const auto &[dx, dy]: det)
  {
    int vx = ux + dx, vy = uy + dy;
    if (vx >= 0 && vx < n && vy >= 0 && vy < m && ms[vx][vy] == ms[ux][uy]
        && c_id[vx][vy] == -1)
      dfs_set_cid(vx, vy, c);
  }
}

int c_type[GN];
int c_wei[GN];

struct edge_t
{
  int     v, w;
  edge_t *rev;
};

std::list<edge_t> e[N * N];

void add_edge(int u, int v, int w)
{
  e[u].push_back({v, w, nullptr});
  e[v].push_back({u, 0, nullptr});
  e[u].back().rev = &e[v].back();
  e[v].back().rev = &e[u].back();
}

int dep[GN];

bool bfs(int s, int t)
{
  std::fill(dep, dep + GN, INF);
  dep[s] = 0;

  std::queue<int> que;
  que.push(s);

  while (!que.empty())
  {
    int u = que.front();
    que.pop();

    if (u == t)
      break;

    for (auto v: e[u])
      if (v.w > 0 && dep[v.v] == INF)
      {
        dep[v.v] = dep[u] + 1;
        que.push(v.v);
      }
  }

  return dep[t] != INF;
}

std::list<edge_t>::iterator ef[GN];

int dfs(int u, int t, int lim)
{
  if (u == t)
    return lim;
  else
  {
    int rem = lim;

    for (auto &it = ef[u]; it != e[u].end(); it++)
      if (it->w && dep[it->v] == dep[u] + 1)
      {
        int v_lim = std::min(rem, it->w);
        int v_use = dfs(it->v, t, v_lim);

        rem -= v_use;
        it->w -= v_use;
        it->rev->w += v_use;

        if (rem == 0)
          break;
      }

    return lim - rem;
  }
}

int dinic(int s, int t)
{
  int ans = 0;
  while (bfs(s, t))
  {
    for (int u = 0; u < GN; u++)
      ef[u] = e[u].begin();
    ans += dfs(s, t, INF);
  }
  return ans;
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%s", ms[i]);
  for (int i = 0; i < n; i++)
    scanf("%s", mt[i]);

  memset(c_id, -1, sizeof(c_id));
  int cur_cid = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (c_id[i][j] == -1)
        dfs_set_cid(i, j, cur_cid++);

  int cur_ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
    {
      cur_ans += (ms[i][j] == mt[i][j]) ? 1 : 0;
      c_type[c_id[i][j]] = ms[i][j] - '0';
      c_wei[c_id[i][j]] += (ms[i][j] == mt[i][j]) ? -1 : 1;
    }

  int cur_uid = cur_cid;
  int s       = cur_uid++;
  int t       = cur_uid++;

  int sum_wei = 0;
  for (int i = 0; i < cur_cid; i++)
  {
    c_wei[i] = std::max(0, c_wei[i]);
    sum_wei += c_wei[i];

    if (c_type[i] == 0)
      add_edge(s, i, c_wei[i]);
    else
      add_edge(i, t, c_wei[i]);
  }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
    {
      auto add_mutal = [](int u, int v) {
        if (c_type[u] == 1)
          std::swap(u, v);
        add_edge(u, v, INF);
      };

      if (j + 1 < m && c_id[i][j] != c_id[i][j + 1])
        add_mutal(c_id[i][j], c_id[i][j + 1]);
      if (i + 1 < n && c_id[i][j] != c_id[i + 1][j])
        add_mutal(c_id[i][j], c_id[i + 1][j]);
    }

  int ans = sum_wei - dinic(s, t);
  std::cout << n * m - (cur_ans + ans) << std::endl;

  return 0;
}
