#include "/home/jack/code/creats/gpl.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

const int N = 100005;
char s[N]; int n;

int count(char s[], int n) {
  static int pre[N]; int ans = 1;
  pre[0] = 0;
  for (int i=1; i<n; ++i) {
    int pos = pre[i-1];
    while (pos && s[pos] != s[i]) { pos = pre[pos-1]; }
    if (s[pos] == s[i]) { pos++; }
    pre[i] = pos; 
    ans += !( (pos*2 >= (i+1)) && (i+1) % (i+1-pos) == 0 ); }
  return ans;
}

void preInit() { } void init() {
  scanf("%s", s); n = std::strlen(s); 
} void solve() {
  long long ans = 0;
  for (int i=0; i<n; ++i) {
    ans += count(s+i, n-i); }
  printf("%lld\n", ans);
}
