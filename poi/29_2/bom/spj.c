#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  assert(argc == 4);
  /* FILE *fin = fopen(argv[1], "r"); */
  FILE *fout = fopen(argv[2], "r");
  FILE *fans = fopen(argv[3], "r");

  char out[100];
  fscanf(fout, "%s", out);
  char ans[100];
  fscanf(fans, "%s", ans);

  assert(strcmp(out, ans) == 0);

  return 0;
}
