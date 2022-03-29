#include <stdio.h>
#include <assert.h>

#define N 500005
int deg[N];

int main(int argc, char **argv)
{
  FILE *fin = fopen(argv[1], "r");
  FILE *fout = fopen(argv[2], "r");
  int t;
  fscanf(fin, "%d", &t);
  for (int i = 0; i < t; i++)
  {
    int n; 
    fscanf(fin, "%d", &n);
    for (int i = 0; i < n - 3; i++)
      fscanf(fin, "%*d%*d");
    for (int i = 1; i <= n; i++)
      deg[i] = 0;
    for (int i = 0; i < n - 1; i++)
    {
      int u, v; fscanf(fout, "%d%d", &u, &v);
      deg[u]++, deg[v]++;
    }
    for (int i = 1; i <= n; i++)
      assert(deg[i] != 2);
  }
}
