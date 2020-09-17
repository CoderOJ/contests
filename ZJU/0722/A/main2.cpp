#include <bits/stdc++.h>
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
#include <ctime>
using namespace std;

void init();
void solve();
int main(){
try { 

#ifndef CUSTOM_MAIN
#ifdef MULTIPLE_TEST_CASES_WITH_T

int T; scanf("%d",&T); while(T--) {init(); solve();}

#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T

while(1) {try{init(); } catch(bool t){return 0;} solve(); }

#else

init(); solve();

#endif
#endif
#endif

} catch (const char* s) { return 0; }
    return 0;
}

#ifdef ENABLE_LL
#define int long long
#endif

#ifdef ENABLE_LL
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
typedef pair < int , int > pr; typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; } char nextChar(){ char r; ist>>r; return r;} }; Scanner sc(cin);
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } }
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }

inline int ran(int scope) { return rand()%scope; }
inline void add(int&a, int b, int c) { if(b) a=(a+c+b)%b; }
template <class T> void replace(vector<T> &A, int pos, vector<T> B) {
    vector<T> X; rep (i,pos) X.push_back(A[i]);
    for (T i:B) X.push_back(i);
    repi (i,pos+1,(int)(A.size())-1) X.push_back(A[i]);
    A = X; }
struct Minio {
    int attack, health, shield, rattle; 
    void init() {
        scanf(IIII,&attack,&health,&rattle,&shield); }
    bool isDead() { return health<=0; }
    void operate(Minio *B) {
        Minio *A = this;
        if (!A->shield) A->health-=B->attack;
        if ( A->shield) A->shield=0;
        if (!B->shield) B->health-=A->attack;
        if ( B->shield) B->shield=0; } 
    void log() {
        ses(attack);ses(health);ses(rattle);see(shield); } };
vector <Minio> genRattle(int n) {
    vector <Minio> res(n); 
    rep (i,n) {res[i].attack=res[i].health=1;}
    return res; }
struct Player {
    vector <Minio> minio;
    int ready;
    void log() {
        see(ready);
        for (auto i: minio) i.log(); }
    void init() {
        int n; scanf(I,&n); minio.resize(n);
        ready= -1;
        repe (i,minio) minio[i].init(); }
    bool haveMinio() { return minio.size() != 0; }
    bool canAttack() { 
        for (auto i: minio) { if (i.attack) return 1; }
        return 0; }
    void nextReady() {
        ready++; ready %= minio.size();
        while (minio[ready].attack==0) { ready++; ready %= minio.size(); } }
    void operate (Player *B) {
        int Bid=ran(B->minio.size());
        ses(ready);see(Bid);
        minio[ready].operate(&B->minio[Bid]);
        int Arattle=min(   minio[ready].rattle, 7-(int)   minio.size()+1);
        int Brattle=min(B->minio[Bid  ].rattle, 7-(int)B->minio.size()+1);
        if (   minio[ready].isDead()) { replace(   minio,ready,genRattle(Arattle)); add(ready, minio.size(),-1); }
            ses(B->minio[Bid].health); see(B->ready);
        if (B->minio[Bid  ].isDead()) { replace(B->minio,Bid  ,genRattle(Brattle)); 
            if (B->ready == Bid) B->ready--; 
            else if (B->ready > Bid) add(B->ready, B->minio.size(), Brattle-1); } }
};

Player A,B;
Player CA,CB;

void init() {
    A.init(); B.init(); 
    CA=A; CB=B;
}

int winTimes;
void checkWinner(Player *U) { if (U==&A) winTimes++; }
void play() {
    A=CA; B=CB;
    Player *F=&A, *S=&B;
    if (F->minio.size() < S->minio.size()) swap(F,S);
    while (1) {
        if (!F->haveMinio() && !S->haveMinio()) return;
        if (!F->haveMinio()) { checkWinner(S); return; }
        if (!S->haveMinio()) { checkWinner(F); return; } 
        if (!S->canAttack() && !F->canAttack())return;
        if (!F->canAttack()) { swap(F,S); continue; }
        F->nextReady(); 
        F->operate(S);
        F->log();S->log();
        swap(F,S);
    }
}

void solve() {
    srand(0);
    const int TIMES=100000;
    rep (_,TIMES) play();
    printf("%.5lf\n",winTimes*1.0/TIMES);
}


