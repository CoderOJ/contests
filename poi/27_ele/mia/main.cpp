#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstdint>
#include <memory>
#include <streambuf>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int B = 63;

struct trie_t
{
  struct node_t
  {
    std::unique_ptr<node_t> s[2];

    int id;
  };

  std::unique_ptr<node_t> root = std::make_unique<node_t>();

  void insert(uint64_t s, int id)
  {
    node_t *cur = root.get();
    for (int i = B - 1; i >= 0; i--)
    {
      uint64_t x = (s >> i) & 1;
      if (!cur->s[x])
        cur->s[x] = std::make_unique<node_t>();
      cur = cur->s[x].get();
    }
    cur->id = id;
  }

  int query_xor_max(uint64_t s)
  {
    node_t *cur = root.get();
    for (int i = B - 1; i >= 0; i--)
    {
      uint64_t x = (s >> i) & 1;
      if (cur->s[!x])
        cur = cur->s[!x].get();
      else
        cur = cur->s[x].get();
    }
    return cur->id;
  }
};

trie_t ta, tb;

CONSTRAINT(N, 100'005, 105)

std::vector<int> e[N];

int  match[N];
bool vis[N];

bool hungary(int u)
{
  for (int v : e[u])
    if (!vis[v])
    {
      vis[v] = true;
      if (match[v] == -1 || hungary(match[v]))
      {
        match[u] = v;
        match[v] = u;
        return true;
      }
    }
  return false;
}

int main()
{
  cm::impl::cm_logger.assert_exit();

  int n = sc.next_int();

  std::vector<uint64_t> a(n), b(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_long();
  for (int i = 0; i < n; i++)
    b[i] = sc.next_long();

  for (int i = 0; i < n; i++)
    ta.insert(a[i], i);
  for (int i = 0; i < n; i++)
    tb.insert(b[i], n + i);

  for (int i = 0; i < n; i++)
  {
    int u = i;
    int v = tb.query_xor_max(a[i]);
    e[u].push_back(v);
    e[v].push_back(u);
  }
  for (int i = 0; i < n; i++)
  {
    int u = n + i;
    int v = ta.query_xor_max(b[i]);
    e[u].push_back(v);
    e[v].push_back(u);
  }

  std::fill(match, match + n + n, -1);
  for (int i = 0; i < n; i++)
  {
    std::fill(vis, vis + n + n, false);
    vis[i] = true;
    if (!hungary(i))
    {
      puts("NIE");
      return 0;
    }
  }

  puts("TAK");
  for (int i = 0; i < n; i++)
    printf("%d ", match[i] - n + 1);
  puts("");

  return 0;
}
