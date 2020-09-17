#include <bits/stdc++.h>
using namespace std;
#define taste first
#define type second

const int n = 100;
pair < int , int > thn[n];
bool use[n];

int main(){
    int n;
    cin >> n;
    for (int i=1;i<=n;i++){
	cin >> thn[i].type;
    }
    for (int i=1;i<=n;i++){
	cin >> thn[i].taste;
    }
    sort (thn + 1,thn + n + 1);
    int idx = 0;
    while (thn[++idx].taste < 0){};
    int stype = 0,staste = 0;
    for (int i=idx;i<=n;i++){
	stype += !use[thn[i].type];
	use[thn[i].type] = 1;
	staste += thn[i].taste;
	// cout << i << ' ' << stype << ' ' << staste << endl;
    }
    for (int i=idx - 1;i>=1;i--){
	if (!use[thn[i].type]){
	    int flash = (stype + 1) * (staste + thn[i].taste);
	    if (flash > stype * staste){
		stype++;
		staste += thn[i].taste;
		use[thn[i].type] = 1;
	    }
	}
	// cout << i << ' ' << stype << ' ' << staste << endl;
    }
    cout << stype * staste << endl;
    return 0;
}
