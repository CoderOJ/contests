#include <iostream>
#include <cstdio>
using namespace std; 
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
#include <bitset>
#include <sstream>

#ifdef ENABLE_LL
#define int long long
#define I "%lld"
#define II "%lld%lld"
#define III "%lld%lld%lld"
#define IIII "%lld%lld%lld%lld"
#define IN "%lld\n"
#define IIN "%lld%lld\n"
#define IIIN "%lld%lld%lld\n"
#define IIIIN "%lld%lld%lld%lld\n"
#else
#define I "%d"
#define II "%d%d"
#define III "%d%d%d"
#define IIII "%d%d%d%d"
#define IN "%d\n"
#define IIN "%d%d\n"
#define IIIN "%d%d%d\n"
#define IIIIN "%d%d%d%d\n"
#endif
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)

typedef pair < int , int > pr; 
typedef pair < pr  , int > prr; 
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } 
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } 
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } 
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
#define L first
#define R second

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif

#ifndef CUSTOM_MAIN

void preInit();
void init(); 
void solve(); 

int32_t main(){ 
preInit();

#ifdef MULTIPLE_TEST_CASES_WITH_T
int T; 

#ifdef _LIB_SCANNER
T = sc.nextInt();
#else
scanf("%d",&T); 
#endif /* _LIB_SCANNER */

while(T--) {init(); solve();} 
#else

#ifdef MULTIPLE_TEST_CASES_WITHOUT_T 
while(1) {
    try {init(); } 
    catch(bool t) {return 0;} 
    solve();
}
#else
init(); solve(); 
#endif /* MULTIPLE_TEST_CASES_WITHOUT_T  */

#endif /* MULTIPLE_TEST_CASES_WITH_T */
    return 0;
}

#endif /* CUSTOM_MAIN */

// my code begins here

const int MOD = (int)(1e9)+9;
const int N =  11;
char s[N][N];
int a[N][N];
int n, m;

char mp[128];

struct Matrix;
struct Matrix {
    int n, m;
    vector < vector < int > > a;

    Matrix (int n, int m) : n(n) , m(m) {
        rep (i,n) a.push_back( vector < int > (m) );
    }

    Matrix multiply(const Matrix & B) const {
        Matrix C(B.n, m);
        rep (i,B.n) rep (j,m) rep (k,n) (C.a[i][j] += a[k][j] * B.a[i][k]) %= MOD;
        return  C;
    }
    Matrix power(int e) const {
        Matrix A = *this;
        Matrix C(n,m);
        rep (i,n) C.a[i][i] = 1;
        while (e) {
            if (e&1) C = C.multiply(A);
            A = A.multiply(A);
            e>>=1;
        }
        return C;
    }
};

struct Node {
    Node* s[4]; 
    bool has[4];
    Node* fail;
    int id;
    int tg;

    Node (int _id = 0) {
        rep (i,4) { s[i] = NULL; has[i] = 0; }
        fail = NULL;
        id=_id;
        tg=0;
    }
};

struct AhoCorasick {
    Node* R;
    int validEnd[105];
    int cnt;
    Matrix* A;

    AhoCorasick () {
        cnt=0;
        R = new Node(cnt++) ;
    }

    void insert(int *a) {
        Node* p=R;
        while (*a != -1) {
            if (p->s[*a] == NULL) p->s[*a] = new Node(cnt++);
            p->has[*a] = 1;
            p = p->s[*a];
            a++;
        }
        p->tg = 1;
    }

    void build() {
        A = new Matrix(cnt,cnt);
        Node *E = R->fail = new Node(-1); 
        rep (i,4) E->s[i] = R;
        queue < Node* > que;
        que.push( R );
        while (!que.empty()) {
            Node* u=que.front(); que.pop();
            validEnd[ u->id ] = u->tg;
            rep (i,4) {
                Node* v=u->s[i];
                if (v == NULL) {
                    u->s[i] = u->fail->s[i];
                } else {
                    A->a[v->id][u->id] = 1; 
                    v->fail = u->fail->s[i];
//                    v->tg |= v->fail->tg;
                    que.push(v);
                }
            }
            rep (i,4) {
                if (u->tg) {
                    Node* ff = u->fail;
                    while (ff != E && ff != NULL) {
                        if (i == 0) { ses(u->id); ses(ff->id); see(ff->has[i]); } 
                        if (ff->has[i]) { A->a[ff->s[i]->id][u->id] = 1; } 
                        ff = ff->fail; } }
            } 
        }
    }

    Matrix get() {
        return *A;
    }
};

#ifdef __LOCALE__
void sss(Matrix &a) {
    for (auto i: a.a) {
        for (auto j: i) cout << j << ' ' ;
        puts("");
    }
}
#else 
void sss(Matrix & x) {}
#endif


void init() {
    scanf(II,&m,&n);
    rep (i,n) scanf("%s", s[i]);
    mp[(int)'A'] = 0;    mp[(int)'C'] = 1;    mp[(int)'G'] = 2;    mp[(int)'T'] = 3; mp[0] = -1;
    rep (i,n) rep (j,N) a[i][j] = mp[(int)s[i][j]];
}

AhoCorasick ac;

void solve() {
    rep (i,n) ac.insert(a[i]);
    ac.build();
    Matrix mul = ac.get();
    sss(mul);
    mul = mul.power(m);
    int ans=0; 
    rep(i,ac.cnt) if (ac.validEnd[i]) { 
        ses(i);see(mul.a[i][0]); (ans+=mul.a[i][0]) %= MOD; }
    printf(IN,ans);
}

void preInit() {

}
 
