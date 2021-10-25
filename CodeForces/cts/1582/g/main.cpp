#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1000005;

int prime[N];
void init_prime()
{
  for (int i = 2; i < N; i++)
    if (prime[i] == 0)
    {
      for (int j = i; j < N; j += i)
        prime[j] = i;
    }
}

std::vector<int> pos[N];
int a[N], l[N], n;

void insert(int p, int x)
{
  l[p] = p;
  while (x > 1)
  {
    pos[prime[x]].push_back(p);
    see(p, x, prime[x], pos[prime[x]]);
    x /= prime[x];
  }
}

void erase(int p, int x)
{
  l[p] = p;
  while (x > 1)
  {
    if (pos[prime[x]].empty())
      l[p] = 0;
    else
    {
      check_min(l[p], pos[prime[x]].back());
      pos[prime[x]].pop_back();
    }
    see(p, x, prime[x], pos[prime[x]]);
    x /= prime[x];
  }
}

int main()
{
  init_prime();

  n = sc.next_int();
  for (int i = 1; i <= n; i++)
    a[i] = sc.next_int();
  for (int i = 1; i <= n; i++)
  {
    char ty = sc.next_char();
    if (ty == '*') insert(i, a[i]);
    else erase(i, a[i]);
  }

  std::vector<int> st;
  long long ans = 0;
  for (int i = 1; i <= n; i++)
  {
    st.push_back(i);
    while (!st.empty() && st.back() > l[i]) st.pop_back();
    see(i, l[i], st.size());
    ans += st.size();
  }

  std::cout << ans << std::endl;

  return 0;
}

