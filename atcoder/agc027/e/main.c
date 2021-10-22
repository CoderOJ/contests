#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MOD 1000000007
#define N 100005

char s[N];
int next[N][2];
int cnt[N];
int n;

int main()
{
  scanf("%s", s);
  n = (int)strlen(s);

  bool same_adj = false;
  for (int i = 0; i + 1 < n; i++)
    if (s[i] == s[i + 1])
      same_adj = true;
  if (!same_adj)
  {
    puts("1");
    return 0;
  }

  int fail = n + 1;
  next[n][0] = fail;
  next[n][1] = fail;
  next[fail][0] = fail;
  next[fail][1] = fail;
  for (int i = n - 1; i >= 0; i--)
  {
    int cur = s[i] - 'a';
    next[i][cur] = i + 1;
    next[i][!cur] = next[i + 1][cur];
  }
  cnt[n] = 1;
  int sum = 0;
  for (int i = n - 1; i >= 1; i--)
  {
    sum += (s[i] - 'a' + 1);
    cnt[i] = (sum % 3 == 0);
  }
  for (int i = n - 1; i >= 0; i--)
    cnt[i] = (cnt[i] + cnt[next[i][0]] + cnt[next[i][1]]) % MOD;
  
  printf("%d\n", cnt[0]);

  return 0;
}
