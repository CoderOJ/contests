#include <bits/stdc++.h>
using namespace std;

#define MOD 998244353

class Map{
private:
    static const long long N = 115;
    long long e[N][N];

public:
    Map (long long n = 0){
        memset(e,0,sizeof(e));
        for (long long i=0;i<N;i++){
            e[i][i] = n;
        }
    }
    
    long long iNod(long long a,long long b){
        return a * 10 + b;
    }
    
    void add(long long a,long long b,long long x,long long y){
        e[iNod(a,b)][iNod(x,y)] = 1;
    }

    long long get(long long a,long long b,long long x,long long y){
        return e[iNod(a,b)][iNod(x,y)];
    }

    Map plus (Map& B){
        Map C;
        for (long long i=0;i<N;i++){
            for (long long j=0;j<N;j++){
                for (long long k=0;k<N;k++){
                    (C.e[i][j] += e[i][k] * B.e[k][j]) %= MOD;
                }
            }
        }
        return C;
    }

    Map power (long long a){
        Map res(1),A = *this;
        while (a){
            if (a & 1){
                res = res.plus(A);
            }
            A = A.plus(A);
            a >>= 1;
        }
        return res;
    }
}
