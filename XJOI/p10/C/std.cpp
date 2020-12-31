#include <bits/stdc++.h>
using namespace std ;
const int N = 1e6,M = N+10,mod = 998244353 ;
inline int add(int a,int b){ return a+b >= mod ? a+b-mod : a+b ; }
inline int sub(int a,int b){ return a >= b ? a-b : a-b+mod ; }
inline int mul(int a,int b){ return 1ll*a*b%mod ; }
inline int power(int a,int b){
    int res = 1 ;
    for( ; b ; b >>= 1){
        if(b&1) res = mul(res,a) ;
        a = mul(a,a) ;
    }
    return res ;
}
int fac[M],ifac[M],inv[M] ;
inline void prework(int n){
    fac[0] = fac[1] = inv[0] = inv[1] = ifac[0] = ifac[1] = 1 ;
    for(int i = 2 ; i <= n ; i++) inv[i] = mul(sub(mod,mod/i),inv[mod%i]) ;
    for(int i = 2 ; i <= n ; i++) fac[i] = mul(fac[i-1],i) ;
    for(int i = 2 ; i <= n ; i++) ifac[i] = mul(ifac[i-1],inv[i]) ;
}
inline int C(int n,int m){ return mul(fac[n],mul(ifac[m],ifac[n-m])) ; }
int n,p,q,P[M],Q[M],f[M] ;
int main(){
    prework(N) ;
    int Inv = power(2,mod-2) ;
    cin >> n >> p ; q = sub(1,p) ;
    if(p == Inv){
        for(int i = 1 ; i < n ; i++)
            printf("%d ",mul(C(n,i),power(Inv,1ll*i*(n-i)%(mod-1)))) ;
        return 0 ;
    }
    f[0] = P[0] = Q[0] = 1 ;
    for(int i = 1 ; i <= n ; i++) P[i] = mul(P[i-1],p) ;
    for(int i = 1 ; i <= n ; i++) Q[i] = mul(Q[i-1],q) ;
    for(int i = 1 ; i < n ; i++)
        f[i] = mul(f[i-1],mul(sub(P[n+1-i],Q[n+1-i]),power(sub(P[i],Q[i]),mod-2))) ;
    for(int i = 1 ; i < n ; i++) printf("%d ",f[i]) ;
    return 0 ;
}
