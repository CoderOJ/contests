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

const int N = 100000;
const int M = 5;
int det[N][M];
int n,m,k;
int ans[M];

void init(){
    scanf("%d%d%d",&n,&m,&k);
    rep (i,n) rep (j,m) scanf ("%d",&det[i][j]);
    ans[m - 1] = k;
}

int head[M];
int start;
vector < pair < int , int > > que[M];
int mxlen;

inline bool empty(int i) {return (int)que[i].size() == head[i];}
inline pair < int , int > back(int i) {return que[i][(int)que[i].size() - 1];}
void push (int a[],int idx){
    rep (i,m){
        pair < int , int > foo (a[i],idx);
        while (!empty(i) && back(i).first < foo.first) que[i].pop_back(); 
        que[i].push_back(foo);
    }
}

int sumMax() {
    int res = 0;
    rep (i,m) {
        res += que[i][head[i]].first;
        see(res);
    }
    return res;
}

void pop () {
    while (!empty(0) && sumMax() > k){
        rep (i,m) if (que[i][head[i]].second == start) head[i]++;
        start ++;
    }
}

void solve(){
    rep (i,n) {
        push (det[i],i);
        pop ();
        see(i);
        see(start);
        if (i - start + 1 > mxlen){
            rep (j,m) ans[j] = que[j][head[j]].first;
            mxlen = i - start +  1;
        }
    }
}

int main(){
    init();
    solve();
    rep (i,m) printf ("%d " , ans[i] );
    puts(""); 
    return 0;
}
