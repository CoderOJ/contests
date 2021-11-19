#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int k = sc.next_int();
  std::vector<int> moves(k);
  for (int i = 0; i < k; i++)
    moves[i] = sc.next_int();
  std::vector<bool> win(n + 1, false);
  for (int i = 1; i <= n; i++)
  {
    for (const auto x : moves)
      if (x <= i && !win[i - x])
      {
        win[i] = true;
        break;
      }
    putchar_unlocked(win[i] ? 'W' : 'L');
  }
  puts("");

  return 0;
}

