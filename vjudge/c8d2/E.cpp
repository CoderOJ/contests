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

#define long long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 

int main(){
    int s,d;
    while (~scanf("%d%d",&s,&d)) {
        int inc = s * 5;
        int nd = 0;
        while (inc >= 0) {
            inc -= (s + d);
            nd++;
        }
        int tot = inc * 2 + s * 2 - (s + d) * max(0,nd - 3);
        if (tot < 0) puts("Deficit");
        else printf("%d\n",tot);
    }
    return 0;
}
