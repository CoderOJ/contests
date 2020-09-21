#ifndef _LIB_SCANNER
#define _LIB_SCANNER 1

#include <stdio.h>

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

#undef getChar
};
Scanner sc;
#endif /* _LIB_SCANNER */
#include <set>
using namespace std; 

#define int long long
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)

void preInit();
void init(); 
void solve(); 

__int32_t main(){ 
preInit();
init(); solve(); 
    return 0;
}


// my code begins here


const int N = 500005;
int a[N];
int n,m,q;

void preInit() {
    n = sc.nextInt(); m = sc.nextInt(); q = sc.nextInt();
    rep (i,n) a[i] = sc.nextInt();
}

int sum = 0;
multiset <int> st;

void init() {
    rep (i,n) { sum += a[i]; st.insert(a[i]); }
}

void output() {
    printf("%lld\n", max( (sum-1)/m+1 , *st.rbegin() ));
}

void solve() {
    output();
    rep (i,q) {
        int w = sc.nextInt()-1, t = sc.nextInt();
        sum -= a[w]; st.erase(st.find(a[w]));
        a[w] = t;
        sum += a[w]; st.insert(a[w]);
        output(); }
}
