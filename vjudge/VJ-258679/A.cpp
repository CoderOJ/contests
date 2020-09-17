#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
const int M = 15;
int dig[M];
int pre[N];
int mpn[N];
queue < int > q;
int n,m;

void init(){
    memset(dig,0,sizeof(dig));
    memset(pre,0xff,sizeof(pre));
    memset(mpn,0xff,sizeof(mpn));
    while (!q.empty()){
	q.pop();
    }
}

void read(){
    for (int i=1;i<=m;i++){
	int a;
	scanf("%d",&a);
	dig[a] = 1;
    }
}

int pre_ans(){
    for (int i=1;i<10;i++){
	if (!dig[i] && i % n == 0){
	    return i;
	}
    }
    return -1;
}

void pre_bfs(){
    for (int i=1;i<10;i++){
	if (!dig[i]){
	    int tmp = i % n;
	    mpn[tmp] = i;
	    q.push(tmp);
	}
    }
}

void print_ans(int t){
    if (pre[t] != -1){
	print_ans(pre[t]);
    }
    printf("%d",mpn[t]);
}

void bfs(){
    while (!q.empty()){
	int ft = q.front();
	q.pop();
	for (int i=0;i<10;i++){
	    if (!dig[i]){
		int tmp = (ft * 10 + i) % n;
		if (mpn[tmp] == -1){
		    mpn[tmp] = i;
		    q.push(tmp);
		    pre[tmp] = ft;
		}
		if (tmp == 0){
		    print_ans(tmp);
		    return ;
		}
	    }
	}
    }
    printf("%d",-1);
}


int main(){
    int cs = 1;
    while (~scanf("%d%d",&n,&m)){
	init();
	read();
	printf("Case %d: ",cs);
	cs++;
	if (pre_ans() != -1){
	    printf("%d\n",pre_ans());
	    continue;
	}
	pre_bfs();
	bfs();
	puts("");
    }
    return 0;
}
