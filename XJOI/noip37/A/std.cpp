#include <bits/stdc++.h>
typedef long long int64;
typedef unsigned int uint;
typedef unsigned long long uint64;
 
const int N = 5e5;
int n, m, deg[N + 5][2];
bool col[N + 5], del[N + 5];
std::vector<int> E[N + 5];
char str[N + 5];
 
int main() {
    scanf("%d%d%s", &n, &m, str + 1);
    for (int i = 1; i <= n; i++) {
        col[i] = str[i] == 'B';
    }
    for (int u, v, i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        E[u].push_back(v);
        E[v].push_back(u);
        deg[u][col[v]]++;
        deg[v][col[u]]++;
    }
    std::queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i][0] == 0 || deg[i][1] == 0) {
            q.push(i);
            del[i] = true;
        }
    }
    for (; !q.empty(); ) {
        int u = q.front();
        q.pop();
        for (auto v : E[u]) {
            if (!del[v] && --deg[v][col[u]] == 0) {
                q.push(v);
                del[v] = true;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!del[i]) {
            std::cerr << "Yes" << std::endl;
            printf("Yes\n");
            return 0;
        }
    }
    std::cerr << "No" << std::endl;
    printf("No\n");
    return 0;
}
