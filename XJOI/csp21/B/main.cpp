#include <bits/stdc++.h>
using namespace std;


int l, r;
int f(int l,int r) {
    if (l > r) { return 0; }
    int x = 1;
    while (x*2 <= r) { x *= 2; }
    if (x <= l) { return r-l+1; }
    return f(l, x*2-r-2) + r-x+1; }

int main() {
    freopen("mortal.in","r",stdin);
    freopen("mortal.out","w",stdout);
    scanf("%d%d",&l,&r);
    printf("%d",f(l,r));
}
