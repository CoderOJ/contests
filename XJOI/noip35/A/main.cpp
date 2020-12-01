#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

const int N = 100005;
const char noans[] = "No solution!";
char c[N];
int s[N], n;

void
preInit()
{}

void
init()
{}

void
solve()
{
  std::queue<int> q;
  memset(s, 0, sizeof(s));
  scanf("%s", c);
  n = strlen(c);
  int top = 0;
  for (int i = n; i >= 1; i--)
    c[i] = c[i - 1];
  for (int i = 1; i <= n; i++) {
    if (c[i] == '*')
      continue;
    if (!top || c[i] == '(') {
      ++top;
      s[top] = i;
    } else {
      if (c[s[top]] == '(') {
        s[top] = 0;
        top--;
      } else {
        ++top;
        s[top] = i;
      }
    }
  }
  int j = 0;
  while (!q.empty())
    q.pop();
  for (int i = 1; i <= top; i++)
    if (c[s[i]] == ')') {
      while (j < s[i]) {
        j++;
        if (c[j] == '*')
          q.push(j);
      }
      if (q.empty()) {
        puts(noans);
        return;
      }
      int u = q.front();
      q.pop();
      c[u] = '(';
    }
  j = n + 1;
  while (!q.empty())
    q.pop();
  for (int i = top; i >= 1; i--)
    if (c[s[i]] == '(') {
      while (j > s[i]) {
        j--;
        if (c[j] == '*')
          q.push(j);
      }
      if (q.empty()) {
        puts(noans);
        return;
      }
      int u = q.front();
      q.pop();
      c[u] = ')';
    }
  for (int i = 1; i <= n; i++)
    if (c[i] != '*')
      printf("%c", c[i]);
  puts("");
}
