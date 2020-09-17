#pragma GCC optimize(3)
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

#ifdef __LL
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
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; }};
Scanner sc(cin);

string Qs="()[]{}<>=+-*/~!#%^&|:\"?\\";

bool isQ(char x) {
    repe (i,Qs) if (x == Qs[i]) return 1;
    return 0;
}

struct Line{
    vector < string > units;
    
    Line (string l = "") {
        units.clear();
        repe (i,l) {
            if (l[i] == ' ' || l[i] == ';') continue;
            char p = l[i];
            string sp; sp.push_back(p);
            if (i==0) units.push_back(sp);
            else if (l[i-1] == ' ') units.push_back(sp);
            else if (isQ(l[i]) || isQ(l[i-1])) units.push_back(sp);
            else units.back().push_back(p);
        }
    }
};

struct Code{
    vector < Line > lines;
    
    void scan() {
        lines.clear();
        int n; scanf(I,&n);
        rep (i,n) {
            string s = sc.nextLine();
            while (s=="") s=sc.nextLine();
            lines.push_back( Line(s) );
        }
    }
};

const int N = 10005;
vector < int > e[N];
int dp[N];
int cnt;
Code source;
map < string , int > mp;

int dfs(int u) {
    if (dp[u] != -1) return dp[u];
    int ans=0;
    repe (i,e[u]) {
        int v = e[u][i];
        if (v == u) throw (int)(-1);
        if (v >= u) throw (char)('a');
        ans += dfs(v);
    }   
    return ans;
}

void init() {
    int cn = (int)source.lines.size()+10;
    source.scan();
    //if (source.check()) { puts("Compile error"); return; }
    rep (i,cn) e[i].clear();
    cnt = 0;
    rep (i,cn) dp[i] = -1;
    mp.clear();
    string posDef;
    repi (i,2,(int)source.lines.size()-1) {
        vector < string > & pos= source.lines[i].units;
        if (isQ(pos[0][0])) continue;
        if (pos[0] == "__" || pos[0] == "printf") continue;
        if (pos[0] == "void" || pos[0] == "int") {
            if ( mp.count(pos[1]) ) { puts("Compile error"); return; }
            posDef = pos[1];
            mp[pos[1]] = cnt++;
        } else {
            //ses(posDef);see(pos[0]);
            if ( !mp.count(pos[0]) ) { puts("Compile error"); return; }
            e[ mp[posDef] ].push_back( mp[pos[0]] );
            //ses(mp[posDef]); see(mp[pos[0]]);
        }
    }
    dp[0] = 1;
    try {
        printf(IN,dfs(cnt-1));
    } catch (int u) {
        puts("Segmentation fault");
    } catch (char u) {
        puts("Compile error");
    }
}

void solve() {
    
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
#ifndef __LL
    freopen("program.in","r",stdin);
    freopen("program.out","w",stdout);
#endif
    int T; scanf(I,&T);
    while (T--) {
        init();
        solve();
    }
    return 0;
}
