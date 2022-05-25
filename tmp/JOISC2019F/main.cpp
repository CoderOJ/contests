#include "transportations.h"
#include <algorithm>
#include <functional>
#include <limits>
#include <list>
#include <queue>
#include <string>
#include <vector>

template <class T>
struct receiver
{
  using rec_k = std::function<void(T)>;
  std::queue<rec_k, std::list<rec_k>> rec_que;

  void send(T v)
  {
    auto f = std::move(rec_que.front());
    rec_que.pop();
    f(std::move(v));
  }

  template <class K>
  void get(K &&k)
  {
    rec_que.emplace(std::forward<K>(k));
  }
};

receiver<bool> ra, rb;

void ReceiveA(bool b)
{
  ra.send(b);
}
void ReceiveB(bool b)
{
  rb.send(b);
}

struct graph_t
{
  struct edge_t
  {
    int v, w;
  };

  int n, m;

  std::vector<std::basic_string<edge_t>> e;

  std::vector<bool> vis;
  std::vector<int>  dis;
  std::priority_queue<std::pair<int, int>,
                      std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      que;
  int last_dis;

  graph_t(int n, int m) :
      n(n), m(m), e(n), vis(n, false), dis(n, std::numeric_limits<int>::max())
  {
    dis[0] = 0;
    que.emplace(0, 0);
    last_dis = 0;
  }

  graph_t(const graph_t &)
  {
    abort();
  }
  graph_t(graph_t &&) = default;

  void extend(int u, int d)
  {
    vis[u]   = true;
    dis[u]   = d;
    last_dis = d;
    for (const auto &[v, w] : e[u])
      if (d + w < dis[v])
      {
        dis[v] = d + w;
        que.emplace(dis[v], v);
      }
  }

  std::pair<int, int> top()
  {
    while (!que.empty())
    {
      auto u = que.top();
      if (u.first == dis[u.second] && !vis[u.second])
        return u;
      que.pop();
    }
    return {last_dis + 501, -1};
  }

  void add_edge(int u, int v, int w)
  {
    e[u] += {v, w};
    e[v] += {u, w};
  }
};

template <class K>
void receive_bits(receiver<bool> &r, int c, K &&k, int x = 0)
{
  if (c == 0)
    k(x);
  else
  {
    r.get([=, &r, k = std::forward<K>(k)](bool b) mutable {
      receive_bits(r, c - 1, std::forward<K>(k), x * 2 + static_cast<int>(b));
    });
  }
}

template <class F>
void send_bits(F f, int v, int c)
{
  for (int i = c - 1; i >= 0; i--)
  {
    bool b = static_cast<bool>(v & (1 << i));
    f(b);
  }
}

template <int id, class Sender, class Cmp, class K>
void solve(graph_t g, receiver<bool> &r, Sender s, Cmp c, K &&k, int round = 0)
{
  if (round == g.n)
  {
    k(std::move(g.dis));
  }
  else
  {
    // clang-format off
    const auto t = g.top();
    int ud = t.first - g.last_dis, u = t.second;
    send_bits(s, ud, 9);
    receive_bits(r, 9, [=, g = std::move(g), k = std::forward<K>(k), &r](int vd) mutable {
      if (c(ud, vd))
      {
        send_bits(s, u, 11);
        g.extend(u, g.last_dis + ud);
        solve<id>(std::move(g), r, s, c, std::forward<K>(k), round + 1);
      }
      else
      {
        receive_bits(r, 11, [=, g = std::move(g), k = std::forward<K>(k), &r](int v) mutable {
          g.extend(v, g.last_dis + vd);
          solve<id>(std::move(g), r, s, c, std::forward<K>(k), round + 1);
        });
      }
    });
    // clang-format on
  }
}

std::vector<int> answer;
std::vector<int> Answer()
{
  return std::move(answer);
}

void InitA(
    int N, int A, std::vector<int> U, std::vector<int> V, std::vector<int> C)
{
  graph_t g(N, A);
  for (int i = 0; i < A; i++)
    g.add_edge(U[i], V[i], C[i]);

  solve<0>(
      std::move(g),
      ra,
      [](bool b) { SendA(b); },
      std::less_equal<int>(),
      [](std::vector<int> ans) { answer = std::move(ans); });
}

void InitB(
    int N, int B, std::vector<int> S, std::vector<int> T, std::vector<int> D)
{
  graph_t g(N, B);
  for (int i = 0; i < B; i++)
    g.add_edge(S[i], T[i], D[i]);

  solve<1>(
      std::move(g),
      rb,
      [](bool b) { SendB(b); },
      std::less<int>(),
      [](const std::vector<int> &) {});
}
