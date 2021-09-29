#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cstring>
#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100005;
std::pair<int,int> inter[N];
bool vis[N];
int n;



int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    inter[i].first = sc.next_int();
    inter[i].second = sc.next_int();
  }

  std::vector<int> sl(n), sr(n);
  for (int i = 0; i < n; i++)
    sl[i] = sr[i] = i;

  std::sort(sl.begin(), sl.end(), [](int a, int b) { return inter[a].first > inter[b].first; });
  std::sort(sr.begin(), sr.end(), [](int a, int b) { return inter[a].second < inter[b].second; });

  long long ans0 = 0;
  {
    auto sli = sl.begin(), sri = sr.begin();
    int pos = 0;
    for (int i = 0; i < n; i++)
    {
      auto& si = i % 2 ? sli : sri;
      while (vis[*si]) si++;
      if (pos < inter[*si].first || pos > inter[*si].second)
      {
        int cur = i % 2 ? inter[*si].first : inter[*si].second;
        ans0 += std::abs(cur - std::exchange(pos, cur));
      }
      vis[*si] = true;
      si++;

      see(i, pos, ans0);
    }
    ans0 += std::abs(pos);
  }
  memset(vis, 0, sizeof(vis));
  long long ans1 = 0;
  {
    auto sli = sl.begin(), sri = sr.begin();
    int pos = 0;
    for (int i = 0; i < n; i++)
    {
      auto& si = i % 2 ? sri : sli;
      while (vis[*si]) si++;
      if (pos < inter[*si].first || pos > inter[*si].second)
      {
        int cur = i % 2 ? inter[*si].second : inter[*si].first;
        ans1 += std::abs(cur - std::exchange(pos, cur));
      }
      vis[*si] = true;
      si++;

      see(i, pos, ans1);
    }
    ans1 += std::abs(pos);
  }

  std::cout << std::max(ans0, ans1) << std::endl;

  return 0;
}

