#include <bits/stdc++.h>
#define int long long
using namespace std;

int getNum(int fst,int sub,int n){
	return fst + sub * (n - 1);
}

int getSum(int fst,int sub,int f,int t){
	int ff = getNum(fst,sub,f);
	int tt = getNum(fst,sub,t);
	return (ff + tt) * (t - f + 1) / 2;
}

#undef int
int main(){
#define int long long
	int A,B,n;
	scanf("%lld%lld%lld",&A,&B,&n);
	for (int i=1;i<=n;i++){
		int l,m,t;
		scanf("%lld%lld%lld",&l,&m,&t);
		if (getNum(A,B,l) > m){
			puts("-1");
			continue;
		}
		int left = l,right = (m - A) / B + 1;
		while (left < right){
			int mid = (left + right + 1) / 2;
			int sum = getSum(A,B,l,mid);
			//cout << left << ' ' << right << ' ' << mid << ' ' << sum << endl;
			if (sum <= t * m){
				left = mid;
			}else{
				right = mid - 1;
			}
			
		}
		cout << left << endl;
	}
	return 0;
}