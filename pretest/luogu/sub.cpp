#include <string>
#include <iostream>
using namespace std;

int main() {
    string ans =
        "ABCBACABCBDBACD"
        "FTTTBA"
        "FTFTAA"
        "FFTTCC"
        "CDDAC"
        "CBDCB";
    int no;
    cin >> no;
    cout << ans[no - 1];
    return 0;
}
