#include <bits/stdc++.h>
using namespace std;
#define int long long
const int M = 51;
string s[M];
bool book[M];
#undef int
int main(){
#define int long long
    int n,m;
    cin >> n >> m;
    long long ans = (long long)pow(10LL,n);
    for (int i=1;i<=m;i++){
	cin >> s[i];
    }
    for (int i=1;i<=m;i++){
	for (int j=1;j<=m;j++){
	    if (i != j && s[i].length() <= s[j].length()){
		bool flag = 0;
		for (int k=0;k<(int)s[i].length();k++){
		    if (s[i][k] != s[j][k]){
			flag = 1;
			break;
		    }
		}
		if (!flag){
		    book[j] = 1;
		}
	    }
	}
    }
    for (int i=1;i<=m;i++){
	if (book[i] == 0){
	    ans -= (long long)pow(10LL,n - s[i].length());
	}
    }
    cout << ans << endl;
    return 0;
}
