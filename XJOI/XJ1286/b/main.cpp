#define ENABLE_LL
#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

#ifdef ENABLE_LL
#define int long long
#endif

#ifdef ENABLE_LL
#define I "%lld"
#define II "%lld%lld"
#define III "%lld%lld%lld"
#define IIII "%lld%lld%lld%lld"
#define IN "%lld\n"
#define IIN "%lld%lld\n"
#define IIIN "%lld%lld%lld\n"
#define IIIIN "%lld%lld%lld%lld\n"
#else
#define I "%d"
#define II "%d%d"
#define III "%d%d%d"
#define IIII "%d%d%d%d"
#define IN "%d\n"
#define IIN "%d%d\n"
#define IIIN "%d%d%d\n"
#define IIIIN "%d%d%d%d\n"
#endif

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; }};
Scanner sc(cin);

const int MAXA=4e5;
int n,m;
int a[MAXA],b[MAXA],fa[MAXA],A[MAXA],B[MAXA],C[MAXA],c[MAXA];
int sum,ans,an[MAXA];

int mysort(int x,int y){
    return C[x]<C[y];
}
int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void init() {
    scanf(II,&n,&m);
    repa (i,n) {
        scanf(II,&a[i],&b[i]);
        fa[i]=i;
        an[i]=1ll*a[i]*b[i];
        sum+=an[i];
    }
}

void solve() {
    int x, y, z;
    ans = sum;
    repa (i,m) scanf(III,&A[i],&B[i],&C[i]),c[i]=i;
    sort (c+1,c+m+1,mysort);
    repa (i,m) {
        x=A[c[i]]; y=B[c[i]]; z=C[c[i]];
        if(find(x) == find(y)) continue;
        x=find(x); y=find(y);
        sum -= an[x]+an[y];
        fa[y] = x;
        b[x] = min(b[x],b[y]);
        a[x] = max(a[x],a[y]);
        an[x] = min(an[x]+an[y],1LL*max(a[x],z)*b[x]);
        sum += an[x];
        checkMin(ans,sum);
    }
    printf(IN,ans);
}

#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
