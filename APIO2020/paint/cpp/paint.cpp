#include "paint.h"

#include <bitset>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr; typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 

const int INF = 0x3f3f3f3f;
const int NN = 100005;
const int MM = 50005;
const int KK = 100005;

int colorWho[KK];
int posWho[NN];

struct STree {
    int a[NN*4];

    inline int ls(int u) { return u+u; }
    inline int rs(int u) { return u+u+1; }
    void pushUp(int u) {
        a[u] = min(a[ls(u)] , a[rs(u)]); }
    
    void modify(int l, int r, int p, int val, int u=1) {
        if (l==p && r==p) { a[u] = val; return; }
        int mid=(l+r)/2;
        if (p <= mid) modify(l,mid,p,val,ls(u));
        if (p >  mid) modify(mid+1,r,p,val,rs(u));
        pushUp(u); }

    int query(int l, int r, int sl, int sr, int u=1) {
        if (sl <= l && sr >= r) return a[u];
        int mid=(l+r)/2 , ans=INF;
        if (sl <= mid) checkMin(ans, query(l,mid,sl,sr,ls(u)));
        if (sr >  mid) checkMin(ans, query(mid+1,r,sl,sr,rs(u)));
        return ans; }
};
STree dp;

int conti[NN];
int contiSum[NN];

inline int isConti(int l, int r) {
    return contiSum[r] - contiSum[l] == r-l; }

int ok[NN];

int minimumInstructions(
    int N, int M, int K, std::vector<int> C,
    std::vector<int> A, std::vector<std::vector<int>> B) {

    memset(colorWho,-1,sizeof(colorWho));
    rep (i,M) rep (j,A[i]) colorWho[ B[i][j] ] = i;
    rep (i,N) {
        if (colorWho[ C[i] ] == -1) return -1;
        else posWho[i] = colorWho[ C[i] ]; }
    
    repa (i,NN-1) {
        int u=posWho[i-1] , v=posWho[i];
        if (v == (u+1)%M) conti[i]=1;
        else conti[i]=0; }
    contiSum[0]=0; repa (i,NN-1) contiSum[i] = contiSum[i-1] + conti[i];

    memset(ok,0,sizeof(ok));
    rep (i,N-M+1) if (isConti(i,i+M-1)) ok[i+M]=1;

    repa (i,N) dp.modify(0,N,i,INF); dp.modify(0,N,0,0);
    repi (i,M,N) if (ok[i]) dp.modify(0,N,i, dp.query(0,N,i-M,i-1)+1);
    int ans = dp.query(0,N,N,N);
    if (ans >= INF) return -1;
    return ans;
}
