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

#define long long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)

const int N = 105;
int n,x,y;
int a[N];
int le;

void init(){
    cin >> n >> x >> y;
    for (int i=1;i<=n;i++){
        cin >> a[i];
        if (a[i] <= x){
            le++;
        }
    }
}

int solve(){
    if (x > y){
        return n;
    }else{
        return (le + 1) / 2;
    }
}

int main(){
    init();
    cout << solve() << endl; 
    return 0;
}
