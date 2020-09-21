#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<int,int>
#define x first
#define y second
#define mp make_pair
int n,h[200100],up[200100][20],dw[200100][20],q[200100],stk[200100],tp,ord[200100];
bool operator <=(const pii &u,const pii &v){
	return 1ll*u.x*v.y<=1ll*v.x*u.y;
}
bool operator >=(const pii &u,const pii &v){
	return 1ll*u.x*v.y>=1ll*v.x*u.y;
}
pii operator ~(pii u){
	if(u.x<=0)u.x*=-1,u.y*=-1;
	if(u.y<=0)return mp(0x3f3f3f3f,1);
	int tmp=__gcd(u.x,u.y);
	return mp(u.x/tmp,u.y/tmp);
}
pii cross(int x,int y){
	return ~mp(h[x]-h[y],x-y);
}
bool cmp(int x,int y){
	return h[x]<h[y];
}
void print(pii p){
	if(p==mp(0x3f3f3f3f,1))puts("-1");
	else printf("%d/%d\n",p.first,p.second);
}
bool upche(int x,int y){
	if(!up[x][0])return false;
	pii u=cross(up[x][0],x);
	return 1ll*(h[x]-h[y])*u.y<=1ll*u.x*(x-y);
}
bool dwche(int x,int y){
	if(!dw[x][0])return false;
	pii u=cross(dw[x][0],x);
	return 1ll*(h[x]-h[y])*u.y>=1ll*u.x*(x-y);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&h[i]),ord[i]=i;
	for(int i=1;i<=n;i++)scanf("%d",&q[i]);
	sort(ord+1,ord+n+1,cmp);
	tp=0;
	for(int i=n;i;i--){
		int j=ord[i];
		while((tp&&cross(j,stk[tp])==mp(0x3f3f3f3f,1))||(tp>=2&&cross(j,stk[tp-1])<=cross(j,stk[tp])))tp--;
		dw[j][0]=stk[tp],stk[++tp]=j;
	}
	for(int j=1;j<19;j++)for(int i=1;i<=n;i++)dw[i][j]=dw[dw[i][j-1]][j-1];
	tp=0;
	for(int i=1;i<=n;i++){
		int j=ord[i];
		while((tp&&cross(j,stk[tp])==mp(0x3f3f3f3f,1))||(tp>=2&&cross(j,stk[tp-1])<=cross(j,stk[tp])))tp--;
		up[j][0]=stk[tp],stk[++tp]=j;
	}
	for(int j=1;j<19;j++)for(int i=1;i<=n;i++)up[i][j]=up[up[i][j-1]][j-1];
	for(int i=1;i<=n;i++){
		int j=i;
		if(h[q[i]]>h[i]&&upche(i,q[i])){
			for(int k=18;k>=0;k--)if(up[j][k]&&upche(up[j][k],q[i]))j=up[j][k];
			j=up[j][0];
		}
		if(h[q[i]]<h[i]&&dwche(i,q[i])){
			for(int k=18;k>=0;k--)if(dw[j][k]&&dwche(dw[j][k],q[i]))j=dw[j][k];
			j=dw[j][0];
		}
		print(cross(j,q[i]));
	}
	return 0;
}
