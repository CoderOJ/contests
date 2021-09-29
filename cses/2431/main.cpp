#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <sstream>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long


  int q = sc.next_int();
  for (int i = 0; i < q; i++)
  {
    int k = sc.next_long() - 1;
    int cur_cnt = 1;
    for (int l = 1; ; l++)
    {
      if (k < cur_cnt * 9 * l)
      {
        int id = k / l;
        int rem = k % l;
        see(id, rem);
        std::stringstream ss;
        ss << cur_cnt + id;
        std::string ans;
        ss >> ans;
        std::cout << ans[rem] << std::endl;
        break;
      }
      k -= cur_cnt * 9 * l;
      cur_cnt *= 10;
    }
  }
  return 0;
}

