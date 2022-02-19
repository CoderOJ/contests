#include <stdio.h>
#include <string.h>

#define N 100005

char s[N];
int  d[N];

int parent[N];
int sum[N];

int get_parent(int u)
{
  return u == parent[u] ? u : (parent[u] = get_parent(parent[u]));
}

void join(int u, int v)
{
  /* printf("%d %d\n", u, v); */
  parent[get_parent(u)] = get_parent(v);
}

int n, m;

int main()
{
  scanf("%s", s + 1);
  n        = (int)strlen(s + 1) + 2;
  s[0]     = 'a';
  s[n - 1] = 'a';

  for (int i = 1; i < n; i++)
  {
    d[i] = (s[i] - s[i - 1] + 26) % 26;
    /* printf("d[%d] = %d\n", i, d[i]); */
  }

  for (int i = 0; i < n; i++)
    parent[i] = i;

  for (int i = 1, j = n - 1; i < j; i++, j--)
    join(i, j);

  scanf("%d", &m);
  for (int i = 0; i < m; i++)
  {
    int l, r;
    scanf("%d%d", &l, &r);
    join(l, r + 1);
  }

  for (int i = 0; i < n; i++)
    sum[get_parent(i)] += d[i];

  for (int i = 0; i < n; i++)
    if (parent[i] == i)
      if (sum[i] % 26 != 0)
      {
        puts("NO");
        return 0;
      }

  puts("YES");
  return 0;
}
