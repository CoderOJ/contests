#include <bits/stdc++.h>

int init_io = []{
#ifndef CM_DEBUG
  freopen("sort.in", "r", stdin);
  freopen("sort.out", "w", stdout);
#endif
  return 0;
}();




const int N = 200005;

struct item_t
{
  int a[4];
};

item_t a[N];
int n, m;

void m2()
{
  int64_t ans = 0;
  for (int i = 0; i < n; i++)
    ans += (int64_t)(a[i].a[0] + a[i].a[1]) * (n + n);
  printf("%" SCNi64 "\n", ans);
}

template <int M>
int64_t brute_force(item_t *al, item_t *ar, item_t *bl, item_t *br)
{
  int64_t ans = 0;
  for (item_t *i = al; i < ar; i++)
    for (item_t *j = bl; j < br; j++)
    {
      int cur = i->a[0] + j->a[0];
      for (int k = 1; k < M; k++)
        cur = std::max(cur, i->a[k] + j->a[k]);
      ans += cur;
    }
  return ans;
}

struct pii_t
{
  int64_t cnt, sum;
  pii_t operator+ (pii_t rhs) const
  {
    return {cnt + rhs.cnt, sum + rhs.sum};
  }
};

struct bit_t
{
  pii_t a[N + N];
  
  void add(int p, pii_t v)
  {
    p += N;
    for (; p < N + N; p += p & -p)
      a[p] = a[p] + v;
  }

  pii_t sum(int p)
  {
    p += N;
    pii_t res{0, 0};
    for (; p > 0; p -= p & -p)
      res = res + a[p];
    return res;
  }
};

struct prio_t
{
  int key[3];
  int val;
};

prio_t p[N * 2];

int64_t p2(prio_t *al, prio_t *ar, prio_t *bl, prio_t *br)
{
  auto cmp_t = [](prio_t x, prio_t y) {
    return x.key[1] < y.key[1];
  };
  std::sort(al, ar, cmp_t);
  std::sort(bl, br, cmp_t);
  
  static bit_t bit;

  int64_t ans = 0;
  prio_t *ai = al;
  for (prio_t *bi = bl; bi < br; bi++)
  {
    for (; ai != ar && ai->key[1] <= bi->key[1]; ai++)
      bit.add(ai->key[0], {1, ai->val});
    pii_t r = bit.sum(bi->key[0]);
    ans += r.cnt * bi->val + r.sum;
  }
  for (prio_t *i = al; i < ai; i++)
    bit.add(i->key[0], {-1, -i->val});

  return ans;
}


int64_t s3(item_t *al, item_t *ar)
{
  prio_t *pl = p, *pm = p + (ar - al), *pr = pm + (ar - al);
  int64_t ans = 0;
  {
    for (int i = 0; i < pr - pl; i++)
    {
      pl[i].key[0] = al[i].a[1] - al[i].a[0];
      pl[i].key[1] = al[i].a[2] - al[i].a[0];
      pl[i].val = al[i].a[0];
    }
    for (int i = 0; i < pr - pl; i++)
    {
      pm[i].key[0] = al[i].a[0] - al[i].a[1];
      pm[i].key[1] = al[i].a[0] - al[i].a[2];
      pm[i].val = al[i].a[0];
    }
    ans += p2(pl, pm, pm, pr);
  }
  {
    for (int i = 0; i < pr - pl; i++)
    {
      pl[i].key[0] = al[i].a[0] - al[i].a[1];
      pl[i].key[1] = al[i].a[2] - al[i].a[1];
      pl[i].val = al[i].a[1];
    }
    for (int i = 0; i < pr - pl; i++)
    {
      pm[i].key[0] = al[i].a[1] - al[i].a[0] - 1;
      pm[i].key[1] = al[i].a[1] - al[i].a[2];
      pm[i].val = al[i].a[1];
    }
    ans += p2(pl, pm, pm, pr);
  }
  {
    for (int i = 0; i < pr - pl; i++)
    {
      pl[i].key[0] = al[i].a[0] - al[i].a[2];
      pl[i].key[1] = al[i].a[1] - al[i].a[2];
      pl[i].val = al[i].a[2];
    }
    for (int i = 0; i < pr - pl; i++)
    {
      pm[i].key[0] = al[i].a[2] - al[i].a[0] - 1;
      pm[i].key[1] = al[i].a[2] - al[i].a[1] - 1;
      pm[i].val = al[i].a[2];
    }
    ans += p2(pl, pm, pm, pr);
  }
  return ans;
}

void m3()
{
  int64_t ans = 0;
  ans += s3(a, a + n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      a[i].a[j] *= -1;
  ans -= s3(a, a + n);
  printf("%" SCNi64 "\n", ans);
}

void m4()
{
  int64_t ans = 0;
  ans += brute_force<4>(a, a + n, a, a + n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      a[i].a[j] *= -1;
  ans -= brute_force<4>(a, a + n, a, a + n);
  printf("%" SCNi64 "\n", ans);
}

int main()
{
  scanf("%d%d", &m, &n);
  for (int j = 0; j < m; j++)
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i].a[j]);
  if (m == 2) m2();
  else if (m == 3) m3();
  else m4();
  return 0;
}
