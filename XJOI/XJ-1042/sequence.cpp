#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int a[N];

int main(){
#ifndef __LOCALE__
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
#endif
    int n,x,y;
    scanf("%d%d%d",&n,&x,&y);
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    sort(a + 1,a + n + 1);
    int f = n - x * y + 1;
    long long ans = 0;
    for (int i=f;i<=n;i++){
        ans += (long long) a[i];
    }
    printf("%lld\n",ans);
    return 0;
}
