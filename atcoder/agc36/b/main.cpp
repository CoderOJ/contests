#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 200'005;
constexpr int B = 42;

int a[N];
int n;

long long k;

long long next[B][N];
long long last[N];

int main()
{
  n = sc.next_int();
  k = sc.next_long();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  std::fill(last, last + N, n + n);
  for (int i = n - 1; i >= 0; i--)
    last[a[i]] = n + i;
  for (int i = n - 1; i >= 0; i--)
  {
    next[0][i] = last[a[i]] + 1;
    last[a[i]] = i;
  }

  for (int b = 0; b + 1 < B; b++)
    for (int i = 0; i < n; i++)
    {
      long long relay = next[b][i];
      next[b + 1][i]  = next[b][relay % n] + relay / n * n;
    }

  long long cur = 0;
  for (int b = B - 1; b >= 0; b--)
  {
    long long round = cur / n * n;
    while (round + next[b][cur - round] <= n * k)
    {
      cur = round + next[b][cur - round];
      round = cur / n * n;
    }
  }

  see(cur);

  std::vector<int> ans;
  std::set<int>    exists;
  for (long long i = cur; i < n * k; i++)
  {
    const int x = a[i % n];
    if (exists.count(x))
    {
      while (ans.back() != x)
      {
        exists.erase(ans.back());
        ans.pop_back();
      }
      exists.erase(x);
      ans.pop_back();
    }
    else
    {
      exists.insert(x);
      ans.push_back(x);
    }
  }

  std::ostream_iterator<int> out(std::cout, " ");
  std::copy(ans.begin(), ans.end(), out);
  std::cout << std::endl;

  return 0;
}
