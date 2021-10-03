#pragma GCC optimize(2, 3, "Ofast")

#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 250005;
constexpr int B = 61;
constexpr int C = 22;
int n, m, t;
uint64_t a[N], b[B][N];
uint64_t bb[C + 1][(1 << C) + 5];

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
    b[0][i] = a[i];
  }
  for (int i = 0; i + 1 < B; i++)
  {
    int cnt0 = 0;
    for (int j = 0; j < n; j++)
      if ((a[j] & (1ull << i)) == 0)
        cnt0++; 
    int pos[2] = {0, cnt0};
    for (int j = 0; j < n; j++)
      b[i + 1][pos[(b[i][j] >> i) & 1]++] = b[i][j];
  }
  for (int i = 0; i < B; i++)
    for (int j = 0; j < n; j++)
      b[i][j] &= ((1ull << i) - 1);

  for (int i = 0; i <= C; i++)
  {
    int pos = 0;
    for (uint64_t j = 0; j <= (1ull << i); j++)
    {
      while (pos < n && b[i][pos] < j) pos++;
      bb[i][j] = pos;
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
    for (int j = 0; j < B; j++)
    {
      uint64_t cur_k = k & ((1ull << j) - 1);
      uint64_t rev_l = (1ull << j) - cur_k;
      size_t rev_cnt;
      if (j <= C) rev_cnt = n - bb[j][rev_l];
      else rev_cnt = (b[j] + n) - std::lower_bound(b[j], b[j] + n, rev_l);
      if (rev_cnt % 2 == 1)
        last_ans ^= (1ull << j);
    }
    printf("%lu\n", last_ans);
  }

  return 0;
}

