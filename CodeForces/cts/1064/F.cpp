#include <bits/stdc++.h>
using namespace std;
#define int long long

void checkMax(int& a,int b){
    a = max(a,b);
}

const int O = 0;

#undef int
int main(){
#define int long long

    int n,l,r,k;
    cin >> n >> l >> r >> k;
    int more = (r - l + n) % n + 1;
    int rest = n - more;
    if (more > k){
	puts("-1");
	return 0;
    }
    int ans = -1;
    if (n <= O){
	//O(n^2)
	for (int i=0;i<=more;i++){
	    for (int j=0;j<=rest;j++){
		cout << i << ' ' << j << endl;
		if ((k - more - i) % (n + i + j) == 0){
		    checkMax(ans,i + j);
		}
	    }
	}
    }else{
	//O(k/n)
	if (more * 2 >= k){
	    int doub = ceil(k / 2.0);
	    cout << doub + rest << endl;
	    return 0;
	}

	for (int t=1;k>=n * t + more;t++){
	    cout << t << ' ' << k << ' ' << n * t + more << endl;
	    int tmp = k - n * t - more;
	    int x = tmp % t;
	    int y = (tmp - x * (t + 1)) / t;
	    if (x <= more && y >= 0  && y <= rest){
		checkMax(ans,x + y);
	    }
	}
    }
    k++;
    if (n <= O){
	//O(n^2)
	for (int i=1;i<=more;i++){
	    for (int j=0;j<=rest;j++){
		cout << i << ' ' << j << endl;
		if ((k - more - i) % (n + i + j) == 0){
		    checkMax(ans,i + j);
		}
	    }
	}
    }else{
	//O(k/n)
	for (int t=1;k>=n * t + more;t++){
	    int tmp = k - n * t - more;
	    int x = tmp % t;
	    if (x == 0){
		x += t;
	    }
	    int y = (tmp - x * (t + 1)) / t;
	    if (x <= more && y >= 0  && y <= rest){
		checkMax(ans,x + y);
	    }
	}
    }
    cout << ans << endl;
    return 0;
}
