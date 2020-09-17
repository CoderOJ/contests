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
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second


void init(){
     
}

char a[200];

int main(){
    init();
    int n;
    scanf("%d",&n);
    scanf("%s",a);
    rep (i,n - 1) {
        if (a[i] != '?' && a[i] == a[i + 1]) {
            puts("No");
            return 0;
        }
    }
    if (a[0] == '?' || a[n - 1] == '?') {
        puts("Yes");
        return 0;
    }
    repa (i,n - 2) {
        if (a[i] == '?') {
            if (a[i - 1] == '?' || a[i + 1] == '?') {
                puts("Yes");
                return 0;
            }
            if (a[i - 1] == a[i + 1]) {
                puts("Yes");
                return 0;
            }
        }
    }
    puts("No");
    return 0;
}
