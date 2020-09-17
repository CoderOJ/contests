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
typedef vector < int > Int ;

void read(Int& A) {
    A.clear();
    string s;
    cin >> s;
    foreach (i,s) {
        A.push_back(s[i] - '0');
    }
}

int main(){
    int T;
    scanf("%d",&T);
    for (int kase = 1;kase <= T; kase++) {
        Int A;
        read(A);
        Int B , C;
        foreach (i,A) {
            if (A[i] == 4) {
                B.push_back(2);
                C.push_back(2);
            }else {
                B.push_back(0);
                C.push_back(A[i]);
            }
        }
        int st = 0;
        while (B[st] == 0) st++;
        printf("Case #%d: ",kase);
        for (int i = st;i < (int)B.size() ; i++ ) printf("%d",B[i]);
        putchar(' ');
        foreach(i,C) printf("%d",C[i]);
        puts("");
    }
    return 0;
}
