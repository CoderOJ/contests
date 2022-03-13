#include <stdio.h>
#include <string.h>

#define N 1000005

char s[N];

int s_next[N];
int n, m;

void calc_next(int next[], const char s[], int n)
{
  next[0] = -1;
  for (int i = 0; i < n; i++)
  {
    int p = next[i];
    while (p != -1 && s[p] != s[i])
      p = next[p];
    next[i + 1] = p + 1;
  }
}

int *occur[129];
int  cnt[N];

void calc_occur(const char s[], int n)
{
  for (int i = 0; i < n; i++)
    cnt[(int)s[i]] += 1;
  occur[0] = s_next;
  for (int i = 0; i < 128; i++)
    occur[i + 1] = occur[i] + cnt[i];

  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < n; i++)
  {
    int cid              = s[i];
    occur[cid][cnt[cid]] = i;
    cnt[cid] += 1;
  }
}

int lower_bound(int *l, int *r, int v)
{
  int *rl = l, *rr = r;
  while (rl < rr)
  {
    int *rm = rl + (rr - rl) / 2;
    if (*rm >= v)
      rr = rm;
    else
      rl = rm + 1;
  }
  if (rl == r)
    return n;
  else
    return *rl;
}

int main()
{
  scanf("%s", s);
  n = (int)strlen(s);
  calc_next(s_next, s, n);
  int restart_pos = s_next[n];
  calc_occur(s, n);

  scanf("%s", s);
  m = (int)strlen(s);

  int pos    = 0;
  int br_cnt = 0;

  for (char *c = s; *c; c++)
  {
    int cid = *c;
    /* printf("%d %d\n", cid, pos); */
    if (lower_bound(occur[cid], occur[cid + 1], pos) == n)
    {
      br_cnt += 1;
      pos = restart_pos;
    }
    if (lower_bound(occur[cid], occur[cid + 1], pos) == n)
    {
      puts("INF");
      return 0;
    }
    pos = lower_bound(occur[cid], occur[cid + 1], pos) + 1;
  }

  printf("%d\n", br_cnt);

  return 0;
}
