#include<iostream>
using namespace std;
#include<cstring>
int kkksc03[1000005]; //kkksc03表示此点匹配的是什么。
bool mark[1000005]; //mark标记数组。
//----邻接表存图(准确的说是链式前向星吧)。-----
struct xyq{ 
	int v,next;
}_[1000005];
int head[1000005],tot=1;
void add(int u,int v){
	_[tot].v=v;
	_[tot].next=head[u];
	head[u]=tot;
	++tot;
}
//------------------
bool dfs(int iakioi){ //二分图匹配。这里不多做解释。
	int i;
	for(i=head[iakioi];i;i=_[i].next){
		if(mark[_[i].v]){ 
			continue;
		}
		mark[_[i].v]=1;
		if(!kkksc03[_[i].v]||dfs(kkksc03[_[i].v])){
			kkksc03[_[i].v]=iakioi;
			return true;
		}
	}
	return false;
}
char a[1005][1005];
int x[1005][1005],y[1005][1005];
int main(){
	int n,m,i,j,sumx=1,sumy=1,sum=0;
	cin>>n>>m;
	for(i=1;i<=n;++i){
		for(j=1;j<=m;++j){
			cin>>a[i][j];
			if(a[i][j]=='*'){
				x[i][j]=a[i-1][j]=='*'?x[i-1][j]:sumx++; //如果没有断开,就可以使用同一块木板。
				y[i][j]=a[i][j-1]=='*'?y[i][j-1]:sumy++; //同上。
				add(x[i][j],y[i][j]); 
			}
		}
	}
	for(i=1;i<sumx;++i){ //二分图最大匹配。
		memset(mark,0,sizeof(mark));
		sum+=dfs(i);
	}
	cout<<sum;//二者使用其一,求最小点覆盖。
	return 0;
}
