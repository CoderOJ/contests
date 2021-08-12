// #include "/home/jack/code/creats/log.hpp"
#include "worldline.h"
#include <vector>
#include <algorithm>
#include <random>
#include <string.h>

void add_edge(int u, int v)
{
  // see(u, v);
  if (u && v)
    addedge(u, v);
}

std::vector<int> query_pid(int n)
{
  next_step();
  std::vector<int> res(n + 1, -1);
  std::vector<std::pair<int,int>> ids;

  std::vector<int> qid(n);
  for (int i = 1; i <= n; i++)
    qid[i - 1] = i;
  std::shuffle(qid.begin(), qid.end(), std::mt19937(18040701));

  int id_cnt = 0;
  for (const int u: qid)
  {
    for (const auto& [v,id] : ids)
      if (query(v, u))
      {
        res[u] = id;
        break;
      }
    if (res[u] == -1)
    {
      res[u] = id_cnt++;
      ids.emplace_back(u, res[u]);
    }
  }

  // see(res);
  return res;
}

int query_permutation(int n,int ans[])
{
  if (n == 2)
    return 0;

  constexpr int SN = 142;
  int id2u[SN][SN];
  int cnt1[SN], cnt2[SN];
  memset(cnt1, 0, sizeof(cnt1));
  memset(cnt2, 0, sizeof(cnt2));

  int uid = 1, sn, ln;
  for (int i = 0; ; i++)
    for (int j = 0; j <= i; j++)
    {
      // see(i, j, uid);
      id2u[i][j] = uid;
      if (uid == n)
      {
        sn = i + 1, ln = j + 1;
        goto L_AWSDFWE;
      }
      uid++;
    }
L_AWSDFWE:
  
  if (ln < sn)
  {
    int off = sn - ln;
    for (int i = sn - 1; i >= off; i--)
      id2u[sn - 1][i] = id2u[sn - 1][i - off];
    for (int i = 0; i < off; i++)
      id2u[sn - 1][i] = 0;
  }
  for (int i = 0; i < sn - 1; i++)
    for (int j = 0; j <= i; j++)
      if (id2u[i][j])
        cnt1[i]++, cnt2[j]++;
  // see(sn, ln);

  new_round();
  for (int i = 0; i < sn; i++)
    for (int j = 0; j < i; j++)
      add_edge(id2u[i][j], id2u[i][j + 1]);
  auto pid1 = query_pid(n);
  int size1[SN];
  memset(size1, 0, sizeof(size1));
  for (int i = 1; i <= n; i++)
    size1[pid1[i]]++;

  new_round();
  for (int i = 0; i < sn - 1; i++)
    for (int j = 0; j <= i; j++)
      add_edge(id2u[i][j], id2u[i + 1][j]);
  auto pid2 = query_pid(n);
  int size2[SN];
  memset(size2, 0, sizeof(size2));
  for (int i = 1; i <= n; i++)
    size2[pid2[i]]++;

  int uu = -1;
  for (int i = 1; i <= n; i++)
  {
    if (size2[pid2[i]] == 1 && size1[pid1[i]] == ln)
    {
      uu = i;
      break;
    }
  }
  // see(uu);

  int size2u[SN][SN];
  for (int i = 1; i <= n; i++)
    if (pid1[i] == pid1[uu])
    {
      ans[id2u[sn - 1][sn - size2[pid2[i]]]] = i;
      size2[pid2[i]]--;
    }
  for (int i = 1; i <= n; i++)
    if (pid1[i] != pid1[uu])
      size2u[size1[pid1[i]]][size2[pid2[i]]] = i;

  for (int i = 0; i + 1 < sn; i++)
    for (int j = 0; j <= i; j++)
    {
      // see(id2u[i][j], i, j, cnt1[i], cnt2[j], size2u[cnt1[i]][cnt2[j]]);
      ans[id2u[i][j]] = size2u[cnt1[i]][cnt2[j]];
    }

  return 1;
}
