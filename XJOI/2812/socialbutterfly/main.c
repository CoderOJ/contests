#include <string.h>
#include <stdio.h>

#define infe 1e9

int min(int a, int b)
{
  return a < b ? a : b;
}

struct node_t
{
  int v, c, nxt;
} __attribute__((aligned(16)));

struct node_t e[6010 * 3 * 2 + 2010 * 2];

int head[6010 + 2010], cur[6010 + 2010], cnt = 1;
int s, t;

void add_edge(int u, int v, int c)
{
  e[++cnt] = ({
    struct node_t r = {v, c, head[u]};
    r;
  });
  head[u] = cnt;
  e[++cnt] = ({
    struct node_t r = {u, 0, head[v]};
    r;
  });
  head[v] = cnt;
}

int que[6010 + 2010], tail, level[6010 + 2010];
int bfs()
{
  memset(level, 0, sizeof level);
  level[que[tail = 1] = s] = 1;
  for (int i = 1; i <= tail; i++)
  {
    int u = que[i];
    for (int j = head[u]; j; j = e[j].nxt)
    {
      if (e[j].c == 0)
      {
        continue;
      }
      int v = e[j].v;
      if (level[v] == 0)
      {
        level[v] = level[u] + 1, que[++tail] = v;
      }
      if (v == t)
      {
        return 1;
      }
    }
  }
  return 0;
}

int dfs(int u, int limit)
{
  if (u == t)
  {
    return limit;
  }
  int ans = 0;
  for (int *j = &cur[u]; *j; *j = e[*j].nxt)
  {
    if (e[*j].c == 0 || level[e[*j].v] != level[u] + 1)
    {
      continue;
    }
    int v = e[*j].v;
    int tmp = dfs(v, min(limit, e[*j].c));
    e[*j].c -= tmp, e[*j ^ 1].c += tmp;
    limit -= tmp, ans += tmp;
    if (limit == 0)
    {
      break;
    }
  }
  return ans;
}

int calc(int limit)
{
  int ans = 0;
  while (bfs())
  {
    memcpy(cur, head, sizeof head);
    int tmp = dfs(s, limit);
    ans += tmp;
    limit -= tmp;
    if (limit == 0)
    {
      break;
    }
  }
  return ans;
}

int n, m, lim;
int id[2010];

int main()
{
  scanf("%d%d%d", &n, &m, &lim);
  s = 0, t = n + m + 1;
  for (int i = 1; i <= n; i++)
  {
    id[i] = cnt + 1;
    add_edge(s, i, lim);
  }
  for (int i = 1; i <= m; i++)
  {
    int u = 0;
    int v = 0;
    scanf("%d%d", &u, &v);
    add_edge(u, i + n, infe);
    add_edge(v, i + n, infe);
    add_edge(i + n, t, 1);
  }
  if (calc(0x3f3f3f3f) < m)
  {
    puts("Yes");
    return 0;
  }
  for (int i = 1; i <= n; i++)
  {
    int tmp = 0;
    int ttt = e[id[i]].c;
    e[id[i]].c = 0;
    s = 0, t = i;
    if ((tmp = calc(e[id[i] ^ 1].c)) < e[id[i] ^ 1].c)
    {
      puts("Yes");
      return 0;
    }
    e[id[i] ^ 1].c -= tmp;
    e[id[i]].c = ttt + tmp;
  }
  puts("No");
}
