#include <algorithm>

template <class NodeType, size_t K>
struct KDTree
{

  static constexpr double rebuild_thr = 0.65;

  struct Node : public NodeType
  {
    Node  *s[2] = {nullptr, nullptr};
    size_t size = 1, spl_id = 0;
    int    coord[K], coord_l[K], coord_r[K];

    using NodeType::NodeType;
    Node(const NodeType &node) : NodeType(node) {}

    void push_up()
    {
      NodeType::push_up(s[0], s[1]);
      size = 1;
      for (size_t i = 0; i < K; ++i)
        coord_l[i] = coord_r[i] = coord[i];
      if (s[0] != nullptr)
      {
        size += s[0]->size;
        for (size_t i = 0; i < K; ++i)
        {
          coord_l[i] = std::min(coord_l[i], s[0]->coord_l[i]);
          coord_r[i] = std::max(coord_r[i], s[0]->coord_r[i]);
        }
      }
      if (s[1] != nullptr)
      {
        size += s[1]->size;
        for (size_t i = 0; i < K; ++i)
        {
          coord_l[i] = std::min(coord_l[i], s[1]->coord_l[i]);
          coord_r[i] = std::max(coord_r[i], s[1]->coord_r[i]);
        }
      }
    }
    ~Node()
    {
      delete s[0];
      delete s[1];
    }
  };

  Node *root = nullptr;

protected:
  static Node **__impl_rebuild_ptr;

  Node **__impl_rebuild_dfs(Node *u, Node **dest)
  {
    if (u->s[0] != nullptr)
      dest = __impl_rebuild_dfs(u->s[0], dest);
    *dest++ = u;
    if (u->s[1] != nullptr)
      dest = __impl_rebuild_dfs(u->s[1], dest);
    return dest;
  }

  Node *__impl_rebuild(Node **_l, Node **_r, int last_split = 0)
  {
    if (_r <= _l)
      return nullptr;
    size_t size = static_cast<size_t>(_r - _l), mid = size / 2;
    size_t split_id = !last_split;
    std::nth_element(_l, _l + mid, _r, [split_id](Node *a, Node *b) {
      return a->coord[split_id] < b->coord[split_id];
    });
    _l[mid]->spl_id = split_id;
    _l[mid]->s[0]   = __impl_rebuild(_l, _l + mid, split_id);
    _l[mid]->s[1]   = __impl_rebuild(_l + mid + 1, _r, split_id);
    _l[mid]->push_up();
    return _l[mid];
  }

  Node *__impl_rebuild_subtree(Node *u)
  {
    Node **seq   = new Node *[u->size];
    Node **seq_r = __impl_rebuild_dfs(u, seq);
    Node  *res   = __impl_rebuild(seq, seq_r);
    delete[] seq;
    return res;
  }

  bool __impl_balanced(Node *u)
  {
    size_t sz[2] = {u->s[0] ? u->s[0]->size : 0, u->s[1] ? u->s[1]->size : 0};
    return static_cast<double>(std::max(sz[0], sz[1])) <=
           static_cast<double>(u->size) * rebuild_thr;
  }

  void __impl_insert(Node *&u, Node *val)
  {
    if (u == nullptr)
    {
      u = val;
      return;
    }
    __impl_insert(u->s[val->coord[u->spl_id] > u->coord[u->spl_id]], val);
    u->push_up();
    if (!__impl_balanced(u))
      __impl_rebuild_ptr = &u;
  }

  NodeType __impl_query(Node *u, const int coord_l[], const int coord_r[])
  {
    if (u == nullptr)
      return NodeType();
    bool is_fully_included = true;
    bool this_valid        = true;
    for (size_t i = 0; i < K; ++i)
    {
      if (u->coord_r[i] < coord_l[i] || u->coord_l[i] > coord_r[i])
        return NodeType();
      else if (u->coord_l[i] < coord_l[i] || u->coord_r[i] > coord_r[i])
      {
        is_fully_included = false;
        if (u->coord[i] < coord_l[i] || u->coord[i] > coord_r[i])
        {
          this_valid = false;
          break;
        }
      }
    }

    if (is_fully_included)
      return static_cast<NodeType>(*u);
    NodeType ans[2] = {
        __impl_query(u->s[0], coord_l, coord_r),
        __impl_query(u->s[1], coord_l, coord_r),
    };
    NodeType res;
    if (this_valid)
    {
      res = *u;
    }
    res.push_up(ans, ans + 1);
    return res;
  }

public:
  void insert(NodeType val, const int coord[])
  {
    Node *u = new Node(val);
    std::copy(coord, coord + K, u->coord);
    std::copy(coord, coord + K, u->coord_l);
    std::copy(coord, coord + K, u->coord_r);
    __impl_rebuild_ptr = nullptr;
    __impl_insert(root, u);
    if (__impl_rebuild_ptr)
    {
      *__impl_rebuild_ptr = __impl_rebuild_subtree(*__impl_rebuild_ptr);
    }
  }

  NodeType query(const int coord_l[], const int coord_r[])
  {
    return __impl_query(root, coord_l, coord_r);
  }

  ~KDTree()
  {
    delete root;
  }
};

template <class NodeType, size_t K>
typename KDTree<NodeType, K>::Node **KDTree<NodeType, K>::__impl_rebuild_ptr;

#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cassert>
#include <deque>
#include <ext/rope>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 200005;

int a[N], b[N], c[N];
int n;

bool direct_win(int x, int y)
{
  return (a[x] < a[y]) + (b[x] < b[y]) + (c[x] < c[y]) >= 2;
}

__gnu_cxx::rope<int> chain;

void calc_chain()
{
  chain = {0};
  int s = 0;
  int t = 0;
  for (int i = 1; i < n; i++)
  {
    if (direct_win(i, s))
    {
      s = i;
      chain.insert(0, i);
    }
    else if (direct_win(t, i))
    {
      t = i;
      chain.insert(i, i);
    }
    else
    {
      // find first win
      auto fl = 0;
      auto fr = i;
      while (fl != fr)
      {
        auto fm = fl + (fr - fl) / 2;
        if (direct_win(i, chain[fm]))
          fr = fm;
        else
          fl = fm + 1;
      }
      chain.insert(fl, i);
    }
  }
  for (int i = 0; i + 1 < n; i++)
    assert(direct_win(chain[i], chain[i + 1]));
  see(chain);
}

struct node_t
{
  int id  = 0x3f3f3f3f;
  int min = id;

  node_t() = default;
  node_t(int id) : id(id), min(id) {}

  void push_up(node_t *l, node_t *r)
  {
    min = id;
    if (l != nullptr)
      check_min(min, l->min);
    if (r != nullptr)
      check_min(min, r->min);
  }
};

int chain_pos[N];
int chain_l[N];
int low[N];

void calc_chain_l()
{
  KDTree<node_t, 2> kab;
  KDTree<node_t, 2> kac;
  KDTree<node_t, 2> kbc;
  for (int i = 0; i < n; i++)
  {
    int x = a[chain[i]];
    int y = b[chain[i]];
    int z = c[chain[i]];

    int boundnn[] = {0x3f3f3f3f, 0x3f3f3f3f};
    int boundxy[] = {x, y};
    int boundxz[] = {x, z};
    int boundyz[] = {y, z};

    node_t val(i);
    kab.insert(val, boundxy);
    kac.insert(val, boundxz);
    kbc.insert(val, boundyz);

    int lab = kab.query(boundxy, boundnn).min;
    int lac = kac.query(boundxz, boundnn).min;
    int lbc = kbc.query(boundyz, boundnn).min;
    see(i, lab, lac, lbc);
    chain_l[i] = std::min({lab, lac, lbc});
  }

  low[n - 1] = chain_l[n - 1];
  for (int i = n - 2; i >= 0; i--)
    low[i] = std::min(low[i + 1], chain_l[i]);
  for (int i = 0; i < n; i++)
    chain_l[i] = (low[i] == i) ? i : chain_l[i - 1];
}

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    a[i] = sc.next_int();
    b[i] = sc.next_int();
    c[i] = sc.next_int();
  }

  calc_chain();

  for (int i = 0; i < n; i++)
    chain_pos[chain[i]] = i;
  calc_chain_l();

  int q = sc.next_int();
  for (int i = 0; i < q; i++)
  {
    int u  = sc.next_int() - 1;
    int v  = sc.next_int() - 1;
    int ui = chain_pos[u];
    int vi = chain_pos[v];
    if (chain_l[ui] <= vi)
      puts("YES");
    else
      puts("NO");
  }

  return 0;
}
