/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const ll INF=(ll)5e18;
const int MOD=998244353;
void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
void checkmin(ll &x,ll y){if(x>y) x=y;}
void checkmax(ll &x,ll y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
int S,A,B,P,tp; ll lstans=0;
int Rand(){
    S=(S*A%P+(B^(tp*lstans)))%P;
    S=S<0 ? -S : S;
    return S;
}
const int N=2000005;
const int M=10000005;
int L[M],R[M],n,m; ll a[N],sum1[N],sum2[N];
int pre[N],suf[N],st[N][22],lg[N];
stack<int> stk;
int query(int l,int r){
    int sz=r-l+1,S=lg[sz];
    if(a[st[l][S]]>a[st[r-(1<<S)+1][S]]) return st[l][S];
    else return st[r-(1<<S)+1][S];
}
ll SUB(int l,int r){
    ll tmp=sum2[r-1]-(l==1 ? 0 : sum2[l-2]);
    ll tmp2=sum1[r-1]-(l==1 ? 0 : sum1[l-2]);
    ll delta=n-l+2-(r-l+1);
    return tmp-delta*tmp2;
}
ll fl[N],gl[N],fr[N],gr[N];
 
int main()
{
    n=read(); m=read();
    for(int i=1;i<=n;i++) a[i]=read(),a[i]+=a[i-1];
    S=read(); A=read(); B=read(); P=read(); tp=read();
    for(int i=1;i<=n;i++) sum1[i]=a[i]+sum1[i-1];
    for(int i=1;i<=n;i++) sum2[i]=a[i]*(n-i+1)+sum2[i-1];
    a[0]=INF; stk.push(0);
    for(int i=1;i<=n;i++){
        while(a[stk.top()]<=a[i]) suf[stk.top()]=i,stk.pop();
        pre[i]=stk.top(); stk.push(i);
    }
    for(int i=1;i<=n;i++) st[i][0]=i;
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    for(int j=1;j<=21;j++){
        for(int i=1;i<=n;i++){
            if(i+(1<<j)-1>n) break;
            int to=i+(1<<(j-1));
            if(a[st[i][j-1]]>a[st[to][j-1]]) st[i][j]=st[i][j-1];
            else st[i][j]=st[to][j-1];
        }
    }
    for(int i=1;i<=n;i++)
        fr[i]=a[i]*(i-pre[i])+fr[pre[i]],
        gr[i]=gr[i-1]+fr[i];
    for(int i=n;i>=1;i--)
        fl[i]=a[i]*(suf[i]-i)+fl[suf[i]],
        gl[i]=gl[i+1]+fl[i];
    ll ans=0;
    for(int i=1;i<=m;i++){
        L[i]=Rand()%n+1,R[i]=Rand()%n+1;
        if(L[i]>R[i]) swap(L[i],R[i]);
        int pos=query(L[i],R[i]);
        int l=L[i],r=R[i];
        lstans=1ll*(pos-l+1)*(r-pos+1)*a[pos];
        lstans+=gr[r]-gr[pos]-fr[pos]*(r-pos);
        lstans+=gl[l]-gl[pos]-fl[pos]*(pos-l);
        lstans-=SUB(l,r);
        ans=(ans+(lstans%MOD+MOD)%MOD)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}
