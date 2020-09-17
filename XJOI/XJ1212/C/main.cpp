#include <bits/stdc++.h>
using namespace std;
const int ans[35] = {1,2,3,7,8,9,13,14,15,21,25,37,45,51,165,211,224,476,584,1112,1364,2234,2342,2564,4436,5144,6554,8534,10664,12452,18710,19802,23924,44828,500001};

int main(){
    int r;scanf("%d",&r);
    cout << lower_bound(ans,ans + 35,r) - ans << endl;
    return 0;
}
