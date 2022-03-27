#include <bits/stdc++.h>

int init_io = []{
#ifndef CM_DEBUG
  freopen("stack.in", "r", stdin);
  freopen("stack.out", "w", stdout);
#endif
  return 0;
}();

const int N = 500005;

int a[N], b[N], n, q;
struct query_t { int l, r, ans, id; } qs[N];

int main()
{
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < n; i++) scanf("%d", &b[i]);
  for (int i = 0; i < q; i++) { int l, r; scanf("%d%d", &l, &r); l--; qs[i] = {l, r, 0, i}; }
  std::sort(qs, qs + q, [](query_t a, query_t b) { return a.l > b.l; });

  query_t *qs_it = qs;
  std::vector<int> que;
  for (int i = n - 1; i >= 0; i--)
  {
    while (!que.empty())
    {
      int j = que.back();
      // check if j can pop i
      if (a[i] != a[j] && b[j] < b[i])
        que.pop_back();
      else
        break;
    }
    que.push_back(i);
    while (qs_it != qs + q && qs_it->l == i)
    {
      qs_it->ans = static_cast<int>(std::lower_bound(que.rbegin(), que.rend(), qs_it->r) - que.rbegin());
      qs_it++;
    }
  }

  std::sort(qs, qs + q, [](query_t a, query_t b) { return a.id < b.id; });
  for (int i = 0; i < q; i++)
    printf("%d\n", qs[i].ans);

  return 0;
}
