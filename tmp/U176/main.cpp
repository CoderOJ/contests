#include <bits/stdc++.h>

const int N = 1 << 18;
int a[N], n, m;

int p[N];
int get(int u) { return u == p[u] ? u : p[u] = get(p[u]); }
void join(int u, int v) { p[get(u)] = get(v); }

int id[N], max_val[N], max_id[N];
std::vector<int> bels[N];

void mark_id(int p, int v)
{
  if (id[p] == -1)
  {
    id[p] = v;
    for (int i = 0; i < m; i++)
      if (p & (1 << i))
        mark_id(p ^ (1 << i), v);
  }
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < n; i++) p[i] = i;
  long long ans = 0;
  while (std::any_of(p + 2, p + n, [](int x) { return get(p[1]) != get(x); }))
  {
    std::fill(max_val, max_val + n, 0);
    for (int i = 0; i < n; i++) bels[i].clear();
    for (int i = 0; i < n; i++) bels[get(i)].push_back(i);

    std::fill(id, id + (1 << m), -1);        
    for (int i = 0; i < n; i++) if (p[i] == i)
    {
      for (int j : bels[i])
        for (int k = a[j]; k > max_val[i]; k = (k - 1) & a[j])
          if (id[k] != -1)
            max_val[i] = k, max_id[i] = id[k];
      for (int j : bels[i]) mark_id(a[j], i);
    }
    std::fill(id, id + (1 << m), -1);        
    for (int i = n - 1; i >= 0; i--) if (p[i] == i)
    {
      for (int j : bels[i])
        for (int k = a[j]; k > max_val[i]; k = (k - 1) & a[j])
          if (id[k] != -1)
            max_val[i] = k, max_id[i] = id[k];
      for (int j : bels[i]) mark_id(a[j], i);
    }

    for (int i = 0; i < n; i++) if (p[i] == i)
      if (i != get(max_id[i]))
        ans += max_val[i], join(i, max_id[i]);
  }
  std::cout << ans << std::endl;
  return 0;
}
