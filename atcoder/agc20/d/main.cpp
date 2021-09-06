#include "/home/jack/cm/debug"
#include <iostream>
using namespace std;

int main() {
    int T , A , B , C , D , k;
    for(cin >> T ; T ; T--) {
        cin >> A >> B >> C >> D;
        k = (A + B) / (min(A , B) + 1);
        int a , b;
        auto getAB = [&] (int p) {
            a = A - p / (k + 1) * k - p % (k + 1) , 
            b = B - p / (k + 1);
        };
        int l = 0 , r = A + B , mid;
        while(l < r) {
            mid = (l + r) >> 1;
            getAB(mid);
            if(b <= (long long)a * k) l = mid + 1;
            else r = mid;
        }
        see(l);
        getAB(l);
        r = l + 1 + b - a * k;
        see(r);
        for(int i = C ; i <= D ; ++i) {
            if(i <= l) {
                if(i % (k + 1) != 0) cout << 'A';
                else cout << 'B';
            } else {
                if((i - r) % (k + 1) != 0) cout << 'B';
                else cout << 'A';
            }
        }
        cout << endl;
    }
}

