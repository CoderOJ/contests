#include <cstdio>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 500;
const double ST = 1;
const double INF = 1e4;

map < string , int > mp;
char str[N];
double dis[N][N];

void init(int n){
    mp.clear();
    for (int i=1;i<=n;i++){
	for (int j=1;j<=n;j++){
	    dis[i][j] = (i != j) ? INF : ST;
	}
    }
}

void floyd(int n){
    for (int i=1;i<=n;i++){
	for (int j=1;j<=n;j++){
	    for (int k=1;k<=n;k++){
		dis[i][j] = max(dis[i][j],dis[i][k] * dis[k][j]);
	    }
	}
    }
}

int main(){
    int T = 1;
    while (1){
	int n;
	scanf("%d",&n);
	if (!n){
	    return 0;
	}
	init(n);
	for (int i=1;i<=n;i++){
	    scanf("%s",str);
	    mp [str] = i;
	}
	int m;
	scanf("%d",&m);
	for (int i=1;i<=m;i++){
	    scanf("%s",str);
	    int u = mp [str];
	    double e ;
	    scanf("%lf",&e);
	    scanf("%s",str);
	    int v = mp [str];
	    dis[u][v] = e * ST;
	}
	floyd(n);
	bool flag = 0;
	for (int i=1;i<=n;i++){
	    if (dis[i][i] > ST){
		flag = 1;
		break;
	    }
	}
	printf("Case %d: %s\n",T++,(flag?"Yes":"No"));
    }
    return 0;
}
