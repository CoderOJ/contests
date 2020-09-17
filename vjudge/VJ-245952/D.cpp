#include <bits/stdc++.h>
using namespace std;

const int N = 10000005;
int isPrime[N];
int cnt[N];
int ans[N];

void initPrime(){
	fill(isPrime,isPrime+N,1);
	for (int i=2;i*i<=N;i++){
		if (isPrime[i]){
			for (int j=i * i;j<=N;j+=i){
				isPrime[j] = 0;
			}
		}
//		cout << i << endl;
	}
}

void initAns(){
	for (int i=2;i<=N;i++){
		ans[i] = ans[i-1];
		if (isPrime[i]){
			for (int j=1;i * j <= N;j++){
				ans[i] += cnt[i * j];
			}
		}
	}
}

int main(){
	initPrime();
	//puts("pass");
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int read;
		scanf("%d",&read);
		cnt[read]++;
	}
	initAns();
	int m;
	scanf("%d",&m);
	for (int i=1;i<=m;i++){
		int f,t;
		scanf("%d%d",&f,&t);
		f = min(f,N);
		t = min(t,N);
		printf("%d\n",ans[t] - ans[f - 1]);
	}
	return 0;
}