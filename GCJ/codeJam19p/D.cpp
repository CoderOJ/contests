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

const int N = 1024;
int a[N];
int rec[N];
int n,b,f;

void send (int len) {
    int mesg[N];
    rep (i,n) mesg[i] = (i % (len * 2)) >= len;
    rep (i,n) cout << mesg[i] ;
    cout << endl;
}

void get (int n) {
    rep (i,n - b) {
        char x;
        cin >> x;
        rec[i] = x - '0';
    }
}

void showA() {
    rep (i,n) cout << a[i] << ' ';
    cout << endl;
}

int main(){
    int T;
    scanf("%d",&T);
    repa (kase , T) {
        scanf("%d%d%d",&n,&b,&f);
        send (16);
        get (n);
        vector < int > c;
        c.push_back(1);
        repa (i,n - b - 1) {
            if (rec[i] == rec[i - 1]) c[c.size() - 1]++;
            else c.push_back(1);
        }
        if ((int)c.size() != (n - 1) / 16 + 1) c.push_back(0);
        for (int i=0;i<n;i+=16) a[i] = min(16 , n - i) - c[i / 16];

showA();
        for (int len = 8;len > 0;len /= 2) {
            send (len);
            get (n);
            int idx = 0;
            for (int st = 0;st < n;st += len * 2) {
                int sz = min(len * 2, n - st) - a[st];
                int cnt1 = 0,cnt0 = 0;
                for (int i=idx;i<idx + sz;i++) (rec[i] == 0 ? cnt0 : cnt1) ++;   
                a[st] = min(len,n - st) - cnt0;
                a[st + len] = min(len , max(n - st - len , 0)) - cnt1;
                idx += sz;
            }
        }

        rep (i,n) if (a[i]) cout << i << ' ';
        cout << endl;
        scanf("%d",&n);

    }
    return 0;
}
