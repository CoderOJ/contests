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

void init(){
     
}

int main(){
    init();
    int T;
    scanf("%d",&T);
    while (T--) {
        int h,m;
        double ad;
        char s[10];
        scanf("%d%d%s",&h,&m,s);
        sscanf(s + 3,"%lf",&ad);
        ad -= 8.0;
        if (ad < 0) ad += 24;
        m += (int)(ad * 10 + 0.5) * 6;
        printf("%02d:%02d\n",(h + m / 60) % 24 , m % 60);
    }
    return 0;
}
