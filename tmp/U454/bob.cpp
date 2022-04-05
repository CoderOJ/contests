#include <bits/stdc++.h>

const int B = 666;
const int N = 1000;
const std::pair<int, int> range[] = {{0, B}, {B, B * 2}, {B * 2, N * 2}};
int is_query[N * 2], ans[N * 2];
int n, m;

int read_bit(FILE *f)
{
  char c;
  int r = fscanf(f, " %c", &c);
  assert(r == 1);
  return c - '0';
}

int main(int, char **argv)
{
  FILE *fin = fopen("bob.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  for (int i = 0; i < n; i++)
  {
    int x;
    fscanf(fin, "%d", &x);
    x--;
    is_query[x] = 1;
  }
  fclose(fin);

  int block_query_cnt[3];
  for (int i = 0; i < 3; i++)
    block_query_cnt[i] = std::accumulate(is_query + range[i].first, is_query + range[i].second, 0);
  // for (int i = 0; i < 3; i++)
  //   fprintf(stderr, "%s: block_query_cnt[%d] = %d\n", argv[0], i, block_query_cnt[i]);
  std::vector<int> block_id{0, 1, 2};
  std::sort(block_id.begin(), block_id.end(), [&](int x, int y) {
    return block_query_cnt[x] < block_query_cnt[y];
  });

  int control_bits[3] = {0, 0, 0};
  control_bits[block_id[0]] = 1;
  control_bits[block_id[1]] = 1;
  control_bits[block_id[2]] = 0;
  // for (int i = 0; i < 3; i++)
  //   fprintf(stderr, "%s: control_bits[%d] = %d\n", argv[0], i, control_bits[i]);
  for (int i = 0; i < 3; i++)
    putchar_unlocked('0' + control_bits[i]);
  for (int i = 0; i < 3; i++)
    if (control_bits[i] == 1)
      for (int j = range[i].first; j < range[i].second; j++)
        putchar_unlocked('0' + is_query[j]);
  fflush(stdout);

  for (int i = 0; i < 3; i++)
    if (control_bits[i] == 1)
      for (int j = range[i].first; j < range[i].second; j++)
        if (is_query[j])
          ans[j] = read_bit(stdin);
  for (int i = 0; i < 3; i++)
    if (control_bits[i] == 0)
      for (int j = range[i].first; j < range[i].second; j++)
        ans[j] = read_bit(stdin);

  FILE *fout = fopen("bob.out", "w");
  for (int i = 0; i < N * 2; i++)
    if (is_query[i])
      putc_unlocked('0' + ans[i], fout);
  fclose(fout);

  return 0;
}
