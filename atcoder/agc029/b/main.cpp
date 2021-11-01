#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <set>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n);
  for (int &x : a)
    x = sc.next_int();

  std::sort(a.begin(), a.end(), std::greater<int>());
  std::multiset<int> st(a.begin(), a.end());
  std::multiset<int>::iterator it;
  int ans = 0;
  for (int x : a)
    if ((it = st.find(x)) != st.end())
    {
      st.erase(it);
      int next = [=] {
        for (int r = 1;; r <<= 1)
          if (r > x)
            return r;
      }() - x;
      if ((it = st.find(next)) != st.end())
      {
        st.erase(it);
        ans++;
      }
    }

  printf("%d\n", ans);

  return 0;
}
