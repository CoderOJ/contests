#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"

#include <algorithm>
#include <set>


const int N = 200005;
int n, m, cnt;

struct node_t
{
  int x[3], k, id, w;
  long long lim;
  bool operator<(const node_t &p) const
  {
    return lim == p.lim ? id < p.id : lim < p.lim;
  }
};
node_t cl[N][3];
std::set<node_t> q[N];

long long tag[N], W[N];
void del(const node_t &p)
{
  for (int i = 0; i < p.k; ++i)
    q[p.x[i]].erase(cl[p.id][i]);
}
void add(const node_t &p)
{
  for (int i = 0; i < p.k; ++i)
  {
    cl[p.id][i] = p;
    cl[p.id][i].lim = tag[p.x[i]] + (W[p.id] + p.k - 1) / p.k;
    cl[p.id][i].w = static_cast<int>(tag[p.x[i]]);
    q[p.x[i]].insert(cl[p.id][i]);
  }
}

int last_ans;
int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i)
  {
    int op, x, y, k;
    scanf("%d", &op);
    if (op == 1)
    {
      scanf("%d%d", &y, &k);
      node_t now;
      now.id = ++cnt;
      now.k = k;
      for (int p = 0; p < k; ++p)
        scanf("%d", &now.x[p]), now.x[p] ^= last_ans;
      W[cnt] = y ^ last_ans;
      add(now);
    }
    else
    {
      std::vector<int> vec;
      scanf("%d%d", &x, &y);
      x ^= last_ans, y ^= last_ans;
      tag[x] += y;
      while (!q[x].empty() && q[x].begin()->lim <= tag[x])
      {
        node_t now = *q[x].begin();
        for (int p = 0; p < now.k; ++p)
          W[now.id] -= tag[now.x[p]] - cl[now.id][p].w;
        del(now);
        if (W[now.id] <= 0)
          vec.push_back(now.id);
        else
          add(now);
      }
      if (vec.empty())
        printf("%d\n", last_ans = 0);
      else
      {
        sort(vec.begin(), vec.end());
        printf("%d ", last_ans = static_cast<int>(vec.size()));
        for (size_t i = 0; i < vec.size(); ++i)
        {
          printf("%d", vec[i]);
          putchar(i == vec.size() - 1 ? '\n' : ' ');
        }
      }
    }
  }
}
