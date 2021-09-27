#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util.hpp"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#define int long long
#define int128_t __int128

cm::scanner<cm::optimal_reader> sc(stdin);
constexpr int128_t i1 = 1;
constexpr int N = 1005;
std::pair<int,int> p[N];
int c[N], n;

int128_t cross(std::pair<int,int> a, std::pair<int,int> b)
{ return i1 * a.first * b.second - i1 * a.second * b.first; }
int128_t dot(std::pair<int,int> a, std::pair<int,int> b)
{ return i1 * a.first * b.first + i1 * a.second * b.second; }

struct vec_t
{
  int xid, yid;
  std::pair<int,int> vec;
  std::pair<int,int> mid;
  long long value;


  vec_t(int xid, int yid) : xid(xid), yid(yid), vec(p[yid] - p[xid]), value(c[xid] + c[yid]) 
  {
    if (vec.first < 0) { vec.first = -vec.first; vec.second = -vec.second; }
    if (vec.first == 0 && vec.second > 0) vec.second = -vec.second;
    mid.first = p[xid].first / 2 + p[yid].first / 2;
    mid.second = p[xid].second / 2 + p[yid].second / 2;
  }

  bool operator< (const vec_t &rhs) const 
  {
    auto c = cross(vec, rhs.vec); 
    if (c != 0) return c > 0;
    auto d = dot(vec, rhs.mid - mid);
    if (d != 0) return d > 0;
    return value > rhs.value;
  }

  bool operator== (const vec_t &rhs) const
  {

    auto c = cross(vec, rhs.vec); 
    if (c != 0) return false;
    auto d = dot(vec, rhs.mid - mid);
    return d == 0;
  }
};


signed main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    p[i].first = sc.next_int() * 2;
    p[i].second = sc.next_int() * 2;
    c[i] = sc.next_int();
  }

  std::vector<vec_t> vs;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      vs.emplace_back(i, j);
  std::sort(vs.begin(), vs.end());

  long long ans = 0;

  for (auto itl = vs.begin(); itl < vs.end(); )
  {
    auto itr = itl;
    while (itr < vs.end() && *itl == *itr)
      itr++;

    for (auto i = itl; i < itr; i++)
      if (i->mid != itl->mid)  
      {
        check_max(ans, itl->value + i->value);
        break;
      }

    itl = itr;
  }

  if (ans == 0) { puts("-1"); return 0; }
  std::cout << ans << std::endl;

  return 0;
}

