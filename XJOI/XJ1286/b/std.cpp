#include<bits/stdc++.h>
using namespace std;

const int MAXA=4e5;
int n,m;
int a[MAXA],b[MAXA],fa[MAXA],A[MAXA],B[MAXA],C[MAXA],c[MAXA];
long long sum,ans,an[MAXA];

int mysort(int x,int y){
    return C[x]<C[y];
}
int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void init {
    scanf(II,&n,&m);
    repa (i,n) {
        scanf("%d%d",&a[i],&b[i]);
        fa[i]=i;
        an[i]=1ll*a[i]*b[i];
        sum+=an[i];
    }
}

void solve() {
    int x, y, z;
    ans = sum;
    repa (i,m) scanf("%d%d%d",&A[i],&B[i],&C[i]),c[i]=i;
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
        checkMin(ans,sum)l
    }
    printf("%lld",ans);
}
