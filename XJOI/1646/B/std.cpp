#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}

LL dis[100005][2];
int head[100005], nxt[400005], cnt, e[400005], val[400005];

inline void add(int u, int v, int w){
    nxt[++ cnt] = head[u];
    head[u] = cnt;
    e[cnt] = v;
    val[cnt] = w;
}
int n, m, k;
int sp[100005];
queue <int> q;
bitset <100005> inq;

inline LL SPFA(){
    memset(dis, 127, sizeof(dis));
    for (register int i = 1;i <= k;i ++){
        q.push(sp[i]);dis[sp[i]][0] = 0;
        inq[sp[i]] = 1;
    }
    while(!q.empty()){
        int x = q.front();q.pop();
        inq[x] = 0;
        for (register int i = head[x];i;i = nxt[i]){
            if(dis[e[i]][0] > dis[x][0] + val[i]){
                dis[e[i]][1] = dis[e[i]][0];
                dis[e[i]][0] = dis[x][0] + val[i];
                if(!inq[e[i]]) {q.push(e[i]);inq[e[i]] = 1;}
                if(dis[e[i]][1] > dis[x][1] + val[i]) dis[e[i]][1] = dis[x][1] + val[i];
            }
            else{
                if(dis[e[i]][1] > dis[x][0] + val[i]){
                    dis[e[i]][1] = dis[x][0] + val[i];
                    if(!inq[e[i]]) {q.push(e[i]);inq[e[i]] = 1;}
                }
            }
        }
    }
    LL ans = 0x3f3f3f3f3f3f3f3f;
    for (register int i = 1;i <= k;i ++){
        if(ans > dis[sp[i]][1]) ans = dis[sp[i]][1];
    }
    return ans;
}

int main(){
    read(n);read(m);read(k);
    for (register int i = 1;i <= m;i ++){
        int u, v, w;read(u);read(v);read(w);
        add(u, v, w);add(v, u, w);
    }
    for (register int i = 1;i <= k;i ++) read(sp[i]);
    fprint(SPFA(), 10);
    return 0;
}

