#include <bits/stdc++.h>
using namespace std;
const int N = 51;
int A[N], Random[N], id, n;
int qsort(int L, int R) {
	if (L >= R) return 0;
	int i = L, j = R;
	int x = Random[++id]; 
	int x0 = A[x];
	assert(L <= x && x <= R);
	while (i < j) {
		while (A[i] < A[x]) i++;
		while (A[j] > A[x]) j--;
		if (i <= j) {
			if (i == x) x = j;
			else if (j == x) x = i;
			swap(A[i], A[j]);
			i++; j--;
		}
	}
	swap(A[x], A[x0]);
	return R - L + qsort(L, x0 - 1) + qsort(x0 + 1, R);
}
int main(){
	// read n and Random_1..n and A_1..n
	int tot = qsort(1, n);
	cout << tot << endl;
}
