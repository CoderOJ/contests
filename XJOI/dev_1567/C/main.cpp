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
#include <stack>

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
//
typedef vector<int> Ty;

bool _is_op(char c);
bool _is_strop(string op);
struct Param {
    vector <string> p;
    inline bool _split(char a, char b) {
        int ia = _is_op(a), ib = _is_op(b);
        if (ia==0 || ib==0) { return ia!=ib; }
        return a!=b; }
    void piece(string s) {
        p.clear(); 
        int midBra = 0;
        for (char c: s) {
            if (c == '[') { midBra++; }
            if (c == ']') { midBra--; }
            if (c == ' ' ) { continue; }
            if (midBra == 0) {
                if (p.empty() || _split( p.back().back(), c)) {
                    p.push_back(""); } }
            p.back().push_back(c); } }
    Param subParam(int l, int r) {
        int len = p.size(); 
        l%=len; if (l<0)  {l+=len;}
        r%=len; if (r<=0) {r+=len;}
        Param re;
        repi (i,l,r-1) { re.p.push_back(p[i]); }
        return re; }
};

namespace DS {
    map <string, Ty> var;
    void declare (string __name, int __len);
    bool isArray(string __param);
    string getSub(string __param);
    string getName(string __param);
    int& access(string __param);
    void clear() { var.clear(); }
}

namespace eval {
    int calc(int a, string op, int b);
    int pri(string op);
    int get_lastOp(Param __p);
    int eval_num(string s);
    int eval(Param __p);
    int eval(string __p);
}


bool _is_op(char c) {
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='<' || c=='>' || c=='=' || c=='(' || c==')'; }
bool _is_strop(string op) {
    return op=="+" || op=="-" || op=="*" || op=="/" ||
           op=="<" || op==">" || op=="==" || op=="(" || op == ")"; }

namespace DS {
    void declare (string __name, int __len) {
        if (!var.count(__name)) { var[__name]=Ty(__len); } }
    bool isArray(string __param) {
        return __param.back() == ']'; }
    string getSub(string __param) {
        int __len = __param.size();
        int id = 0; 
        rep (i,__len) if (__param[i]=='[') { id = i; break; }
        return __param.substr(id+1, __len-id-2); }
    string getName(string __param) {
        int __len = __param.size();
        int id = 0; 
        rep (i,__len) if (__param[i]=='[') { id = i; break; }
        return __param.substr(0,id); } 
    int& access(string __param) {
        if (!isArray(__param)) {
            declare(__param, 1);
            return var[__param][0]; } 
        else {
            Param sub; sub.piece(getSub(__param));
            string name = getName(__param);
            declare(name, 1005);
            return var[ name ][ eval::eval(sub) ]; } }
}


namespace eval {
    int calc(int a, string op, int b) {
        if (op == "+") { return a+b; }
        if (op == "-") { return a-b; }
        if (op == "*") { return a*b; }
        if (op == "/") { return a/b; }
        if (op == "<") { return a<b; }
        if (op == ">") { return a>b; }
        if (op == "==") { return a == b; } 
        throw string("Operator not defined"); }
    int pri(string op) {
        if (op == "==" || op == "<" || op == ">") { return 0; }
        if (op == "+" || op == "-") { return 1; }
        if (op == "*" || op == "/") { return 2; }
        throw string("Operator not defined"); } 
    int get_lastOp(Param __p) {
        int bra = 0;
        int mp = 10, md = -1;
        rep (i,(int)(__p.p.size())) {
            if (__p.p[i] == "(") bra++;
            else if (__p.p[i] == ")") bra--; 
            else if (bra==0 && _is_strop(__p.p[i])) {
                int nmp = pri(__p.p[i]);
                if (nmp <= mp) { mp=nmp; md=i; } } }
        return md; }
    int eval_num(string s) {
        int nnum_cnt = count_if(s.begin(), s.end(), [](char a) { return a<'0' || a>'9'; });
        if (nnum_cnt != 0) {
            return DS::access(s); }
        else {
            int res = 0;
            for (char c: s) {
                res *= 10; res += c-'0'; }
            return res; } }
    int eval(Param __p) {
        if (__p.p.size() == 1) {
           return eval_num(__p.p[0]); }
        int lid = get_lastOp(__p);
        if (lid == -1) {
            return eval(__p.subParam(1,-1)); }
        else {
            int xa = eval(__p.subParam(0,lid));
            int xb = eval(__p.subParam(lid+1,0));
            return calc(xa, __p.p[lid], xb); } }
    int eval(string __p) {
        Param p; p.piece(__p);
        for (string& u: p.p) { if (u=="=") { u = "=="; } }
        return eval(p); }
}

vector <string> split(string s, char __sp=' ') {
    vector <string> res;
    res.push_back("");
    for (char c: s) {
        if (c == __sp || c == '\t') {
            if (res.size() == 0 || res.back() != "") {
                res.push_back(""); } }
        else {
            res.back().push_back(c); } }
    while (res.size() && res.back() == "") { res.pop_back(); }
    return res; }

struct LST {
    static const int N = 1005;
    struct State {
        vector <string> s;
        State *n1, *n2; 

        State () { s.clear(); n1=n2=NULL; }
        State* run() {
            if (s.size() == 0) { return NULL; }
            if (s[0] == "input") {
                int r; scanf(I,&r); DS::access(s[1]) = r; 
                return n1; }
            else if (s[0] == "output") {
                printf(IN, eval::eval( s[1] )); 
                return n1; }
            else if (s[0] == "if") {
                return eval::eval(s[1]) ? n1 : n2; }
            else if (s[0] == "else") {
                return n1; }
            else if (s[0] == "fi") {
                return n1; }
            else if (s[0] == "for") {
                return eval::eval(s[1]) ? n1 : n2; }
            else if (s[0] == "}") {
                return n1; }
            else {
                DS::access(s[0]) = eval::eval(s[1]); 
                return n1; } }
    };
    
    State st[1005];
    int g_n;

    pr findIf(int _st) {
        int cntIf = 0;
        int elseId=-1, fiId=-1;
        repi (i,_st,g_n-1) {
            if (st[i].s[0] == "if") { cntIf++; }
            if (st[i].s[0] == "fi") { cntIf--; }
            if (cntIf == 1 && st[i].s[0] == "else") { elseId=i; }
            if (cntIf == 0 && st[i].s[0] == "fi")   { fiId  =i; } 
            if (cntIf <= 0) { break; } }
        if (elseId == -1) { elseId = fiId; }
        return { elseId, fiId }; }
    string getForA(string __s) {
        int id=0; repe(i,__s) { if (__s[i]==';') { id=i; break; } }
        return __s.substr(4,id-4); }
    string getForB(string __s) {
        int id1=0, id2=0;
        repe (i,__s) { if (__s[i]==';') { id1 = id2; id2 = i; } }
        return __s.substr(id1+1, id2-id1-1); }
    string getForC(string __s) {
        int id1=0, id2=0;
        repe (i,__s) { if (__s[i]==';') { id1 = i; } }
        repe (i,__s) { if (__s[i]==')') { id2 = i; } }
        return __s.substr(id1+1,id2-id1-1); }
    void initFor() { 
        stack <string> lsParam;
        State nst[1005]; int nstCnt=0;
        rep (i,g_n) {
            if (st[i].s[0].substr(0,3) == "for") {
                string A = getForA(st[i].s[0]);
                string B = getForB(st[i].s[0]);
                string C = getForC(st[i].s[0]);
                nst[nstCnt++].s.push_back(A);
                nst[nstCnt].s.push_back("for");
                nst[nstCnt].s.push_back(B); 
                nstCnt++;
                lsParam.push(C); }
            else if (st[i].s[0][0] == '}') {
                nst[nstCnt++].s.push_back(lsParam.top()); lsParam.pop();
                nst[nstCnt++].s.push_back("}"); }
            else {
                nst[nstCnt++] = st[i]; } }
        g_n = nstCnt; 
        rep (i,g_n) st[i] = nst[i]; }
    int findFor(int id) {
        int forCnt = 0;
        repi (i,id,g_n-1) {
            if (st[i].s[0] == "for") { forCnt++; }
            if (st[i].s[0] == "}")   { forCnt--; }
            if (forCnt==0 && st[i].s[0] == "}") { return i; } } 
        return g_n; }
    void log() {
        rep (i,g_n) {
            printf("%3d| ",i);
            for (string u: st[i].s) { cout << u << ' '; }
            puts(""); } }
    void init(int n) {
        g_n = n;
        rep (i,n) {
            string s; getline(cin,s); while (s=="") { getline(cin,s); }
            st[i].s = split(s,' '); }
        initFor();
        rep (i,g_n) {
            if (st[i].s.size() == 1) {
                st[i].s = split(st[i].s[0],'='); } } 
        rep (i,g_n-1) {
            if (st[i].s[0] == "if") {
                pr ifState = findIf(i);
                st[i].n1 = &st[i+1];
                st[i].n2 = &st[ifState.L+1];
                st[ifState.L].n1 = st[ifState.L].n2 = &st[ifState.R+1]; }
            else if (st[i].s[0] == "for") {
                int forState = findFor(i);
                st[i].n1 = &st[i+1];
                st[i].n2 = &st[forState+1];
                st[forState].n1 = st[forState].n2 = &st[i]; }
            else if (st[i].s[0] == "else") { continue; }
            else if (st[i].s[0] == "}") { continue; }
            else {
                st[i].n1 = st[i].n2 = &st[i+1]; } } }
    void run() {
        DS::clear();
        State* u = st;
        while (u != NULL) { u = u->run(); } }
};

void preInit() {

}

void init() {
     
}

void solve() {
    int n; scanf(I,&n);
    LST p; p.init(n);
    int T; scanf(I,&T);
    while (T--) {
        p.run(); }
}
