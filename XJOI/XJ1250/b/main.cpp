#include <bits/stdc++.h>
using namespace std;
const int N = 51;
int A[N], Random[N], id, n;
int qsort(int L, int R) {
	if (L >= R) return 0;
	int i = L, j = R;
	int x = Random[++id]; 
	int x0 = A[x];
	if (!(L <= x && x <= R)) throw (int)(-1);
    //assert(L <= x && x <= R);
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

int ans[N];
int tt[N];

bool jury1() {
    for (int i=1;i<=n;i++) if (Random[i] != i) return 0;
    return 1;
}

bool jury2() {
    for (int i=1;i<=n;i++) if (Random[i] != Random[1]) return 0;
    return 1;
}

void subtask() {
    if (jury1() || jury2()) {
        puts("Solution exists");
        printf("%d\n",n * (n-1) / 2);
        for (int i=1;i<=n;i++)  printf("%d ",i);
        puts("");
        exit(0);
    }
}

int main(){
	// read n and Random_1..n and A_1..n
    srand(19260817);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&Random[i]); 
    for (int i=1;i<=n;i++) A[i] = i;
	int tot=0;
    subtask();
    while( (clock())*1000.0/CLOCKS_PER_SEC < 900) {
        random_shuffle(A + 1,A+n+1);
        for (int i=1;i<=n;i++) tt[i] = A[i];
        //next_permutation(A+1,A+n+1);
        id=0;
        try {
            int t = qsort(1,n);
            if (t > tot) {
                tot = t;
                for (int i=1;i<=n;i++) ans[i] = tt[i];
            }
        } catch (int u) {}
    }
    if (tot == 0) {
        puts("No solution");
        return 0;
    }else {
        puts("Solution exists");
    }
	cout << tot << endl;
    for (int i=1;i<=n;i++) printf("%d ",ans[i]);
    puts("");
    return 0;
}
