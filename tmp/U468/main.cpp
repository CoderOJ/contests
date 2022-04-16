#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < n; i++)
#define repa(i, n) for (int i = 1; i <= n; i++)

const int MOD = 998244353;

int zip(bool x, bool y)
{
  return x * 2 + y;
}

struct matrix_t
{
  int a[4][4] = {};

  matrix_t operator* (const matrix_t &rhs) const
  {
    static int64_t v[4][4];
    memset(v, 0, sizeof(v));
    rep(i, 4) rep(k, 4) rep(j, 4)
      v[i][j] += 1ll * a[i][k] * rhs.a[k][j];
    matrix_t res;
    rep(x, 4) rep(y, 4)
      res.a[x][y] = v[x][y] % MOD;
    return res;
  }

  bool operator== (const matrix_t &rhs) const
  {
    return memcmp(a, rhs.a, sizeof(a)) == 0;
  }

  bool operator!= (const matrix_t &rhs) const
  {
    return memcmp(a, rhs.a, sizeof(a)) != 0;
  }
};

struct state_join_min
{
  matrix_t operator()(const matrix_t &op)
  {
    static int64_t v[4][4];
    memset(v, 0, sizeof(v));
    rep(ax, 2) rep(ay, 2)
      rep(bx, 2) rep(by, 2)
        v[zip(ax | bx, ay & by)][zip(ax, ay)] += op.a[zip(bx, by)][0];
    matrix_t res;
    rep(x, 4) rep(y, 4)
      res.a[x][y] = v[x][y] % MOD;
    return res;
  }
};

struct state_join_max
{
  matrix_t operator()(const matrix_t &op)
  {
    static int64_t v[4][4];
    memset(v, 0, sizeof(v));
    rep(ax, 2) rep(ay, 2)
      rep(bx, 2) rep(by, 2)
        v[zip(ax & bx, ay | by)][zip(ax, ay)] += op.a[zip(bx, by)][0];
    matrix_t res;
    rep(x, 4) rep(y, 4)
      res.a[x][y] = v[x][y] % MOD;
    return res;
  }
};

matrix_t I = []{
  matrix_t res;
  rep(i, 4) res.a[i][i] = 1;
  return res;
}();

struct node_t
{
  std::unique_ptr<node_t> ls;
  std::unique_ptr<node_t> rs;
  matrix_t state = I;

  bool is_leaf() const
  {
    return ls == nullptr && rs == nullptr;
  }

  void push_mul(const matrix_t mul)
  {
    state = mul * state;
  }

  void push_down()
  {
    if (state != I)
    {
      ls->push_mul(state);
      rs->push_mul(state);
      state = I;
    }
  }
};

void sgt_insert(std::unique_ptr<node_t> &root, int l, int r, int ml, int mr, const matrix_t &state)
{
  if (root == nullptr)
    root = std::make_unique<node_t>();
  if (ml <= l && r <= mr)
  {
    root->state = state;
  }
  else
  {
    int m = l + (r - l) / 2;
    if (ml < m)
      sgt_insert(root->ls, l, m, ml, mr, state);
    if (mr > m)
      sgt_insert(root->rs, m, r, ml, mr, state);
  }
}

template <class join>
std::unique_ptr<node_t> sgt_join(std::unique_ptr<node_t> &&u, std::unique_ptr<node_t> &&v)
{
  if (u->is_leaf())
  {
    v->push_mul(join()(u->state));
    return std::move(v);
  }
  else if (v->is_leaf())
  {
    u->push_mul(join()(v->state));
    return std::move(u);
  }
  else
  {
    u->push_down();
    v->push_down();
    std::unique_ptr<node_t> r = std::make_unique<node_t>();
    r->ls = sgt_join<join>(std::move(u->ls), std::move(v->ls));
    r->rs = sgt_join<join>(std::move(u->rs), std::move(v->rs));
    return r;
  }
}

matrix_t sgt_query(const std::unique_ptr<node_t> &u, int l, int r, int p)
{
  if (u->is_leaf())
    return u->state;
  else
  {
    u->push_down();
    int m = l + (r - l) / 2;
    if (p < m) return sgt_query(u->ls, l, m, p);
    else return sgt_query(u->rs, m, r, p);
  }
}

const int N = 200005;

std::vector<int> e[N];
int n, l, r;

int dfs_calc(int u, int f, int d)
{
  if (u != 1 && e[u].size() == 1)
    return u;
  else
  {
    std::vector<int> s;
    for (int v : e[u]) if (v != f)
      s.push_back(dfs_calc(v, u, d + 1));
    if (d % 2 == 1)
      return *std::max_element(s.begin(), s.end());
    else
      return *std::min_element(s.begin(), s.end());
  }
}

std::unique_ptr<node_t> dfs_get_sgt(int u, int f, int d, int key)
{
  if (u != 1 && e[u].size() == 1)
  {
    matrix_t s0;
    s0.a[zip(u < key, u > key)][0] = 2;
    matrix_t s1;
    s1.a[zip(u < key, u > key)][0] = 1;
    s1.a[zip(true, true)][0] = 1;
    int mm = std::abs(key - u) + 1;

    std::unique_ptr<node_t> r;
    sgt_insert(r, 0, n, 0, mm, s0);
    sgt_insert(r, 0, n, mm, n, s1);

    return r;
  }
  else
  {
    std::unique_ptr<node_t> r;
    for (int v : e[u]) if (v != f)
    {
      std::unique_ptr<node_t> vr = dfs_get_sgt(v, u, d + 1, key);
      if (r == nullptr)
        r = std::move(vr);
      else
      {
        std::unique_ptr<node_t> ur;
        std::swap(r, ur);
        if (d % 2 == 1)
          r = sgt_join<state_join_max>(std::move(ur), std::move(vr));
        else
          r = sgt_join<state_join_min>(std::move(ur), std::move(vr));
      }
    }
    return r;
  }
}

int ans[N];

int main()
{
  scanf("%d%d%d", &n, &l, &r);
  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }

  int key = dfs_calc(1, 0, 1);
  auto t = dfs_get_sgt(1, 0, 1, key);

  for (int i = 0; i < n; i++)
  {
    auto r = sgt_query(t, 0, n, i);
    ans[i] = (0ll + r.a[1][0] + r.a[2][0] + r.a[3][0]) % MOD;
  }
  ans[n] = 1;
  for (int u = 2; u <= n; u++)
    if (e[u].size() == 1)
      ans[n] = ans[n] * 2 % MOD;
  ans[n] -= 1;

  for (int i = n; i >= 1; i--)
    ans[i] = (ans[i] - ans[i - 1] + MOD) % MOD;

  for (int i = l; i <= r; i++)
    printf("%d ", ans[i]);
  puts("");

  return 0;
}
