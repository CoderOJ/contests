#include <iostream>
#include <cstdio>
using namespace std; 
#ifndef _LIB_SCANNER
#define _LIB_SCANNER 1

#include <stdio.h>
#include <stdlib.h>

class Scanner {
private:
    static const int BUFFER_SIZE = 10000;
    char buff[BUFFER_SIZE];
    int buffPos, buffLim;

public:
    Scanner () { 
        buffLim = fread(buff, 1, BUFFER_SIZE, stdin);
        buffPos = 0;
    }

private:
    inline void flushBuff() {
        buffLim = fread(buff, 1, BUFFER_SIZE, stdin);
        if (buffLim==0) {
            buff[buffLim++] = '\n';
        }
        buffPos = 0; 
    }

    inline bool isWS(char t) {
        return t==' ' || t=='\n';
    }

    inline bool isDig(char t) {
        return t>='0' && t<='9'; 
    }

    void nextPos() {
        buffPos++;
        if (buffPos == buffLim) {
            flushBuff();
        }
    }

#define getChar() buff[buffPos]

public:
    inline char getchar() {
        char ch=getChar();
        nextPos();
        return ch; 
    }

    inline void next(char* s) {
        while ( isWS(getChar()) ) {
            nextPos(); 
        }
        while ( !isWS(getChar()) ) {
            *s = getChar(); s++;
            nextPos();
        }
        *s = '\0';
    }

    inline void nextLine(char* s) {
        while ( getChar()!='\n' ) {
            nextPos();
        }
        if ( getChar()=='\n' ) {
            nextPos();
        }
        while ( getChar() != '\n' ) {
            *s = getChar(); s++;
            buffPos++;
        }
        *s = '\0';
    }

    inline int nextInt() {
        while ( !isDig(getChar()) ) {
            nextPos();
        }
        int sign = (getChar() == '-') ? nextPos(),-1 : 1;
        int res = 0;
        while (isDig(getChar())) {
            res = res*10 + getChar()-'0';
            nextPos();
        }
        return res * sign; 
    }

    inline double nextDouble() {
        while ( isWS(getChar()) ) {
            nextPos();
        }
        int sign = (getChar() == '-') ? nextPos(),-1 : 1;
        double res = 0;
        while (isDig(getChar())) {
            res = res * 10 + getChar()-'0';
            nextPos();
        }
        if (getChar() == '.') {
            nextPos();
            double ep = 1;
            while (isDig(getChar())) {
                ep *= 0.1;
                res += ep * (getChar()-'0');
                nextPos();
            }
        }
        return sign * res;
    }

    inline char nextChar() {
        while (isWS(getChar())) nextPos();
        char res = getChar(); nextPos();
        return res;
    }

#undef getChar
};
Scanner sc;
#endif /* _LIB_SCANNER */
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


const int N = 50005;

struct LCT {
    struct Node {
        Node *s[2], *f;
        int v, m;
        int tg;
        
        Node() { s[0]=s[1]=f=NULL; v=m=tg=0; }
        inline bool isRoot() { 
            if (f==NULL) return 1;
            return f->s[0] != this && f->s[1] != this; }
        inline bool getSon() {
            return this == f->s[1]; }
        inline void pushUp() {
            m = v; 
            if (s[0]) checkMin(m,s[0]->m); 
            if (s[1]) checkMin(m,s[1]->m); }
        inline void pushRev() {
            tg ^= 1; swap(s[0],s[1]); }
        inline void pushDown() {
            if (tg) { 
                if (s[0]) s[0]->pushRev(); 
                if (s[1]) s[1]->pushRev(); }
            tg = 0; }
        void push() {
            if (!isRoot()) { f->push(); }
            pushDown(); }
        void rotate() {
            bool cc = getSon();
            Node *uu = this, *ff = f, *aa = ff->f;
            if (!ff->isRoot()) aa->s[ ff->getSon() ] = uu;
            ff->f = uu; ff->s[cc] = uu->s[!cc];
            uu->f = aa; uu->s[!cc] = ff;
            if (ff->s[cc] != NULL) { ff->s[cc]->f = ff; }
            ff->pushUp(); uu->pushUp(); }
        void _splay() {
            if (isRoot()) return;
            if (f->isRoot()) { rotate(); return; }
            (f->getSon() == getSon() ? f : this) -> rotate(); rotate();
            _splay(); }
        Node* splay() {
            push(); _splay(); 
            return this; }
        void access() {
            Node *uu=this, *ss=NULL;
            while (uu!=NULL) {
                uu->splay(); uu->s[1]=ss; uu->pushUp();
                ss = uu; uu = uu->f; } 
            splay(); }
        void makeRoot() {
            access(); pushRev(); }
        Node* findRoot() {
            access();
            pushDown(); Node* uu=this;
            while (uu->s[0] != NULL) { uu->pushDown(); uu=uu->s[0]; }
            return uu; }
        void update(int val) {
            splay(); v = val; pushUp(); }
    };

    Node p[N*2];

    void link(int u, int v) {
        p[u].makeRoot(); p[u].f = &p[v]; }
    void cut(int u, int v) {
        p[u].makeRoot(); p[v].access();
        p[v].s[0] = p[u].f = NULL; p[v].pushUp(); }
    void update(int u, int val) {
        p[u].update(val); }
    bool isConnect(int u, int v) {
        return p[u].findRoot() == p[v].findRoot(); }
    int query(int u, int v) {
        p[u].makeRoot(); p[v].access(); 
        return p[v].m; }
};

LCT T;

const int INF = 0x3f3f3f3f;
int n,m;
pr etu[N];
int rid[N];

void preInit() {
    n = sc.nextInt(); m = sc.nextInt();
    repa (i,n) T.update(i,INF); 
    rep (i,m) rid[i] = m;
    rep (i,m) {
        int u=sc.nextInt(), v=sc.nextInt(); 
        etu[i] = {u,v};
        if (T.isConnect(u,v)) {
            int cid = T.query(u,v);
            ses(cid);see(i);
            rid[cid] = i;
            T.cut(etu[cid].L,cid+n+1); T.cut(cid+n+1,etu[cid].R);  }
        T.update(n+i+1,i);
        T.link(u,n+i+1); T.link(n+i+1,v);  }
}

int q;
struct Query { int time, val, id; };
vector <Query> qrs;
int ans[N*2];

struct FTree {
    int a[N+10];
    FTree () { memset(a,0,sizeof(a)); }
    inline int low(int u) { return u&(-u); }
    void modify(int u, int val) { u += 4;
        while (u<N+10) { a[u] += val; u += low(u); } }
    int query(int u) { u += 4;
        int res =0;
        while (u) { res += a[u]; u -= low(u); } 
        return res; }
};

void init() {
    q = sc.nextInt();
    rep (i,q) { 
        int l = sc.nextInt()-1, r = sc.nextInt()-1;
        qrs.push_back( {r+1,r,i*2} ); qrs.push_back( {l,r,i*2+1} ); }
    sort(qrs.begin(), qrs.end(), [](Query a, Query b) { return a.time > b.time; });
    int inCnt=m; FTree st;
    for (auto q: qrs) {
        while (inCnt >= q.time) { st.modify(rid[inCnt],1); inCnt--; }
        ans[q.id] = st.query(m+5) - st.query(q.val); }
}

void solve() {
    rep (i,q) { 
        printf(IN,n-ans[i*2+1]+ans[i*2]); }
}
