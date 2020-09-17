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
    int T;
    scanf("%d",&T);
    while (T--) {
        int n;
        scanf("%d",&n);
        if (n % 3 == 0) {
            cout << 1LL * (n / 3) * (n / 3) * (n / 3) << endl;
        }else if (n % 4 == 0) {
            cout << 1LL * (n / 4) * (n / 4) * (n / 2) << endl;
        }else {
            puts("-1");
        }
    }   
    return 0;
}
