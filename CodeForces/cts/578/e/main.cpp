#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cstring>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100005;
int n, idcnt;
char s[N];
std::vector<int> v[N], id[2], ve[2][2];

void adjust()
{
  if (!ve[1][0].empty() || !ve[1][1].empty())
    return;
  if (ve[0][0].empty() || ve[0][1].empty())
    return;
  int a = ve[0][0].back(), b = ve[0][1].back();
  (v[a].back() < v[b].back()) ? (v[a].push_back(v[b].back()), v[b].pop_back())
                              : (v[b].push_back(v[a].back()), v[a].pop_back());
  ve[0][0].pop_back(), ve[0][1].pop_back();
  ve[1][0].push_back(b), ve[1][1].push_back(a);
}

void print(int x)
{
  for (int i = 0; i < static_cast<int>(v[x].size()); ++i)
    printf("%d ", v[x][i]);
}

int main()
{
  n = static_cast<int>(sc.next_token(s + 1) - s - 1);
  for (int i = 1, c, t; i <= n; ++i)
  {
    c = s[i] == 'R';
    if (id[c ^ 1].empty())
      id[c ^ 1].push_back(++idcnt);
    t = id[c ^ 1].back();
    v[t].push_back(i), id[c ^ 1].pop_back(), id[c].push_back(t);
  }
  printf("%d\n", idcnt - 1);
  for (int i = 1; i <= idcnt; ++i)
    ve[v[i].size() & 1][s[v[i].back()] == 'R'].push_back(i);
  adjust();

  int t = (ve[1][0].size() != ve[1][1].size())
              ? ve[1][1].size() > ve[1][0].size()
              : ve[0][0].size() > ve[0][1].size();

  while (!ve[0][t ^ 1].empty())
    print(ve[0][t ^ 1].back()), ve[0][t ^ 1].pop_back();

  while (!ve[1][t].empty())
  {
    print(ve[1][t].back()), ve[1][t].pop_back();
    while (!ve[0][t].empty())
      print(ve[0][t].back()), ve[0][t].pop_back();
    t ^= 1;
  }
  return 0;
}
