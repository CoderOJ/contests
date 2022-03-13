#include <assert.h>
#include <stdio.h>
#include <string.h>

#define N 1000005

char s[N], t[N];

int main(int argc, char **argv)
{
  assert(argc == 4);
  /* FILE *fin  = fopen(argv[1], "r"); */
  FILE *fout = fopen(argv[2], "r");
  FILE *fans = fopen(argv[3], "r");

  fscanf(fout, "%s", s);
  fscanf(fans, "%s", t);

  assert(strcmp(s, "NIE") == strcmp(t, "NIE"));

  return 0;
}
