#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
using namespace std;
typedef long long LL;
const int N=100005,mod=1e9+7;
string s;
LL n,q,cnt[205],fac[N],inv[N],dp[N],tmp[N],g[60][60];
LL ksm(LL x,LL t){
    LL s=1;
    while(t){
        if(t&1)
            s=s*x%mod;
        x=x*x%mod;
        t>>=1;	
    }
    return s;
}
int id(char c){
    if(c>='a'&&c<='z')
        return c-'a';
    return 26+c-'A';
}
int main(){
    ios::sync_with_stdio(false);
    cin>>s>>q;
    int n=s.size(),m=n/2;
    s=' '+s;
    for(int i=1;i<=n;++i)
        ++cnt[id(s[i])];
    fac[0]=1;
    for(int i=1;i<=n/2;++i)
        fac[i]=fac[i-1]*i%mod;
    inv[n/2]=ksm(fac[n/2],mod-2);
    for(int i=n/2-1;~i;--i)
        inv[i]=inv[i+1]*(i+1)%mod;
    LL W=fac[n/2]*fac[n/2]%mod;
    for(int i=0;i<52;++i)
    	if(cnt[i])
	        W=W*inv[cnt[i]]%mod;
    dp[0]=1;
    for(int i=0;i<52;++i)
       	if(cnt[i])
       		for(int j=m;j>=cnt[i];--j)
	            dp[j]=(dp[j]+dp[j-cnt[i]])%mod;
    for(int i=0;i<52;++i){
    	if(!cnt[i])
    		continue;
        for(int j=0;j<52;++j){
        	if(!cnt[j])
        		continue;
        	memcpy(tmp,dp,sizeof tmp);
            for(int k=cnt[i];k<=m;++k)
                tmp[k]=(tmp[k]-tmp[k-cnt[i]]+mod)%mod;
            if(i!=j)
                for(int k=cnt[j];k<=m;++k)
                    tmp[k]=(tmp[k]-tmp[k-cnt[j]]+mod)%mod;
            g[i][j]=tmp[m];
        }
    }
    while(q--){
        int x,y;
        cin>>x>>y;
        cout<<g[id(s[x])][id(s[y])]*W*2%mod<<'\n';
    }
    return 0;	
}
