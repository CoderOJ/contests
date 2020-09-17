#include<bits/stdc++.h>
#define il inline
#define vd void
#define mod 1000000007
typedef long long ll;
il ll gi(){
    int x; scanf("%d",&x); return x;
}
int n,k;
int a[100010];
int f[100010];
il int pow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}
	return ret;
}
il int solve(int v,int len){
	int x=1000000000-v,xk=pow(x,k);
	f[0]=f[1]=1;
	for(int i=2;i<=len+1;++i){
		f[i]=1ll*(x+1)*f[i-1]%mod;
		if(i-k-1>=0)f[i]=(f[i]-1ll*xk*f[i-k-1]%mod+mod)%mod;
	}
	return f[len+1];
}
int main(){
	n=gi(),k=gi();
	for(int i=1;i<=n-k+1;++i)a[i]=gi();
	int ans=1,len;
	for(int i=1,j;i<=n-k+1;i=j+1){
		j=i;
		while(a[j+1]==a[i])++j;
		len=j-i+k;
		if(i!=1&&a[i-1]>a[i])len-=k;
		if(j!=n-k+1&&a[j+1]>a[i])len-=k;
		if(len>0)ans=1ll*ans*solve(a[i],len)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
