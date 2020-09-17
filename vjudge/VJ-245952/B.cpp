#include <bits/stdc++.h>
using namespace std;

const int N = 500005;
int p[N];
int h[N];

int main(){
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d%d",p+i,h+i);
    }
    p[n+1] = 0x7fffffff;
    cout << p[n]<< endl << p[n+1] << endl;
    int ans = 0;
    int pos = -0x3f3f3f3f;
    for (int i=1;i<=n;i++){
        cout << ans << ' ' << pos << endl;
        if (p[i]-h[i] > pos){
            ans++;
            pos = p[i];
        }else if (p[i] + h[i] < p[i+1]){
            ans++;
            pos = p[i] + h[i];
        }else{
            pos = p[i];
        }
    }
    cout << ans << endl;
    return 0;
}
