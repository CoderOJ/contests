#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N 500005
int _ans[N * 2], *ans_top = _ans;
int k[N], a[N][2];
int id[N], rev[N];

int main(int argv, char **argc)
{
  assert(argv >= 3);
  FILE *in = fopen(argc[1], "r");
  FILE *ans = fopen(argc[2], "r");
  int n, m; fscanf(in, "%d%d", &m, &n);
  for (int i=1; i<=m; i++) {
    fscanf(in, "%d", &k[i]); 
    for (int j=0; j<k[i]; j++) fscanf(in, "%d", &a[i][j]); }

  for (int i=0; i<m; i++) fscanf(ans, "%d", &id[i]);
  for (int i=0; i<m; i++) fscanf(ans, "%d", &rev[i]);
  for (int i=0; i<m; i++) {
    if (rev[i] == 0) { for (int j=0; j<k[id[i]]; j++) *ans_top++ = a[id[i]][j]; }
    else { for (int j=k[id[i]]-1; j>=0; j--) *ans_top++ = a[id[i]][j]; } }

  int l = (int)(ans_top - _ans);
  for (int i=0; i<l; i++) printf("%d\n", _ans[i]);
  puts("");
  for (int i=0; i<l; i++) {
    if (_ans[i] != _ans[l-i-1]) {
      printf("error on %d, %d != %d\n", i, _ans[i], _ans[l-i-1]); exit(1); } }
}
