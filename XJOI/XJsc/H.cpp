#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
using namespace std;

#define long long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif

struct DisjointSet{
    static const int L = 1e5 + 5;
    int pt[L];

    DisjointSet(){
        for (int i=0;i<L;i++){
            pt[i] = i;
        }
    }

    int find(int x){
        if (pt[x] == x){
            return x;
        }
        return pt[x] = find(pt[x]);
    }

    void add(int a,int b){
        pt[find(b)] = find(a);
    }

    bool uni(int a,int b){
        return (find(a) == find(b));
    }
};

DisjointSet kd;

const int N = 55;
char mp[N][N];
int tot[N * N * 2];
int n;

const long MOD = 1e9 + 7;

long fact(int n){
    long res = 1;
    for (long i=3;i<=n;i++){
        res = (res * i) % MOD;
    }
    return res;
}

void init(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        for (int j=1;j<=i;j++){
            cin >> mp[i][j];
        }
    }
}

int _map(int a,int b){
    return a * N + b;
}

void uni(){
    for (int i=2;i<=n;i++){
        for (int j=1;j<i;j++){
            if (mp[i][j] == '.' && mp[i][j + 1] == '.'){
                if (mp[i - 1][j] == '.'){
                    //kd[i][j] = kd[i][j + 1] = kd[i - 1][j];
                    kd.add(_map(i,j),_map(i,j+1));
                    kd.add(_map(i,j),_map(i-1,j));
                }
                if (mp[i + 1][j + 1] == '.'){
                    //kd[i + 1][j + 1] = kd[i][j + 1] = kd[i][j];
                    kd.add(_map(i,j),_map(i + 1,j + 1));
                    kd.add(_map(i,j),_map(i,j + 1));
                }
            }
        }
    }
}

void count(){
    for (int i=1;i<=n;i++){
        for (int j=1;j<=i;j++){
            tot[kd.find(_map(i,j))]++;
        }
    }
}   

long solve(){
    long res = 1;
    for (int i=1;i<=_map(n,n);i++){
        res = (res * fact(tot[i])) % MOD;
    }
    return res;
}

int main(){
    init();
    uni();
    count();
    printf("%lld\n",solve());
    return 0;
}
