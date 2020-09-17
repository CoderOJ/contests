#include <bits/stdc++.h>
using namespace std;

struct bcj{
    static const int L = 1e5 + 5;
    int pt[L];

    bcj(int n = L - 1){
        for (int i=0;i<=n;i++){
            pt[i] = i;
        }
    }

    void clear(int n = L - 1){
	for (int i=0;i<=n;i++){
	    pt[i] = i;
	}
    }

    int find(int x){
        if (pt[x] == x){
            return x;
        }
        return pt[x] = find(pt[x]);
    }

    void add(int a,int b){
        int fa,fb;
        fa = find(a);
        fb = find(b);
        pt[fb] = fa;
    }

    bool uni(int a,int b){
        return (find(a) == find(b));
    }
};

const int N = 100005;
int fib[100];
bcj book;

void init_fib(){
   fib[1] = 1;
   for (int i=2;fib[i - 1] <= N;i++){
       fib[i] = fib[i - 1] + fib[i - 2];
   }
}

bool check_fib(int lower , int upper){
    for (int i=1;fib[i - 1] <= N;i++){
	if (fib[i] <= upper && fib[i] >= lower){
	    return 1;
	}
    }
    return 0;
}

struct Edge{
    int u,v,e;
    Edge(){}
    Edge(int uu,int vv,int ee):u(uu),v(vv),e(ee){}

    bool operator < (const Edge& B) const {
	return e < B.e;
    }
};

Edge edge[N];

int solve(int n,int m,int cs){
    book.clear(n);
    int ans = 0,tot = 0;
    for (int i=1;i<=m;i++){
	int u = edge[i].u;
	int v = edge[i].v;
	int e = edge[i].e;
	if (e == cs && !book.uni(u,v)){
	    book.add(u,v);
	    ans += e;
	    tot ++;
	}
    }
    for (int i=1;i<=m;i++){
	int u = edge[i].u;
	int v = edge[i].v;
	int e = edge[i].e;
	if (e != cs && !book.uni(u,v)){
	    book.add(u,v);
	    ans += e;
	    tot ++;
	}
    }
    if (tot == n - 1){
	return ans;
    }else{
	return -1;
    }
}

int main(){
    init_fib();
    int T;
    scanf("%d",&T);
    for (int cs = 1;cs <= T;cs++){
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
	    int uu,vv,ee;
	    scanf("%d%d%d",&uu,&vv,&ee);
	    edge[i] = Edge(uu,vv,ee);
        }
	int a1 = solve(n,m,0);
	int a2 = solve(n,m,1);
	bool ans = check_fib(a1,a2);
	printf("Case #%d: %s\n",cs,(ans?"Yes":"No"));
    }
    return 0;
}
