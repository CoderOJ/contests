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

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
typedef pair < int , int > Point;

int main(){
    int T;
    scanf("%d",&T);
    repa (kase , T) {
        int n;
        scanf("%d",&n);
        printf("Case #%d: ",kase);
        rep (i,n * 2 - 2) {
            char x;
            cin >> x;
            putchar(x == 'E' ? 'S' : 'E');
        }
        puts("");
    }   
    return 0;
}
