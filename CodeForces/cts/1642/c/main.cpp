#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <set>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int k = sc.next_int();

    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();

    std::sort(a.begin(), a.end());

    int ans = 0;

    std::multiset<int> st;
    for (int x : a)
    {
      if (x % k == 0 && st.find(x / k) != st.end())
      {
        st.erase(st.find(x / k));
      }
      else
      {
        st.insert(x);
      }
    }
    
    ans += static_cast<int>(st.size());
    printf("%d\n", ans);
  }
  return 0;
}
