#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    long long x = pow(10,n);
    cout << 50 << endl;
    for (int i=1;i<=50;i++){
	cout << i + 10000 - 50 << ' ';
    }
    cout << endl;
    cout << 50 << endl;
    for (int i=1;i<=50;i++){
	cout << 10000 << ' ';
    }
    cout << endl;
    for (int i=1;i<=50;i++){
	cout << x << ' ';
    }
    return 0;
}
