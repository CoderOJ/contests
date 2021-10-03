#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 250005;
constexpr int B = 61;
int n, m, t;
uint64_t a[N], b[B][N];
int up_id[B][N][2];

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  t = sc.next_int();
  uint64_t xor_sum = 0;
  for (int i = 0; i < n; i++)
  {
    a[i] = sc.next_long();
    xor_sum ^= a[i];
    for (int j = 0; j < B; j++)
      b[j][i] = a[i] & ((1ull << j) - 1);
  }
  for (int i = 0; i < B; i++)
  {
    std::sort(b[i], b[i] + n);
    b[i][n] = 1ull << i;
  }

  for (int i = 0; i + 1 < B; i++)
  {
    int id0 = 0, id1 = 0;
    for (int j = 0; j <= n; j++)
    {
      while (id0 < n && b[i][id0 + 1] < b[i + 1][j]) id0++;
      while (id1 < n && b[i][id1 + 1] < (1ull<<i) + b[i + 1][j]) id1++;
      up_id[i][j][0] = id0;
      up_id[i][j][1] = id1;
    }
  }

  uint64_t last_ans = 0;
  for (int i = 0; i < m; i++)
  {
    uint64_t k = sc.next_long();
    if (t) k ^= (last_ans >> 20);
    last_ans = xor_sum;
    if (n % 2 == 1)
      last_ans ^= k;

    int last_pos = 0;
    for (int j = 0; j < B; j++)
    {
      size_t rev_cnt = n - last_pos;
      if (rev_cnt % 2 == 1)
        last_ans ^= (1ull << j);
      see(i, last_pos);
      last_pos = up_id[j][last_pos][(k >> j) & 1];
    }
    printf("%lu\n", last_ans);
  }

  return 0;
}

