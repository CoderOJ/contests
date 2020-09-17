#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a; 
    cin >> a;
    string s;
    int x;
    cin >> x;
    char rubbish;
    cin >> rubbish;
    int y;
    cin >> y;
    x = x * 100 + y;
    cout << a * x / 100 << endl; 
    return 0;
}
