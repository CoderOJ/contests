#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define N 2001

struct data_t
{
  int key, id;
};

void merge_sort(struct data_t x[], int n)
{
  static struct data_t y[N] = {};
  if (n <= 1)
    return;
  merge_sort(&(x[0]), n / 2);
  merge_sort(&(x[n / 2]), (n + 1) / 2);

  int i, p, q;
  for (i = 0, p = 0, q = n / 2; i < n; i++)
  {
    if (p >= n / 2)
      y[i] = x[q++];
    else if (q >= n)
      y[i] = x[p++];
    else
      y[i] = (x[p].key < x[q].key) ? x[p++] : x[q++];
  }
  for (i = 0; i < n; i++)
    x[i] = y[i];
}

struct dsu_t
{
  int *par, *size, *height;
};

void dsu_init(struct dsu_t *f, int n)
{
  int i;
  for (i = 1; i <= n; i++)
  {
    f->par[i]    = i;
    f->size[i]   = 1;
    f->height[i] = 1;
  }
}

int dsu_root(struct dsu_t *F, int v)
{
  if (F->par[v] == v)
    return v;
  else
  {
    F->par[v] = dsu_root(F, F->par[v]);
    return F->par[v];
  }
}

void dsu_merge(struct dsu_t *F, int u, int v)
{
  u = dsu_root(F, u);
  v = dsu_root(F, v);
  if (u == v)
    return;
  else if (F->height[u] > F->height[v])
  {
    F->par[v] = u;
    F->size[u] += F->size[v];
  }
  else
  {
    F->par[u] = v;
    F->size[v] += F->size[u];
    if (F->height[u] == F->height[v])
      F->height[v]++;
  }
}

int           u[N], v[N], w[N];
int           n, m;
long long     k;
long long     power[N];
struct data_t d[N];

int main()
{
  scanf("%d %d", &n, &m);
  scanf("%lld", &k);
  for (int i = 1; i <= m; i++)
  {
    scanf("%d %d %d", &u[i], &v[i], &w[i]);
    d[i - 1].key = w[i];
    d[i - 1].id  = i;
  }

  merge_sort(d, m);

  power[0] = 1;
  for (int i = 1; i <= m; i++)
    power[i] = power[i - 1] * 2 % MOD;

  int       count[3] = {};
  long long tmp;

  struct dsu_t f;
  f.par    = (int *)malloc(sizeof(int) * (n + 1));
  f.size   = (int *)malloc(sizeof(int) * (n + 1));
  f.height = (int *)malloc(sizeof(int) * (n + 1));

  for (int i = 0; i < m; i++)
  {
    dsu_init(&f, n);
    dsu_merge(&f, u[d[i].id], v[d[i].id]);
    tmp = w[d[i].id];
    for (int j = 0; j < m; j++)
    {
      if (dsu_root(&f, u[d[j].id]) != dsu_root(&f, v[d[j].id]))
      {
        dsu_merge(&f, u[d[j].id], v[d[j].id]);
        tmp += w[d[j].id];
      }
    }
    if (tmp < k)
      count[0]++;
    else if (tmp == k)
      count[1]++;
    else
      count[2]++;
  }

  if (count[1] == 0)
    puts("0");
  else if (count[0] == 0)
    printf("%lld\n", (power[count[1]] - 2) * power[count[2]] % MOD);
  else
    printf("%lld\n", (power[count[1]] - 1) * power[count[2]] * 2 % MOD);

  free(f.par);
  free(f.size);
  free(f.height);

  return 0;
}
