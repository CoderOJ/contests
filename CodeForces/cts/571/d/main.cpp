#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 500500;
int gs[N], fs[N], n, m;
int f[N], g[N], ft[N], gt[N];
char opt[5];

int find(int *f, int x)
{
  while (x ^ f[x])
    x = f[x];
  return x;
}
inline void merge(int *f, int *siz, int *t, int x, int y, int k)
{
  x = find(f, x), y = find(f, y);
  if (siz[x] < siz[y])
    std::swap(x, y);
  siz[x] += siz[y], f[y] = x, t[y] = k;
}

int clear_tag[N];
std::vector<std::pair<int, long long>> add[N];

int main()
{
  n = sc.next_int(), m = sc.next_int();
  for (int i = 1; i <= n; i++)
    fs[f[i] = g[i] = i] = gs[i] = 1, add[i].push_back(std::make_pair(-1, 0));
  for (int i = 1; i <= m; i++)
  {
    sc.next_token(opt);
    int x = sc.next_int();
    switch (opt[0])
    {
    case 'U': {
      int y = sc.next_int();
      merge(f, fs, ft, x, y, i);
      break;
    }
    case 'M': {
      int y = sc.next_int();
      merge(g, gs, gt, x, y, i);
      break;
    }
    case 'A': {
      int k = find(f, x);
      add[k].push_back(std::make_pair(i, fs[k] + add[k].back().second));
      break;
    }
    case 'Z': {
      int k = find(g, x);
      clear_tag[k] = i;
      break;
    }
    case 'Q': {
      int fx = x, tag = clear_tag[x];
      while (g[fx] != fx)
      {
        if (clear_tag[g[fx]] > gt[fx])
          tag = std::max(tag, clear_tag[g[fx]]);
        fx = g[fx];
      }
      fx = x;
      int l = static_cast<int>(
          lower_bound(add[x].begin(), add[x].end(), std::make_pair(tag, 0ll)) -
          add[x].begin());
      long long ans = add[x].back().second - add[x][l - 1].second;
      while (f[fx] != fx)
      {
        int tf = f[fx];
        l = static_cast<int>(
            lower_bound(add[tf].begin(), add[tf].end(),
                        std::make_pair(std::max(tag, ft[fx]), 0ll)) -
            add[tf].begin());
        ans += add[tf].back().second - add[tf][l - 1].second;
        fx = f[fx];
      }
      printf("%lld\n", ans);
    }
    }
  }
  return 0;
}
