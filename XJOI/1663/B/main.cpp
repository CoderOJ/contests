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
#include <bitset>
#include <sstream>
using namespace std; 
#ifndef CUSTOM_MAIN
void init(); void solve(); int main(){ try { 
#ifdef MULTIPLE_TEST_CASES_WITH_T
int T; scanf("%d",&T); while(T--) {init(); solve();} 
#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T 
while(1) {try{init(); } catch(bool t){return 0;} solve(); } 
#else
init(); solve(); 
#endif
#endif
} catch (...) { return 0; } return 0; }
#endif
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
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
#define L first
#define R second
typedef pair < int , int > pr; typedef pair < pr  , int > prr; template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
class Scanner { private: static const int BUFFER_SIZE = 10000; char buff[BUFFER_SIZE]; int buffPos, buffLim; public: Scanner () { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); buffPos = 0; } private: inline void flushBuff() { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); if (buffLim==0) { buff[buffLim++] = '\n'; } buffPos = 0; } inline bool isWS(char t) { return t==' ' || t=='\n'; } inline bool isDig(char t) { return t>='0' && t<='9'; } void nextPos() { buffPos++; if (buffPos == buffLim) { flushBuff(); } } 
#define getChar() buff[buffPos]
public: inline char getchar() { char ch=getChar(); nextPos(); return ch; } inline void next(char* s) { while ( isWS(getChar()) ) { nextPos(); } while ( !isWS(getChar()) ) { *s = getChar(); s++; nextPos(); } *s = '\0'; } inline void nextLine(char* s) { while ( getChar()!='\n' ) { nextPos(); } if ( getChar()=='\n' ) { nextPos(); } while ( getChar() != '\n' ) { *s = getChar(); s++; buffPos++; } *s = '\0'; } inline int nextInt() { while ( !isDig(getChar()) ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; int res = 0; while (isDig(getChar())) { res = res*10 + getChar()-'0'; nextPos(); } return res * sign; } inline double nextDouble() { while ( isWS(getChar()) ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; double res = 0; while (isDig(getChar())) { res = res * 10 + getChar()-'0'; nextPos(); } if (getChar() == '.') { nextPos(); double ep = 1; while (isDig(getChar())) { ep *= 0.1; res += ep * (getChar()-'0'); nextPos(); } } return sign * res; } inline char nextChar() { while (isWS(getChar())) nextPos(); char res = getChar(); nextPos(); return res; } 
#undef getChar
}; 

const int B = 30;
const int SZ = 20000000;
struct Trie {
    struct Node {
        Node *s[2];
        int t; 

        Node () { s[0]=s[1]=NULL; t=0; }
    };

    Node pool[SZ];
    int cnt;
    Node* newNode() {
        return &pool[cnt++]; }

    Node* R;
    Trie () {
        cnt=0;
        R = &pool[cnt++]; }
    void insert(int x) {
        R->t++;
        Node *u = R;
        repb (b,B,0) {
            int cur = (x>>b)&1;
            if (u->s[cur] == NULL) { u->s[cur] = newNode(); }
            u = u->s[cur]; u->t++; } }
    int getAns(int x, int k) {
        Node *u = R; int ans=0;
        repb (b,B,0) {
            int cur = (k>>b)&1;
            int rev = (x>>b)&1;
            if (cur == 0 && u->s[!rev] != NULL) ans += u->s[!rev]->t;
            if (u->s[cur^rev] == NULL) return ans;
            u = u->s[cur^rev]; }
        ans += u->t;
        return ans; }
};

Scanner sc;
int n,k;

void init() {
    n = sc.nextInt();
    k = sc.nextInt();
}

void solve() {
    Trie t;
    long long ans=0;
    int pre = 0; t.insert(0);
    rep (i,n) {
        pre ^= sc.nextInt();
        ans += t.getAns(pre,k);
        t.insert(pre); }
    printf("%lld\n",ans);
    see(t.cnt);
}

