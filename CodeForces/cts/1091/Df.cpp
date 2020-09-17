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

int a[100];

int main(){
    int n;
    cin >> n;
    for (int i=1;i<=n;i++){
        a[i] = i;   
    }
    vector < int > ans;
    do{
        for (int i=1;i<=n;i++){
            ans.push_back(a[i]);
        }
    }while(next_permutation(a + 1,a + n + 1));
    vector < vector < int > > tt;
    for (int i=0;i<=(int)ans.size() - n;i++){
        int sum = 0;
        for (int j=0;j<n;j++){
            sum += ans[i + j];
        }
        if (sum == n * (n + 1) / 2){
            vector < int > t;
            t.push_back(i % n);
            for (int j=0;j<n;j++){
                //cout << ans[i + j] << ' ';
                t.push_back(ans[i + j]);
            }
            tt.push_back(t);
        }
    }
    sort(tt.begin(),tt.end());
    for (int i=0;i<(int)tt.size();i++){
        foreach(j,tt[i]){
            cout << tt[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
