#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)

const int N = 100005;

struct Dsu {
    int p[N];
    void init() { rep (i,N) p[i] = i; }
    int get(int u) { return u==p[u] ? u : p[u] = get(p[u]); }
    void merge(int u, int v) {
        p[get(u)] = get(v); }
    bool query(int u, int v) {
        return get(u) == get(v); }
} st;

set <int> us[3];
vector <int> e[N];
int n,m;

void check(int id) {
    Dsu st; st.init();
    for (int u: us[id]) {
        for (int v: e[u])  {
            if (v < u) continue;
            if (us[id].count(v) == 0) { continue; }
            if (st.query(u,v)) { cout << id << ' ' << u << ' ' << v << endl; puts("Err"); exit(1); }
            st.merge(u,v); } } }

int main(int argc, char** argv) {
    FILE* data = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "r");
    fscanf(data, "%d%d", &n, &m);
    rep (i,m) { 
        int u,v; fscanf(data, "%d%d", &u, &v);
        e[u].push_back(v); e[v].push_back(u); }
    repa (i,n) {
        int c; fscanf(output, "%d", &c);
        us[c].insert(i); }
    check(1); check(2);
    return 0;
}
