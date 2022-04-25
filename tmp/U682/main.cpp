#include "/home/jack/cm/lambda"
#include "/home/jack/cm/debug"
#include <bits/stdc++.h>

const int N = 100005;
const int B = 30;

struct basis_t
{
  uint32_t v[B] = {};
  int t[B] = {};

  void insert(uint32_t _v, int _t, auto f)
  {
    for (int i = B - 1; i >= 0 && _v; i--)
      if (_v & (1 << i))
      {
        if (v[i] == 0)
        {
          v[i] = _v;
          t[i] = _t;
        }
        else
        {
          if (f(_t, t[i]))
          {
            std::swap(v[i], _v);
            std::swap(t[i], _t);
          }
        }
        _v ^= v[i];
      }
  }

  uint32_t query(uint32_t _v, auto _pv, auto _f)
  {
    for (int i = B - 1; i >= 0; i--)
      if (_pv(t[i]))
        _v = std::max(_v, _v ^ v[i], _f);
    return _v;
  }
};

uint32_t a[N], ap[N], b[N];
int64_t k;
int n;

struct pre_inter_t
{
  int l, r;
  uint32_t v;
};
std::vector<pre_inter_t> pre_inters[N];

void calc_pre_inters()
{
  using namespace cm::lambda::placeholders;

  basis_t bs;
  pre_inters[0] = std::vector<pre_inter_t>(B + 1, {0, 0, 0});
  for (int i = 0; i < n; i++)
  {
    bs.insert(b[i], i, _0 > _1);

    std::vector<int> brks;
    for (int j = 0; j < B; j++)
    {
      if (bs.v[j])
        brks.push_back(bs.t[j]);
      else
        brks.push_back(-1);
    }
    std::sort(brks.begin(), brks.end(), _0 > _1);
    brks.push_back(-1);

    auto &cur_res = pre_inters[i + 1];
    cur_res.resize(B + 1);
    int l, r = i + 1;
    for (int j = 0; j <= B; j++)
    {
      l = brks[j] + 1;
      uint32_t q = bs.query(ap[i + 1], _0 >= l, _0 < _1);
      cur_res[j] = {l, r, q};
      r = l;
    }
  }
}

struct suf_point_t
{
  int s, d;
  uint32_t v;
};
std::vector<suf_point_t> suf_points[N];

void calc_suf_points()
{
  using namespace cm::lambda::placeholders;

  basis_t bs;
  for (int i = n - 1; i >= 0; i--)
  {
    bs.insert(b[i], i, _0 < _1);

    std::vector<int> brks;
    for (int j = 0; j < B; j++)
      if (bs.v[j])
        brks.push_back(bs.t[j]);
    std::sort(brks.begin(), brks.end());
    brks.insert(brks.begin(), i);
    brks.push_back(n);

    for (size_t j = 0; j + 1 < brks.size(); j++)
    {
      uint32_t q = bs.query(ap[i], _0 < brks[j + 1], _0 > _1);
      suf_points[brks[j]].push_back({(int)j, 1, q});
      suf_points[brks[j + 1]].push_back({(int)j, -1, q});
    }
  }
}

struct node_t
{
  using ptr_t = node_t *;
  ptr_t s[2] = {nullptr, nullptr};
  int cnt = 0;
};

node_t pool[2][N * B * 3];
node_t *pool_ptr;

node_t::ptr_t make_node()
{
  *pool_ptr = node_t();
  return pool_ptr++;
}

struct trie_t
{
  struct opt_t
  {
    enum { modify, query } type;
    node_t::ptr_t p;
    uint32_t v;
    int d;
  };

  std::vector<opt_t> ops;

  void make_modify(uint32_t v, int d)
  {
    ops.push_back({opt_t::modify, nullptr, v, d});
  }
  
  void make_query(uint32_t v, int d)
  {
    ops.push_back({opt_t::query, nullptr, v, d});
  }

  void build()
  {
    node_t::ptr_t root = make_node();
    for (auto &p : ops)
      p.p = root;
  }

  int64_t test_forward(int l)
  {
    int64_t res = 0;
    for (auto &p : ops)
    {
      if (p.type == opt_t::modify)
      {
        int c = (p.v >> l) & 1;
        if (p.p->s[c] == nullptr)
          p.p->s[c] = make_node();
        p.p = p.p->s[c];
        p.p->cnt += p.d;
      }
      else if (p.p != nullptr)
      {
        int c = (p.v >> l) & 1;
        if (p.p->s[0 ^ c])
          res += p.p->s[0 ^ c]->cnt;
      }
    }
    return res;
  }

  void apply_forward(int l, int c)
  {
    for (auto &p : ops)
      if (p.type == opt_t::query && p.p)
      {
        int cc = (p.v >> l) & 1;
        p.p = p.p->s[cc ^ c];
      }
  }
};

trie_t t[B + 1];

void build_tries()
{
  for (int i = 0; i < n; i++)
  {
    for (auto &p : suf_points[i])
      t[p.s].make_modify(p.v, p.d);
    for (int j = 0; j <= B; j++)
      t[j].make_query(pre_inters[i + 1][j].v, 1);
  }

  for (int i = 0; i <= B; i++)
    t[i].build();
}

int main()
{
  scanf("%d%" SCNi64, &n, &k);
  for (int i = 0; i < n; i++)
    scanf("%" SCNu32, &a[i]);
  for (int i = 0; i < n; i++)
  {
    scanf("%" SCNu32, &b[i]);
    b[i] ^= a[i];
  }
  
  ap[0] = 0;
  for (int i = 0; i < n; i++)
    ap[i + 1] = ap[i] ^ a[i];

  pool_ptr = pool[0];

  calc_pre_inters();
  calc_suf_points();
  build_tries();

  uint32_t ans = 0;
  int64_t over = 0;
  for (int i = B - 1; i >= 0; i--)
  {
    pool_ptr = pool[(B - i) % 2];

    int64_t c_over = 0;
    for (int j = 0; j <= B; j++)
      c_over += t[j].test_forward(i);
    if (over + c_over < k)
    {
      over += c_over;
      for (int j = 0; j <= B; j++)
        t[j].apply_forward(i, 1);
      ans |= (1 << i);
    }
    else
    {
      for (int j = 0; j <= B; j++)
        t[j].apply_forward(i, 0);
    }
  }

  std::cout << ans << std::endl;
  
  return 0;
}
