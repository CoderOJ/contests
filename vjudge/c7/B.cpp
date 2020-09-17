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
#include <stack>
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

const int N = 100005;
int n;
int ans;
char s[N];

void init(){
    ans = 0;
    scanf("%d",&n);
    getchar();
}

typedef pair < int , int > Skey;
#define ri first     /*   specially for "))...))((...(("   */
#define le second   /*     */

Skey get () {
    scanf("%s",s);
    int len = strlen(s);
    stack < char > st;
    rep (i , len) {
        if (s[i] == '(') st.push('(');
        else {
            if (!st.empty() && st.top() == '(') {
                ans += 2;
                st.pop();
            }else {
                st.push(')');
            }
        }
    }
    int r = 0 , l = 0 ;
    while (!st.empty()) {
        (st.top() == ')' ? r : l)++;
        st.pop();
    }
    see(l);
    see(r);
    return Skey ( r , l );
}

bool cmp ( Skey A , Skey B ) {
    if (A.ri < A.le) return B.ri < B.le ? A.ri < B.ri : 1;
    else return B.ri >= B.le ? A.le > B.le : 0;
}

void solve() {
    vector < Skey > rem;
    rep (i,n) rem.push_back ( get() );
    sort (rem.begin() , rem.end() , cmp);
    int ep = 0;
    rep (i,n) {
        ans += 2 * ( min (ep,rem[i].ri) );
        ep = max (0,ep - rem[i].ri) + rem[i].le;
    }
    printf("%d\n",ans);
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--) {
        init();
        solve();
    }
    return 0;
}
