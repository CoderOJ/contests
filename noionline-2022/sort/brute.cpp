#include "/home/jack/cm/debug"
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
void m3()
{
  int64_t ans = 0;
  ans += brute_force<3>(a, a + n, a, a + n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      a[i].a[j] *= -1;
  ans -= brute_force<3>(a, a + n, a, a + n);
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

void m2()
{
  int64_t ans = 0;
  ans += brute_force<2>(a, a + n, a, a + n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      a[i].a[j] *= -1;
  ans -= brute_force<2>(a, a + n, a, a + n);
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
