#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <functional>
#include <set>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 200005;
int n, p[N], v[N];
int belong[N];

struct node_info_t
{
  int id;
  int cnt_0;
  int cnt_1;

  bool operator< (const node_info_t &rhs) const
  {
    long long la = 1ll * cnt_1 * rhs.cnt_0;
    long long lb = 1ll * rhs.cnt_1 * cnt_0;
    return la == lb ? id < rhs.id : la < lb;
  };

  friend std::ostream& operator<< (std::ostream& out, node_info_t x) 
  {
    out << "(" << x.id << ", " << x.cnt_0 << ", " << x.cnt_1 << ")";
    return out;
  }
};

node_info_t info[N];

int main()
{
  n = sc.next_int();
  for (int i = 1; i <= n; i++)
    belong[i] = i;
  for (int i = 2; i <= n; i++)
    p[i] = sc.next_int();
  for (int i = 1; i <= n; i++)
  {
    v[i] = sc.next_int();
    info[i].id = i;
    info[i].cnt_0 = (v[i] == 0);
    info[i].cnt_1 = (v[i] == 1);
  }

  std::function<int(int)> get_belong = [&](int u)
  {
    return belong[u] == u ? u : belong[u] = get_belong(belong[u]);
  };

  std::set<node_info_t> aval;
  for (int i = 2; i <= n; i++)
    aval.insert(info[i]);

  long long ans = 0;
  for (int i = 1; i < n; i++)
  {
    see(aval);
    auto [u, c0, c1] = *aval.begin(); 
    aval.erase(aval.begin());
    see(u, c0, c1);

    int f = get_belong(p[u]);
    ans += 1ll * info[f].cnt_1 * c0;
    see(u, f, info[f]);
    belong[u] = f;
    if (f > 1) aval.erase(info[f]);
    info[f].cnt_0 += c0;
    info[f].cnt_1 += c1;
    if (f > 1) aval.insert(info[f]);
  }

  std::cout << ans << std::endl;

  return 0;
}

