#include <stdio.h>

class Scanner {
private:
    static const int BUFFER_SIZE = 10000;
    char buff[BUFFER_SIZE];
    int buffPos, buffLim;

public:
    Scanner () { 
        buffLim = fread(buff, 1, BUFFER_SIZE, stdin);
        buffPos = 0;
    }

private:
    inline void flushBuff() {
        buffLim = fread(buff, 1, BUFFER_SIZE, stdin);
        if (buffLim==0) {
            buff[buffLim++] = '\n';
        }
        buffPos = 0; 
    }

    inline bool isWS(char t) {
        return t==' ' || t=='\n';
    }

    inline bool isDig(char t) {
        return t>='0' && t<='9'; 
    }

    void nextPos() {
        buffPos++;
        if (buffPos == buffLim) {
            flushBuff();
        }
    }

#define getChar() buff[buffPos]

public:
      inline int nextInt() {
        while ( !isDig(getChar()) ) {
            nextPos();
        }
        int sign = (getChar() == '-') ? nextPos(),-1 : 1;
        int res = 0;
        while (isDig(getChar())) {
            res = res*10 + getChar()-'0';
            nextPos();
        }
        return res * sign; 
    }

  
#undef getChar
};
Scanner sc;
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#include <algorithm>
#include <vector>
using namespace std;

void init(); 
void solve(); 

int32_t main(){ 
init(); solve(); 
return 0;
}


// my code begins here

const int N = 1000005;
vector <int> e[N];
int n,m,k;

void init() {
    n=sc.nextInt(); m=sc.nextInt(); k=sc.nextInt();
    rep (i,m) { int u=sc.nextInt(), v=sc.nextInt(); e[u].push_back(v); e[v].push_back(u); }
}

int vis[N], dep[N];
vector <int> bans;

void dfs(int u, int f) {
    vis[u] = 1; dep[u] = dep[f]+1;
    for (int v: e[u]) if (v!=f) {
        if (vis[v] && dep[v] < dep[u]) { bans.push_back(dep[u]-dep[v]+1); }
        else if (!vis[v])              { dfs(v,u); } } }

void solve() {
    int exist=0; 
    repa (i,n) { if (!vis[i]) { dfs(i,0); exist++; } }
    int direct = m; for (int b: bans) direct -= b;
    if (direct >= k) {
        exist += k; }
    else {
        exist += direct; k -= direct;
        sort(bans.begin(), bans.end(), [](int a, int b) { return a>b;});
        for (int b: bans) {
            int get = min(k,b);
            exist += max(0,get-1); k -= get; } }
    printf("%d\n",exist);
}
