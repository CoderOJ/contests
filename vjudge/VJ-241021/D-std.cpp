#include <bits/stdc++.h>
using namespace std;
int n, k, p, noww;
int a[100005], f[100005];
char s[100005];
deque<int>q;
inline int ff(int x) {
    return (x + n - 1) % n + 1;
}
inline void Push(int x) {
    while((!q.empty()) && q.back() < x)
        q.pop_back();
    q.push_back(x);
}
int main() {
    scanf("%d%d%d", &n, &k, &p);
    if(k > n)
        k = n;
    noww = k;
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for(int i = 1; i <= k; ++i)
        f[k] += a[i];
    for(int i = k + 1; i <= n; ++i)
        f[i] = f[i - 1] + a[i] - a[i - k];
    for(int i = 1; i < k; ++i)
        f[i] = f[ff(i - 1)] + a[i] - a[ff(i - k)];
    for(int i = n; i >= k; --i)
        Push(f[i]);
    scanf("%s", s + 1);
    for(int i = 1; i <= p; ++i) {
        if(s[i] == '?')
            printf("%d\n", q.front());
        else {
            if((!q.empty()) && q.front() == f[ff(noww + n - k)])
                q.pop_front();
            Push(f[noww = ff(noww - 1)]);
        }
    }
    puts("");
    return 0;
}
