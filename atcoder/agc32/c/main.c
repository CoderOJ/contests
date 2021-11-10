#include <stdio.h>

typedef struct list_t
{
  struct list_t *next;
  int v, id;
} list;

int main()
{
  int m, N, M, u, w, deg[100001] = {};
  list *adj[100001] = {}, e[400003], *p, *q;
  scanf("%d %d", &N, &M);
  for (m = 1; m <= M; m++)
  {
    scanf("%d %d", &u, &w);
    e[m * 2].v = w;
    e[m * 2 + 1].v = u;
    e[m * 2].id = m * 2;
    e[m * 2 + 1].id = m * 2 + 1;
    e[m * 2].next = adj[u];
    e[m * 2 + 1].next = adj[w];
    adj[u] = &(e[m * 2]);
    adj[w] = &(e[m * 2 + 1]);
    deg[u]++;
    deg[w]++;
  }

  int i, n = N;
  for (i = 1; i <= n; i++)
  {
    if (deg[i] % 2 != 0)
      break;
    else if (deg[i] > 2)
      continue;
    else if (N == 1)
    {
      printf("No\n");
      fflush(stdout);
      return 0;
    }

    for (p = adj[i]; p->id < 0; p = p->next)
      ;
    for (q = p->next; q->id < 0; q = q->next)
      ;
    u = p->v;
    w = q->v;
    e[m * 2].v = w;
    e[m * 2 + 1].v = u;
    e[m * 2].id = m * 2;
    e[m * 2 + 1].id = m * 2 + 1;
    e[m * 2].next = adj[u];
    e[m * 2 + 1].next = adj[w];
    adj[u] = &(e[m * 2]);
    adj[w] = &(e[m * 2 + 1]);
    m++;

    e[(p->id) ^ 1].id *= -1;
    e[(q->id) ^ 1].id *= -1;
    M--;
    N--;
    deg[i] = 0;
  }

  if (i <= n)
    printf("No\n");
  else if (N == 1)
  {
    if (M >= 3)
      printf("Yes\n");
    else
      printf("No\n");
  }
  else if (N == 2)
  {
    for (i = 1; i <= n; i++)
    {
      if (deg[i] == 0)
        continue;
      else if (deg[i] >= 6)
        break;
      for (p = adj[i]; p != NULL; p = p->next)
        if (p->v == i)
          break;
      if (p != NULL)
        break;
    }
    if (i <= n)
      printf("Yes\n");
    else
      printf("No\n");
  }
  else
    printf("Yes\n");

  return 0;
}
