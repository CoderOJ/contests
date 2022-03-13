#include <assert.h>
#include <math.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  assert(argc == 4);
  FILE *fin  = fopen(argv[1], "r");
  FILE *fout = fopen(argv[2], "r");
  FILE *fans = fopen(argv[3], "r");

  int n;
  fscanf(fin, "%d", &n);

  for (int i = 0; i < n; i++)
  {
    double out;
    fscanf(fout, "%lf", &out);
    double ans;
    fscanf(fans, "%lf", &ans);
    assert(fabs(out - ans) / ans <= 0.001);
  }

  return 0;
}
