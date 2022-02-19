#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  std::vector<std::pair<int, int>> a;
  for (int i = 0; i < n; i++)
  {
    int x = sc.next_int();
    int y = sc.next_int();
    a.emplace_back(x + y, y);
  }

  std::vector<int> state{0};

  std::sort(a.begin(), a.end());
  see(a);

  for (const auto &[x, y] : a)
  {
    see(state);
    if (state.back() <= x - y)
      state.push_back(state.back() + y);
    for (size_t i = state.size() - 1; i > 0; i--)
      if (state[i - 1] <= x - y)
        check_min(state[i], state[i - 1] + y);
  }

  std::cout << state.size() - 1 << std::endl;

  return 0;
}
