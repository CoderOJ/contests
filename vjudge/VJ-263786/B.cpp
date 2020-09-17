#include <bits/stdc++.h>
using namespace std;

#define TO first
#define DIS second
#define Edge pair < int , int >

const int N = 10005;
vector < Edge > e[N];
int deep[N];

void init(int n){
    for (int i=0;i<=n;i++){
	e[i].clear();
    }
    for (int i=0;i<=n;i++){
	deep[i] = -1;
    }
}

int solve(int foo){
    if (deep[foo] != -1){
	return deep[foo];
    }
    int ans = 0;
    for (int i=0;i<(int)e[foo].size();i++){
	ans = max(ans,solve(e[foo][i].TO) + e[foo][i].DIS);
    }
    return deep[foo] = ans;
}

int main(){
    int n,m;
    while (~scanf("%d%d",&n,&m)){
	init(n);
	for (int i=1;i<=m;i++){
	    int u,v,ee;
	    scanf("%d%d%d",&u,&v,&ee);
	    e[u].push_back( Edge(v,ee) );
	}
	int ans = 0;
	for (int i=0;i<n;i++){
	    ans = max(ans,solve(i) + 1);
	}
	printf("%d\n",ans);
    }
    return 0;
}
