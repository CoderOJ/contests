#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,n) for(int i=0;i<(n);i++)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define SZ(x) ((int)x.size())
#define ALL(x) (x).begin(),(x).end()
#define pc __builtin_popcount
#define ctz __builtin_ctz
using namespace std;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef long long ll;
 
template<class T> void read(T &x){
    int f=0; x=0; char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) f|=(ch=='-');
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    if(f) x=-x;
}
 
const int N=40,N2=N/2+1,M=1<<(N/2);
namespace {
    const int mod=1e9+7;
    inline void add(int &x,int y){
        x=x+y>=mod?x+y-mod:x+y;
    }
    inline void sub(int &x,int y){
        x=x-y<0?x-y+mod:x-y;
    }
    inline int mul(int x,int y){
        return (ull)x*y%mod;
    }
    inline int power(int x,int p){
        int res=1;
        for(;p;p>>=1,x=mul(x,x))
            if(p&1)res=mul(res,x);
        return res;
    }
    inline int getinv(int x){
        return power(x,mod-2);
    }
}
int sum[M],f[N2][M],A[N2],B[N2],inv[N2],n,m,c,Inv;
ull e[N];
 
void path(){
    static int f[M][N];
    for(int s=1;s<(1<<n);s++){
        if(pc(s)==1){
            int k=ctz(s);
            add(f[s][k*2],1);
            add(f[s][k*2+1],1);
        }
        REP(i,n*2){
            int val=f[s][i];
            if(!val) continue;
            REP(j,n){
                if(s>>j&1) continue;
                if(e[i]>>(j*2)&1){
                    add(f[s|(1<<j)][j*2+1],val);
                }
                if(e[i]>>(j*2+1)&1){
                    add(f[s|(1<<j)][j*2],val);
                }
            }
//          printf("# path %d %d\n",s,val);
            add(sum[s],mul(val,Inv));
        }
    }
}
 
void loop(){
    static int f[M][N];
    for(int s=1;s<(1<<n);s++){
        if(pc(s)==1){
            int k=ctz(s);
            add(f[s][k*2+1],1);
        }
        int p=ctz(s);
        REP(i,n*2){
            int val=f[s][i];
            if(!val) continue;
            for(int j=p;j<n;j++){
                if(s>>j&1) continue;
                if(e[i]>>(j*2)&1){
                    add(f[s|(1<<j)][j*2+1],val);
                }
                if(e[i]>>(j*2+1)&1){
                    add(f[s|(1<<j)][j*2],val);
                }
            }
            if(e[i]>>(2*p)&1){
//              printf("# sum %d %d\n",s,val);
                add(sum[s],val);
            }
        }
    }
}
 
void fmt(int *f,int n){
    for(int k=0,d=1;k<n;k++,d<<=1){
        for(int i=0;i<(1<<n);i+=d<<1){
            int *l=f+i,*r=f+i+d;
            REP(j,d)add(*r++,*l++);
        }
    }
}
 
void ifmt(int *f,int n){
    for(int k=0,d=1;k<n;k++,d<<=1){
        for(int i=0;i<(1<<n);i+=d<<1){
            int *l=f+i,*r=f+i+d;
            REP(j,d)sub(*r++,*l++);
        }
    }
}
const ull magic=16ull*mod*mod;
inline ull fix(ull x){
    return x>=magic?x-magic:x;
}
void Exp(int *a,int *b,int n){
    rep(k,1,n){
        a[k-1]=mul(a[k],k);
    }
    b[0]=1;
    rep(k,1,n){
        ull res=0;
        rep(i,0,k-1){
            res=fix(res+(ull)a[i]*b[k-1-i]);
        }
        b[k]=mul(res%mod,inv[k]);
    }
}
 
int solve(){
    REP(s,1<<n){
        f[pc(s)][s]=sum[s];
    }
    rep(i,0,n) fmt(f[i],n);
    REP(s,1<<n){
        rep(i,0,n) A[i]=f[i][s];
        Exp(A,B,n);
        rep(i,0,n) f[i][s]=B[i];
    }
    ifmt(f[n],n);
    return f[n][(1<<n)-1];
}
 
int main(){
    read(n),read(m),read(c);
    Inv=getinv(mul(c,2));
    n=(n+1)/2;
    rep(i,1,m){
        int x,y;
        read(x),x--;
        read(y),y--;
        e[x]|=ull(1)<<y;
        e[y]|=ull(1)<<x;
    }
    path();
    loop();
    rep(i,1,n){
        inv[i]=getinv(i);
    }
    int ans=solve();
    ans=mul(ans,power(c,n));
    cout<<ans<<endl;
    return 0;
}
