#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#define MOD   998244353
#define N     100005
#define W     3
#define B     18

__attribute__ ((always_inline)) inline
int imind(int x, int y)
{
  return x < y ? x : y;
}

__attribute__ ((always_inline)) inline
int imaxd(int x, int y)
{
  return x > y ? x : y;
}

__attribute__ ((always_inline)) inline
void swapd(int *x, int *y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

__attribute__ ((always_inline)) inline
void swapq(int **x, int **y)
{
  int *t = *x;
  *x = *y;
  *y = t;
}

__attribute__ ((always_inline)) inline
int iaddmd(int a, int b)
{
  int r = a + b;
  return r >= MOD ? r - MOD : r;
}

__attribute__ ((always_inline)) inline
int isubmd(int a, int b)
{
  int r = a - b;
  return r < 0 ? r + MOD : r;
}

__attribute__ ((always_inline)) inline
int imulmd(int a, int b)
{
  return (long long)(a) * b % MOD;
}

int ipowmd(int a, int b)
{
  int r = 1;
  for (; b; b >>= 1)
  {
    if (b & 1)
      r = imulmd(r, a);
    a = imulmd(a, a);
  }
  return r;
}

int iinvd(int x)
{
  return ipowmd(x, MOD - 2);
}

int get_ge_n(int x)
{
  int r = 1, n = 0;
  while (r < x)
    r <<= 1, n++;
  return n;
}

void dft(int *a, int n)
{
  int l = 1 << n;

  static int bit_rev[1 << B], bit_n = -1;
  if (bit_n != n)
  {
    bit_rev[0] = 0;
    for (int i = 1; i < l; i++)
      bit_rev[i] = (bit_rev[i >> 1] >> 1) | ((i & 1) << (n - 1));
    bit_n = n;
  }
  static int w[1 << B], w_n = -1;
  if (w_n < n)
  {
    for (int i = 1; i < l; i <<= 1)
    {
      const int pwi = ipowmd(W, (MOD - 1) / (i * 2));
      int pw = 1;
      for (int j = 0; j < i; j++)
      {
        w[i + j] = pw;
        pw = imulmd(pw, pwi);
      }
    }
    w_n = n;
  }

  for (int i = 0; i < l; i++)
    if (i < bit_rev[i])
      swapd(&a[i], &a[bit_rev[i]]);
  for (int i = 1; i < l; i <<= 1)
    for (int j = 0; j < l; j += i * 2)
      for (int k = 0; k < i; k++)
      {
        const int x = a[j + k], y = a[j + i + k];
        a[j + k] = iaddmd(x, imulmd(y, w[i + k]));
        a[j + i + k] = isubmd(x, imulmd(y, w[i + k]));
      }
}

void seqrd(int *l, int *r)
{
  r--;
  while (l < r)
  {
    swapd(l, r);
    l++, r--;
  }
}

void idft(int *a, int n)
{
  int l = (1 << n);
  seqrd(a + 1, a + l);
  dft(a, n);
  int l_inv = iinvd(l);
  for (int i = 0; i < l; i++)
    a[i] = imulmd(a[i], l_inv);
}

int ipmul(int *a, int al, int *b, int bl)
{
  int n = get_ge_n(al + bl - 1), l = 1 << n;
  memset(a + al, 0, sizeof(int) * (unsigned)(l - al));
  dft(a, n);
  if (a != b)
  {
    memset(b + bl, 0, sizeof(int) * (unsigned)(l - bl));
    dft(b, n);
  }
  for (int i = 0; i < l; i++)
    a[i] = imulmd(a[i], b[i]);
  idft(a, n);
  return al + bl - 1;
}

struct vector_t
{
  int *begin, *end, *m_end;
};

void vector_construct(struct vector_t *p)
{
  p->begin = (int*)malloc(sizeof(int) * 4);
  p->end = p->begin;
  p->m_end = p->begin + 4;
}

void vector_destroy(struct vector_t *p)
{
  free(p->begin);
  p->begin = NULL;
}

void vector_push(struct vector_t *p, int val)
{
  if (p->end == p->m_end)
  {
    ptrdiff_t ori_size = p->end - p->begin;
    size_t new_cap = (size_t)(p->m_end - p->begin) * 2;
    p->begin = (int*)realloc(p->begin, sizeof(int) * new_cap);
    p->end = p->begin + ori_size;
    p->m_end = p->begin + new_cap;
  }
  *p->end++ = val;
}

void vector_swap(struct vector_t *x, struct vector_t *y)
{
  swapq(&x->begin, &y->begin);
  swapq(&x->end, &y->end);
  swapq(&x->m_end, &y->m_end);
}

struct vector_t e[N];
int n;

bool vis[N];
int size[N], tot_size, min_cost, min_id;
void get_size(int u, int f)
{
  size[u] = 1;
  for (int *v = e[u].begin; v < e[u].end; v++)
    if (*v != f && !vis[*v])
    {
      get_size(*v, u);
      size[u] += size[*v];
    }
}

void get_root(int u, int f)
{
  int cur_cost = tot_size - size[u];
  for (int *v = e[u].begin; v < e[u].end; v++)
    if (*v != f && !vis[*v])
    {
      get_root(*v, u);
      cur_cost = imaxd(cur_cost, size[*v]);
    }
  if (cur_cost < min_cost)
  {
    min_cost = cur_cost;
    min_id = u;
  }
}

int ans_cnt[1 << B];
int cur_cnt[1 << B];
int dfs_set_depth(int u, int f, int d)
{
  int max_depth = d;
  cur_cnt[d]++;
  for (int *v = e[u].begin; v < e[u].end; v++)
    if (*v != f && !vis[*v])
      max_depth = imaxd(max_depth, dfs_set_depth(*v, u, d + 1));
  return max_depth;
}

void dac(int u)
{
  get_size(u, 0);
  tot_size = size[u];
  min_cost = __INT32_MAX__;
  get_root(u, 0);
  u = min_id;
  vis[u] = true;

  int l = dfs_set_depth(u, 0, 0) + 1;
  l = ipmul(cur_cnt, l, cur_cnt, l);
  for (int i = 0; i < l; i++)
    ans_cnt[i] += cur_cnt[i];
  memset(cur_cnt, 0, sizeof(int) * (size_t)(l));
  for (int *v = e[u].begin; v < e[u].end; v++)
    if (!vis[*v])
    {
      int l = dfs_set_depth(*v, 0, 1) + 1;
      l = ipmul(cur_cnt, l, cur_cnt, l);
      for (int i = 0; i < l; i++)
        ans_cnt[i] -= cur_cnt[i];
      memset(cur_cnt, 0, sizeof(int) * (size_t)(l));
    }

  for (int *v = e[u].begin; v < e[u].end; v++)
    if (!vis[*v])
      dac(*v);
}

int fac[N], ifac[N];
int rev_a[1 << B], rev_b[1 << B];

int main()
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    vector_construct(&e[i]);
  for (int i = 1; i < n; i ++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    vector_push(&e[u], v);
    vector_push(&e[v], u);
  }
  dac(1);

  fac[0] = fac[1] = 1;
  ifac[0] = ifac[1] = 1;
  for (int i = 2; i < N; i++)
    ifac[i] = imulmd(ifac[MOD % i], MOD - MOD / i);
  for (int i = 2; i < N; i++)
  {
    fac[i] = imulmd(fac[i - 1], i);
    ifac[i] = imulmd(ifac[i - 1], ifac[i]);
  }

  for (int i = 0; i < n; i++)
    rev_a[i] = imulmd(ans_cnt[i], fac[n - 1 - i]);
  for (int i = 0; i < n; i++)
    rev_b[i] = ifac[i];

  ipmul(rev_a, n, rev_b, n);
  for (int i = 0; i < n; i++)
  {
    int i_binom = imulmd(ifac[n - 1], imulmd(fac[i], fac[n - 1 - i]));
    printf("%d ", imulmd(imulmd(rev_a[n - 1 - i], ifac[i]), i_binom));
  }
  puts("");

  for (int i = 1; i <= n; i++)
    vector_destroy(&e[i]);
  return 0;
}
