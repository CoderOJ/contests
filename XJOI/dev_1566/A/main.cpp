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

namespace Data {
    int xx,AA,BB,CC;
    void init() { scanf(IIII,&xx,&AA,&BB,&CC); }
    int get () { return xx=(xx*AA+BB)%CC; }
}

struct Role {
    int life, attack; char type, skill;
    void scan() { cin >> attack >> life >> type >> skill; }
};

struct Player {
    vector <Role> a;
    
    Player (int n) {
        a.resize(n);
        rep (i,n) a[i].scan(); }
    // 每当这名玩家棋盘上有一个海盗棋子被移出棋盘,使自己获得 +50 攻击力
    void Ghost() {
        int dpCnt = count_if(a.begin(), a.end(), [](Role a) { return a.type == 'P' && a.life <= 0; });
        for (Role& u: a) { if (u.skill == 'G') { u.attack += 50 * dpCnt; } } }
    // 当这个棋子被移出棋盘后,使这名玩家棋盘上的鱼人棋子获得 +20 攻击力和 +20 生命值
    void King() {
        int dkCnt = count_if(a.begin(), a.end(), [](Role a) { return a.skill == 'K' && a.life <= 0; });
        for (Role &u: a) if (u.type == 'M' && u.life > 0) { u.life += 20*dkCnt; u.attack += 20*dkCnt; } }
        // for (Role &u: a) if (u.type == 'M') { u.life += 20*dkCnt; u.attack += 20*dkCnt; } }
    // 使这名玩家棋盘上的其他鱼人棋子获得 +20 攻击力
    void LeaderInit() {
        int l = (int)(a.size());
        rep (i,l) if (a[i].skill == 'L') {
            rep (j,l) if (i!=j && a[j].type == 'M') { a[j].attack += 20; } } }
    void Leader() {
        int l = (int)(a.size());
        rep (i,l) if (a[i].skill == 'L' && a[i].life <= 0) {
            rep (j,l) if (i!=j && a[j].type == 'M') { a[j].attack -= 20; } } }
    // 每当这名玩家棋盘上的另外一个海盗棋子即将攻击,使那颗棋子获得 +20 攻击力和 +20 生命值
    void Captain(int id) {
        if (a[id].type != 'P') { return; }
        rep (i,(int)(a.size())) if (i != id && a[i].skill == 'C') { a[id].attack += 20; a[id].life += 20; } }
    void clear() {
        vector <Role> b;
        for (Role u: a) { if (u.life > 0) { b.push_back(u); }  }
        a = b; }

    void prefix(int id) {
        Captain(id); }
    void suffix() {
        Leader(); Ghost(); King();
        clear(); }
};

int n;
int As, Bs;

void Doit(Player A, Player B) { 
    A.LeaderInit(); B.LeaderInit();
    while (A.a.size() > 0 && B.a.size() > 0) { 
        int aid = Data::get() % (int)A.a.size();
        int bid = Data::get() % (int)B.a.size();
        A.prefix(aid); B.prefix(bid);
        A.a[aid].life -= B.a[bid].attack;
        B.a[bid].life -= A.a[aid].attack;
        A.suffix(); B.suffix(); }
    As += (int)A.a.size(); Bs += (int)B.a.size(); }

void solve() {
    scanf(I,&n); Data::init();
    Player A(n); Player B(n);
    rep (i,500) { Doit(A,B); }
    printf("%d %d\n",As, Bs);
}


void preInit() { } void init() { }

