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



const int N = 1000005;

class LCT {
public:
    struct Node {
        Node *s[2], *f;
        int val,tot,rev,equ;
        Node (Node *f=NULL, int val=0) : f(f), val(val) {
            val = tot = rev = equ = 0; } 
        bool isRoot() {
            if (f==NULL) return 1;
            return !(f->s[0]==this || f->s[1]==this); }
        void pushUp() { 
            tot= val; rep (i,2) if (s[i]) { checkMax(tot,s[i]->tot); } }
        void pushRev() {
            swap(s[0], s[1]); rev^=1; }
        void pushEqu() {
            equ = 1; val = tot = 1; }
        void pushDown() {
            if (rev) { rep (i,2) if (s[i]) s[i]->pushRev(); }
            if (equ) { rep (i,2) if (s[i]) s[i]->pushEqu(); }
            rev=equ=0; } 
        void push() {
            if (!isRoot()) f->push(); 
            pushDown(); }
        bool getSon() {
            return f->s[1]==this; }
        void rotate() {
            Node *uu=this, *ff=f, *aa=ff->f; bool ss=getSon();
            if (!ff->isRoot()) aa->s[ ff->getSon() ] = uu;
            ff->s[ss]= uu->s[!ss]; ff->f=uu;
            uu->s[!ss] = ff; uu->f=aa;
            if (ff->s[ss] != NULL) ff->s[ss]->f = ff;
            ff->pushUp(); uu->pushUp();  }
        void _splay() { 
            if (isRoot()) return;
            if (f->isRoot()) { rotate(); return; }
            Node *uu=this, *ff=uu->f;
            ( ff->getSon()==uu->getSon() ? ff : uu ) -> rotate(); rotate(); 
            _splay(); }
        void splay() {
            push(); _splay(); }   
        void access() {
            Node *uu=this, *ss=NULL;
            while (uu!=NULL) {
                uu->splay(); uu->s[1]=ss; uu->pushUp();
                ss = uu; uu=uu->f; } }
        void makeRoot() {
            access(); splay(); pushRev(); }
        Node* straight(int ss) { 
            pushDown(); Node* uu=this; 
            while (uu->s[ss]!=NULL) { uu->pushDown(); uu=uu->s[ss];} 
            return uu; }
        Node* findRoot() {
            access(); splay(); return straight(0); }
        void update(int _v) {
            splay(); val=_v; pushUp(); }
    };

    Node p[N];

    void split(Node* u, Node* v) {
        u->makeRoot(); 
        v->access(); v->splay(); }
    void _link(Node* u, Node* v) {
        u->makeRoot(); u->f=v; }
    void link(int _u, int _v) { 
        Node* u=&p[_u]; Node* v=&p[_v];
        _link(u,v); }
    void _cut(Node* u, Node* v) {
        u->makeRoot(); v->access(); v->splay();
        v->s[0] = u->f = NULL; v->pushUp(); }
    void cut(int _u, int _v) {
        Node* u=&p[_u]; Node* v=&p[_v];
        _cut(u,v); }
    void update(int _u, int v) {
        Node* u=&p[_u]; u->update(v); }
    int _query(Node* u, Node* v) {
        split(u,v);
        return v->tot; }
    int query(int _u, int _v) {
        Node* u=&p[_u]; Node* v=&p[_v];
        int res = _query(u,v); 
        p[_v].pushEqu(); 
        return res; }
};

LCT T;

struct Dsu {
    int p[N], sz[N];
    Dsu () { rep (i,N) { p[i] = i; sz[i] = 1; } }
    int get(int u) { return u==p[u] ? u : p[u] = get(p[u]); }
    void merge(int u, int v) {
        int pu=get(u), pv=get(v);
        if (pu==pv) { return; }
        sz[pu] += sz[pv]; p[pv] = pu; }
};

int dep[N], mark[N], fa[N];
int pans[N];
int ans; 
int n,m,c;
Dsu st;

void preInit() {

}

void init() {
    n = sc.nextInt(); m = sc.nextInt(); c = sc.nextInt();
    rep (i,N) { dep[i] = 1; fa[i] = -1; }
}

void solve() {
    rep (i,m) {
        int u=sc.nextInt(), v=sc.nextInt();
        (u+=ans); (v-=ans); 
        if (u>n) { u-=n; } if (v<1) { v+=n; }
        int pu = st.get(u), pv = st.get(v);
        if (pu == pv) {
            if (pans[pu] == -1) { goto nxt; }
            int res = T.query(u,v);
            if (res) { 
                if (st.sz[pu] >= c) { 
                    if (pans[pu]!=-1) {ans -= pans[pu]; } }
                pans[ pu ] = -1; } 
            else {
                pans[ pu ] ++; 
                if (st.sz[pu] >= c) { ans++; } } }
        else {
            int su = st.sz[pu], sv = st.sz[pv];
            if (pans[pu]==-1 || pans[pv]==-1) {
                if (pans[pu] != -1 && su >= c) { ans -= pans[pu]; }
                if (pans[pv] != -1 && sv >= c) { ans -= pans[pv]; }
                pans[pu] = pans[pv] = -1; }
            else {
                if (su+sv >= c) {
                    if (su < c) { ans += pans[pu]; }
                    if (sv < c) { ans += pans[pv]; } } 
                pans[pu] += pans[pv]; }
            st.merge(pu,pv);             
            T.link(u,v); }
nxt:;
        printf(IN,ans); 
    }
}
