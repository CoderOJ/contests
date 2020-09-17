#include <bits/stdc++.h>
using namespace std;
void init(); void solve(); int main(){ init(); solve(); return 0;}
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)

const int N = 5000005; const int M = 200005;
char s[N]; int n, m; int l[M], r[M], k[M];
int prefix[N], suffix[N]; int bars[N]; int id[N]; int barsCnt;
struct Qr { int l,r,k,i,a; } qs[M];

void init() {
    scanf("%s",s+1); n=strlen(s+1); scanf("%d",&m); rep (i,m) scanf("%d%d%d",&l[i],&r[i],&k[i]);
    prefix[0]=-1;    repa (i,n)   prefix[i] = s[i]=='T' ? i : prefix[i-1];
    suffix[n+1]=n+1; repb (i,n,1) suffix[i] = s[i]=='T' ? i : suffix[i+1];
    int ls=0; repa (i,n) if (s[i]=='T') { bars[barsCnt++]=i-ls-1; ls=i; id[i]=barsCnt; } }

int nxt[N], anss[N];
void treat() {
    sort(qs, qs+m, [](Qr a, Qr b) { return a.k<b.k; });
    int qsStart=0; rep (i,(int)barsCnt) nxt[i]=i+1; int head=0;
    while (qsStart < m) {
        vector <int> qks; int qsEnd=qsStart; 
        while (qsEnd<m && qs[qsEnd].k == qs[qsStart].k) { qks.push_back(qs[qsEnd].l); qks.push_back(qs[qsEnd].r); qsEnd++; } sort(qks.begin(), qks.end());
        int k=qs[qsStart].k; int *pre=&head, pos=head; int ans=0; int lrs=0;
        while (lrs<(int)qks.size() && qks[lrs] < head) { anss[qks[lrs]] = 0; lrs++; }
        while (pos<(int)barsCnt) {
            ans += bars[pos]/k; int to=nxt[pos]; while(lrs<(int)qks.size() && qks[lrs] < to) { anss[qks[lrs]]=ans; lrs++; }
            if (bars[pos] <= k) { *pre=to; pos=to;} 
            else { pre=&nxt[pos]; pos=to; } }
        repi (i,qsStart, qsEnd-1) qs[i].a= anss[qs[i].r]-anss[qs[i].l]; 
        qsStart=qsEnd; }
    sort(qs, qs+m, [](Qr a, Qr b) { return a.i < b.i; }); } 

inline long long interval(int l, int r, int k, int i) { int res=qs[i].a; return 1LL*(res+r-l)*k; }
inline int originGet(int u, int k) { return ((u-1)/k+1)*k; }
void solve() {
    rep (i,m) if (prefix[r[i]] >= l[i]) { int ll=suffix[l[i]], rr=prefix[r[i]]; qs[i]={id[ll]-1, id[rr]-1, k[i], i, 0}; }
    treat(); 
    rep (i,m) {
        if (prefix[r[i]] < l[i]) { printf("%d\n", r[i]-l[i]+1); }
        else { int ll=suffix[l[i]], rr=prefix[r[i]]; printf("%lld\n", r[i]-rr + originGet(ll-l[i]+1, k[i]) + interval(id[ll]-1, id[rr]-1, k[i], i)); } } }
