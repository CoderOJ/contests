#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <functional>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  __gnu_pbds::tree<std::pair<int,int>, __gnu_pbds::null_type, std::less<std::pair<int,int>>,
                   __gnu_pbds::rb_tree_tag,
                   __gnu_pbds::tree_order_statistics_node_update>
      t;

  int n = sc.next_int();
  int q = sc.next_int();
  std::vector<int> e(n);
  for (int i = 0; i < n; i++)
    t.insert({e[i] = sc.next_int(), i});

  for (int i = 0; i < q; i++)
  {
    char op = sc.next_char();
    if (op == '?')
    {
      int l = sc.next_int();
      int r = sc.next_int();
      std::cout << t.order_of_key({r + 1, 0}) - t.order_of_key({l, 0}) << std::endl;
    }
    else
    {
      int i = sc.next_int() - 1;
      int b = sc.next_int();
      int a = std::exchange(e[i], b);
      auto a_it = t.lower_bound({a, 0});
      int a_id = a_it->second;
      t.erase(a_it);
      t.insert({b, a_id});
    }
    see(t);
  }

  return 0;
}
