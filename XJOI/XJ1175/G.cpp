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

struct Node {
    int x , y;
    int d;

    Node () {}
    Node (int x , int y , int d) : x(x) , y(y) , d(d) {}
};

const int Dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

const int N = 60;
int mp[N][N];
int n,m;
Node it , gl;
Node Err(-1,-1,-1);

void init(){
    scanf("%d%d",&n,&m);
    rep (i,n) rep (j,m) {
        int x; scanf("%d",&x);
        if (x == 1) {
            mp[i][j] = 1; mp[i][j + 1] = 1; mp[i + 1][j] = 1; mp[i + 1][j + 1] = 1;   
        }
    }
}

Node op(Node ig , int opt) {
    opt++;
    Node res;
    if (opt <= 3) res = Node(ig.x + opt * Dir[ig.d][0] , ig.y + opt * Dir[ig.d][1] , ig.d);
    if (opt == 4) res = Node(ig.x , ig.y , (ig.d + 3) % 4);
    if (opt == 5) res = Node(ig.x , ig.y , (ig.d + 1) % 4);
    if (res.x <= 0 || res.x >= n || res.y <= 0 || res.y >= m) return Err;
    return res;
}

bool cmp(Node A , Node B) {
    return A.x == B.x && A.y == B.y;
}

bool operator < (Node A , Node B) {
    return A.x == B.x ? (A.y == B.y ? A.d < B.d : A.y < B.y) : A.x < B.x;
}


void debug(Node x) {
    see(x.x);
    see(x.y);
    see(x.d);
}

map < Node , int > dis;
void bfs() {
    if (mp[it.x][it.y] == 1) {
        puts("-1");
        exit(0);
    }

    dis[it] = 0;
    queue < Node > que;
    que.push(it);
    while (!que.empty()) {
        Node pos = que.front() ; que.pop();
        debug(pos);
        if (cmp(pos,gl)) {
            printf("%d\n" , dis[pos]);
            return ;
        }
        rep (opt,5) {
            Node v = op(pos , opt);
            debug(v);
            if (opt == 2) {
                Node pv = op(pos,1);
                if (mp[pv.x][pv.y] == 1) continue;
            }
            if (cmp(v , Err)) continue;
            if (dis.count(v)) continue;
            if (mp[v.x][v.y]) continue;
            dis[v] = dis[pos] + 1;
            que.push(v);
        }
    }
    puts("-1");
}

int main(){
    init();
    int ix , iy , gx , gy ; scanf("%d%d%d%d",&ix,&iy,&gx,&gy);
    char dr; cin >> dr;
    int d = (dr=='N' ? 0 : (dr=='E' ? 1 : (dr=='S' ? 2 : 3)));
    it = Node(ix,iy,d);
    gl = Node(gx,gy,-1);
    bfs(); 
    return 0;
}
