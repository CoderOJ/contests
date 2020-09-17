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

const int N = 119;
const int K = 5;
bool gab[N + 10];

void init(){
    memset(gab,0,sizeof(gab));
}

char ans[K + 10];
int rec[N + 10];
int recTot[K + 10];
void solve() {
    set < int > chosen;
    repa (mw,K - 1) {
        memset (recTot , 0 , sizeof (recTot));

        rep (i,N) {
            if (gab[i]) continue;
            cout << i * K + mw << endl;
            char x;
            cin >> x;
            rec[i] = x - 'A';
            recTot[ rec[i] ]++;
        }
        
        int mx = 0 , iden ;
        rep (i,K) mx = max(mx , recTot[i]);
        rep (i,K) if (!chosen.count(i) && recTot[i] != mx) iden = i;
        rep (i,N) if (rec[i] != iden) gab[i] = 1;
        ans[mw] = iden;
        chosen.insert(iden);
    }   
    rep (i,K) if (!chosen.count(i)) ans[K] = i;
    repa (i,K) printf("%c" , ans[i] + 'A');
    cout << endl;
}

int main(){
    int T,f;
    scanf("%d%d",&T,&f);
    while (T--) {
        init();
        solve();
        char x;
        cin >> x;   
    }
    return 0;
}
