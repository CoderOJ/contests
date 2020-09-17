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

const int N = 300;
string s[N];
bool hwin[N];
int n;

void init(){
    scanf("%d",&n);
    rep (i,n) cin >> s[i];
    memset(hwin , 0 , sizeof(hwin));
}

const char win[4] = {'S','X','P','R'};
void solve() {
    int mxl = 0;
    string res = "";
    rep (i,n) mxl = max (mxl , (int)s[i].length());
    for (int w = 0;;w++) {
        set < char > al;
        rep (i,n) if (!hwin[i]) al.insert(s[i][w % s[i].size()]);
        if (al.size() == 3) {
            puts("IMPOSSIBLE");
            return ;
        }
        if (al.size() == 1) {
            res = res + win[*al.begin() - 'P'];
            break;
        }
        if (al.size() == 2) {
            char a = *al.begin() , b = *al.rbegin();
            char wo,k;
            if (win[a - 'P'] == b) wo = win[a - 'P'] , k = a;
            if (win[b - 'P'] == a) wo = win[b - 'P'] , k = b;
            res = res + wo;
            rep (i,n) if (s[i][w % s[i].size()] == k) hwin[i] = 1;
        }
    }
    cout << res << endl;
}

int main(){
    int T;
    scanf("%d",&T);
    repa (kas , T) {
        init();
        printf("Case #%d: ",kas);
        solve();
    }   
    return 0;
}
