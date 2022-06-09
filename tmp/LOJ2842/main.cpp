#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cinttypes>
#include <cstring>

#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 4010, M = 100010;

const int64_t inf = 1e18;

int n, m, q, l;
int nxt[N << 1], to[N << 1], w[N << 1], head[N], cnt = 2;

void add(int u, int v, int w0)
{
  nxt[cnt] = head[u], to[cnt] = v;
  w[cnt]  = w0;
  head[u] = cnt;
  cnt++;
}

struct node_t
{
  int64_t v;
  int     x, y;

  node_t(int64_t v = inf, int x = 0, int y = 0) : v(v), x(x), y(y) {}

  bool operator<(const node_t a) const
  {
    return v < a.v;
  }
};

node_t f[N / 2][N / 2][5];

int64_t dis[N][N];

void check_min(node_t &a, int x, int y)
{
  a = std::min(a, node_t(dis[x][y ^ 1], x, y));
}

struct matrix_t
{
  int64_t a[5][5] = {};
  matrix_t()
  {
    memset(a, 0x3f, sizeof(a));
  }

  const int64_t *operator[](int x) const
  {
    return a[x];
  }
  int64_t *operator[](int x)
  {
    return a[x];
  }

  matrix_t(int x, int y, int z)
  {
    memset(a, 0x3f, sizeof(a));

    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++)
        if (!z || f[x][y][i].y != f[y][z][j].x)
          a[i][j] = f[x][y][i].v;
  }

  int64_t min()
  {
    int64_t ans = inf;

    for (auto &i : a)
      ans = std::min(ans, i[0]);

    return ans;
  }
};

matrix_t operator*(const matrix_t &a, const matrix_t &b)
{
  matrix_t c;

  for (int k = 0; k < 5; k++)
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++)
        c[i][j] = std::min(c[i][j], a[i][k] + b[k][j]);

  return c;
}

bool vis[N];
void dij(int s, int64_t d[])
{
  static int pos[N];

  for (int i = 2; i <= cnt; i++)
    vis[i] = false, d[i] = inf;

  for (int i = 1; i <= n; i++)
    pos[i] = 0;

  d[s] = w[s];
  std::priority_queue<std::pair<int64_t, int>> q;
  q.emplace(-d[s], s);

  while (!q.empty())
  {
    int x = q.top().second;
    q.pop();

    if (vis[x])
      continue;
    vis[x] = true;
    int u  = to[x];
    if (pos[u] == -1)
      continue;

    if (!pos[u])
    {
      pos[u] = x ^ 1;

      for (int i = head[u]; i; i = nxt[i])
        if ((i ^ 1) != x && d[i] > d[x] + w[i])
          d[i] = d[x] + w[i], q.emplace(-d[i], i);
    }
    else
    {
      if (d[pos[u]] > d[x] + w[pos[u]])
        d[pos[u]] = d[x] + w[pos[u]], q.emplace(-d[pos[u]], pos[u]);

      pos[u] = -1;
    }
  }
}

int      a[M];
matrix_t t[M << 2];

void build(int u, int l, int r)
{
  if (l == r)
  {
    t[u] = matrix_t(a[l], a[l + 1], a[l + 2]);
    return;
  }

  int mid = (l + r) / 2;
  build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
  t[u] = t[u << 1] * t[u << 1 | 1];
}

void insert(int u, int l, int r, int p)
{
  if (l == r)
  {
    t[u] = matrix_t(a[l], a[l + 1], a[l + 2]);
    return;
  }

  int mid = (l + r) / 2;

  if (p <= mid)
    insert(u << 1, l, mid, p);
  else
    insert(u << 1 | 1, mid + 1, r, p);

  t[u] = t[u << 1] * t[u << 1 | 1];
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  q = sc.next_int();
  l = sc.next_int();

  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    int w = sc.next_int();
    add(u, v, w);
    add(v, u, w);
  }

  for (int i = 2; i <= cnt; i++)
    dij(i, dis[i]);

  for (int x = 1; x <= n; x++)
    for (int y = 1; y <= n; y++)
      if (x != y)
      {
        for (int i = head[x]; i; i = nxt[i])
          for (int j = head[y]; j; j = nxt[j])
            check_min(f[x][y][0], i, j);

        for (int i = head[x]; i; i = nxt[i])
          for (int j = head[y]; j; j = nxt[j])
          {
            if (i != f[x][y][0].x)
              check_min(f[x][y][1], i, j);

            if (j != f[x][y][0].y)
              check_min(f[x][y][2], i, j);
          }

        for (int i = head[x]; i; i = nxt[i])
          for (int j = head[y]; j; j = nxt[j])
          {
            if (i != f[x][y][0].x && j != f[x][y][1].y)
              check_min(f[x][y][3], i, j);

            if (j != f[x][y][0].y && i != f[x][y][2].x)
              check_min(f[x][y][4], i, j);
          }
      }

  for (int i = 1; i <= l; i++)
    a[i] = sc.next_int();

  build(1, 1, l - 1);

  while (q-- > 0)
  {
    int x = sc.next_int();
    int y = sc.next_int();
    a[x]  = y;

    for (int i = -2; i <= 0; i++)
      if (x + i > 0 && x + i < l)
        insert(1, 1, l - 1, x + i);

    int64_t res = t[1].min();
    printf("%" SCNi64 "\n", res >= inf ? -1 : res);
  }

  return 0;
}
