#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 250005;
constexpr int B = 60;
int n, m, t;
uint64_t a[N], b[B][N];

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  t = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_long();

  uint64_t last_ans = 0;
  for (int i = 0; i < m; i++)
  {
    uint64_t k = sc.next_long();
    if (t) k ^= (last_ans >> 20);
    last_ans = 0;
    for (int i = 0; i < n; i++)
      last_ans ^= (a[i] + k);
    printf("%lu\n", last_ans);
  }

  return 0;
}

