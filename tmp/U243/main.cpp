#include <bits/stdc++.h>

struct point_t
{
  int x, y;

  static bool less_xy(const point_t &lhs, const point_t &rhs)
  {
    return std::make_pair(lhs.x, lhs.y) < std::make_pair(rhs.x, rhs.y);
  }
};

struct vector_t
{
  int x, y;

  vector_t() = default;
  vector_t(int x, int y) : x(x), y(y) {}
  vector_t(point_t x, point_t y) : x(y.x - x.x), y(y.y - x.y) {}

  int64_t dot(const vector_t &rhs) const
  {
    return 1ll * x * rhs.x + 1ll * y * rhs.y;
  }

  int64_t cross(const vector_t &rhs) const
  {
    return 1ll * x * rhs.y - 1ll * y * rhs.x;
  }

  bool operator<(const vector_t &rhs) const
  {
    return cross(rhs) > 0;
  }
};

const int N = 30005;
const int M = 100005;
const int B = 256;

struct block_t
{
  std::vector<point_t> p;
  std::vector<std::tuple<vector_t, size_t, size_t>> ch;
  std::vector<std::tuple<vector_t, size_t, size_t>>::iterator ch_it;
  std::vector<size_t> ids, rank;
  std::bitset<B> mask[B + 1], full;

  void build()
  {
    ids.resize(p.size());
    for (size_t i = 0; i < p.size(); i++)
      ids[i] = i;
    std::sort(ids.begin(), ids.end(), [&](size_t x, size_t y) {
      return point_t::less_xy(p[x], p[y]);
    });
    rank.resize(p.size());
    for (size_t i = 0; i < p.size(); i++)
      rank[ids[i]] = i;

    ch.clear();
    for (size_t i = 0; i < p.size(); i++)
      for (size_t j = i + 1; j < p.size(); j++)
        ch.emplace_back(vector_t(p[ids[i]], p[ids[j]]), i, j);
    std::sort(ch.begin(), ch.end());
    for (auto &[v, i, j] : ch)
      i =ids[i], j = ids[j];
    ch_it = ch.begin();

    for (size_t i = 0; i < p.size(); i++)
    {
      mask[i + 1] = mask[i];
      mask[i + 1].set(ids[i]);
      full.set(i);
    }
  }

  std::bitset<B> query(const point_t &src, const vector_t &v, bool rev)
  {
    while (ch_it != ch.end())
    {
      const auto &[cv, i, j] = *ch_it;
      if (cv < v)
      {
        assert(rank[i] + 1 == rank[j]);
        assert(mask[rank[j]].test(i) == 1);
        assert(mask[rank[j]].test(j) == 0);

        mask[rank[j]].reset(i);
        mask[rank[j]].set(j);
        std::swap(ids[rank[i]], ids[rank[j]]);
        std::swap(rank[i], rank[j]);
        ch_it++;
      }
      else
      {
        break;
      }
    }
    if (rev == false)
    {
      auto it = std::lower_bound(ids.begin(), ids.end(), v, [&](size_t i, const vector_t &v) {
        return vector_t(src, p[i]).cross(v) >= 0;
      });
      return mask[std::distance(ids.begin(), it)];
    }
    else
    {
      auto it = std::lower_bound(ids.begin(), ids.end(), v, [&](size_t i, const vector_t &v) {
        return vector_t(src, p[i]).cross(v) > 0;
      });
      return mask[std::distance(ids.begin(), it)] ^ full;
    }
  }
};

block_t b[N / B + 2];
int n, m, bs;

struct triangle_t
{
  point_t a, b, c;

  triangle_t() = default;
  triangle_t(const point_t &a, const point_t &b, const point_t &c)
  {
    if (vector_t(a, b).cross(vector_t(a, c)) < 0)
      this->a = a, this->b = b, this->c = c;
    else
      this->a = a, this->b = c, this->c = b;
  }
};

std::bitset<B> cur[M];
int ans[M];

struct query_t
{
  point_t src;
  vector_t v;
  int qid;
  bool rev;

  query_t() = default;
  query_t(const point_t &src, const vector_t &v, int qid)
  {
    this->src = src;
    this->qid = qid;
    if (v.x > 0 || (v.x == 0 && v.y < 0))
    {
      this->v = v;
      this->rev = false;
    }
    else
    {
      this->v = {-v.x, -v.y};
      this->rev = true;
    }
  }
};

int main()
{
  scanf("%d%d", &n, &m);
  bs = (n + B - 1) / B;
  for (int i = 0; i < n; i++)
  {
    int x, y;
    scanf("%d%d", &x, &y);
    b[i / B].p.push_back({x, y});
  }
  for (int i = 0; i < bs; i++)
    b[i].build();

  std::vector<query_t> qs;
  for (int i = 0; i < m; i++)
  {
    int ax, ay, bx, by, cx, cy;
    scanf("%d%d%d%d%d%d", &ax, &ay, &bx, &by, &cx, &cy);
    triangle_t t({ax, ay}, {bx, by}, {cx, cy});
    qs.push_back({t.a, vector_t(t.a, t.b), i});
    qs.push_back({t.b, vector_t(t.b, t.c), i});
    qs.push_back({t.c, vector_t(t.c, t.a), i});
  }
  std::sort(qs.begin(), qs.end(), [](const query_t &x, const query_t &y) {
    return x.v < y.v;
  });

  for (int bi = 0; bi < bs; bi++)
  {
    for (int i = 0; i < m; i++)
      cur[i].set();
    for (const auto &q : qs)
      cur[q.qid] &= b[bi].query(q.src, q.v, q.rev);
    for (int i = 0; i < m; i++)
      ans[i] += cur[i].count();
  }

  for (int i = 0; i < m; i++)
    printf("%d\n", ans[i]);

  return 0;
}
