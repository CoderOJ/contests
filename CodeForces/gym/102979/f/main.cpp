#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct edge_t
{
  int      v;
  uint32_t w;
  int      id;
};

constexpr int N = 100005;

std::vector<edge_t> e[N];

int n, m, q;

uint32_t dep[N];
bool     vis[N];

std::vector<uint32_t> extra_e;

void dfs_init(int u, int fa_id)
{
  vis[u] = true;
  for (const auto &[v, w, id] : e[u])
    if (id != fa_id)
    {
      if (!vis[v])
      {
        dep[v] = dep[u] ^ w;
        dfs_init(v, id);
      }
      else
      {
        extra_e.push_back(w ^ dep[u] ^ dep[v]);
      }
    }
}

uint32_t basis[32];

void basis_insert(uint32_t x)
{
  for (int i = 30; i >= 0; i--)
    if (x & (1u << i))
    {
      if (basis[i] == 0)
      {
        basis[i] = x;
        break;
      }
      else
      {
        x ^= basis[i];
      }
    }
}

void basis_build()
{
  for (int i = 0; i < 30; i++)
    if (basis[i])
      for (int j = i + 1; j < 30; j++)
        if (basis[j] & (1u << i))
          basis[j] ^= basis[i];
}

uint32_t pre_dep[N];

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  q = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int      u = sc.next_int();
    int      v = sc.next_int();
    uint32_t w = sc.next_int();
    e[u].push_back({v, w, i});
    e[v].push_back({u, w, i});
  }

  dfs_init(1, -1);
  for (uint32_t w : extra_e)
    basis_insert(w);
  basis_build();

  for (int i = 1; i <= n; i++)
    pre_dep[i] = pre_dep[i - 1] ^ dep[i];

  for (int i = 0; i < q; i++)
  {
    int  l   = sc.next_int();
    int  r   = sc.next_int();
    bool odd = ((r - l) % 4 == 1) || ((r - l) % 4 == 2);

    uint32_t c = 0;
    if ((r - l) % 2 == 1)
      c = pre_dep[r] ^ pre_dep[l - 1];
    else
      c = 0;
    uint32_t ans = c;
    for (int i = 0; i < 30; i++)
    {
      bool c_cur = (c >> i) & 1;
      if (odd ^ c_cur)
        ans ^= basis[i];
    }

    std::cout << ans << std::endl;
  }

  return 0;
}
