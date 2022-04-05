#include <bits/stdc++.h>

const int B = 666;
const int N = 1000;
const std::pair<int, int> range[] = {{0, B}, {B, B * 2}, {B * 2, N * 2}};
int b[N * 2];
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
  FILE *fin = fopen("alice.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  for (int i = 0; i < n * 2; i++)
    b[i] = read_bit(fin);
  fclose(fin);

  int control_bits[3];
  for (int i = 0; i < 3; i++)
    control_bits[i] = read_bit(stdin);
  // for (int i = 0; i < 3; i++)
  //   fprintf(stderr, "%s: control_bits[%d] = %d\n", argv[0], i, control_bits[i]);

  for (int i = 0; i < 3; i++)
    if (control_bits[i] == 1)
      for (int j = range[i].first; j < range[i].second; j++)
      {
        int cur_query = read_bit(stdin);
        if (cur_query == 1)
          putchar_unlocked('0' + b[j]);
      }
  for (int i = 0; i < 3; i++)
    if (control_bits[i] == 0)
      for (int j = range[i].first; j < range[i].second; j++)
        putchar_unlocked('0' + b[j]);
  fflush(stdout);

  return 0;
}
