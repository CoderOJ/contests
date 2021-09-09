#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"
#include <memory>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1000000007;
using int_t = cm::intm<MOD>;
constexpr int B = 30;
int n, k;

int_t inv2 = int_t(2).inv();
int_t inv6 = int_t(6).inv();
int_t pow_2[B + 5];
AT_INIT({
  pow_2[0] = 1;
  for (int i = 1; i < B + 5; i++)
    pow_2[i] = pow_2[i - 1] * 2;
});

struct trie_node_t
{
  std::unique_ptr<trie_node_t> s[2];
  int_t sum = 0;
  void push_up()
  {
    sum = 0;
    if (s[0] != nullptr) sum += s[0]->sum;
    if (s[1] != nullptr) sum += s[1]->sum;
  }
  bool is_leaf()
  { return s[0] == nullptr && s[1] == nullptr; }
  void push_down()
  {
    cm_assert(sum >= 2);
    cm_assert(is_leaf());
    s[0] = std::make_unique<trie_node_t>();
    s[1] = std::make_unique<trie_node_t>();
    s[0]->sum = s[1]->sum = sum / 2;
  }
};

std::unique_ptr<trie_node_t> trie;

void trie_insert(std::unique_ptr<trie_node_t> &p, 
                 int l, int r, int il, int ir)
{
  if (p == nullptr) p = std::make_unique<trie_node_t>();
  if (il <= l && r <= ir) { p->sum = r - l; return; }
  int mid = (l + r) / 2;
  if (il < mid) trie_insert(p->s[0], l, mid, il, ir);
  if (ir > mid) trie_insert(p->s[1], mid, r, il ,ir);
  p->push_up();
}

int_t ncr(int_t n, int r)
{
  if (r == 2) return n * (n - 1) * inv2;
  else return n * (n - 1) * (n - 2) * inv6;
}

int high_bit, rem_bits[B + 1];

int_t dfs_sub(std::unique_ptr<trie_node_t> &x, 
             std::unique_ptr<trie_node_t> &y,
             int d, int_t cnt)
{
  if (x == nullptr) return 0;
  if (y == nullptr) return x->sum * ncr(cnt, 2);

  if (x->is_leaf() && y->is_leaf())
    return pow_2[d + 1] * ncr(cnt + rem_bits[d + 1] + 1, 2);

  if (x->is_leaf()) x->push_down();
  if (y->is_leaf()) y->push_down();

  if (k & (1 << d))
    return dfs_sub(x->s[0], y->s[1], d - 1, cnt + (y->s[0] ? y->s[0]->sum : 0))
         + dfs_sub(x->s[1], y->s[0], d - 1, cnt + (y->s[1] ? y->s[1]->sum : 0));
  else
    return dfs_sub(x->s[0], y->s[0], d - 1, cnt)
         + dfs_sub(x->s[1], y->s[1], d - 1, cnt);
}

int_t dfs(std::unique_ptr<trie_node_t> &u, int p)
{
  if (u == nullptr) return 0;
  if (u->is_leaf())
  {
    return pow_2[p - high_bit + 1] * ncr(pow_2[high_bit], 3)
         + pow_2[p] * (rem_bits[high_bit] + 1) * (rem_bits[high_bit]); 
  }
  else if (p == high_bit)
  {
    return ncr(u->s[0] ? u->s[0]->sum : 0, 3)
         + ncr(u->s[1] ? u->s[1]->sum : 0, 3)
         + dfs_sub(u->s[0], u->s[1], p - 1, 0)
         + dfs_sub(u->s[1], u->s[0], p - 1, 0);
  }
  else
  {
    return dfs(u->s[0], p - 1) + dfs(u->s[1], p - 1);
  }
}

int main()
{
  n = sc.next_int();
  k = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int l = sc.next_int(), r = sc.next_int() + 1;
    trie_insert(trie, 0, 1 << B, l, r);
  }

  for (int i = 0; i < B; i++)
  {
    if (k & (1 << i))
      high_bit = i;
    rem_bits[i] = ((1 << i) - 1) & k;
  }

  std::cout << dfs(trie, B - 1) << std::endl;
  return 0;
}

