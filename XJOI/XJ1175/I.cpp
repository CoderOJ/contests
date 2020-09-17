#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second

const int N = 30;
const int M = 1000;
int n,m;
bool isf = 1;
char a[M] , b[M];
vector < int > e[N];
int vis[N];
int pre[N];

void init(){
    scanf("%d%d",&n,&m);
    rep (i,n) {
        scanf("%s%s",a,b); int u = a[0] - 'A' , v = b[0] - 'A';
        e[u].push_back(v);
        e[v].push_back(u);
    }
}

void bfs(int s , int t) {
    memset (vis,0,sizeof(vis));
    memset (pre,0,sizeof(pre));
    queue < int > que;
    que.push(s);
    vis[s] = 1;
    while (!que.empty()) {
        int pos = que.front() ; que.pop();
        //see(char(pos + 'A'));
        if (pos == t) break;
        
        foreach(i,e[pos]) {
            int v = e[pos][i];
            if (!vis[v]) {
                vis[v] = 1;
                que.push(v);
                pre[v] = pos;   
            }
        }
    }
    //see("pass");
    vector < char > ans;
    for (int i=t;i!=s;i = pre[i]) ans.push_back(i + 'A');
    ans.push_back(s + 'A');
    reverse(ans.begin() , ans.end());
    if (!isf) printf(" ");
    else isf = 0;
    foreach(i,ans) printf("%c",ans[i]);
}

void solve() {
    rep (i,m) {
        scanf("%s%s",a,b);
        bfs(a[0] - 'A' , b[0] - 'A');
    }
}

int main(){
    init();
    solve();
    return 0;
}
