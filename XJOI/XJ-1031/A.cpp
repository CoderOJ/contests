#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int a[N];
int tmp[N];
map < int , int > mp;

int main(){
    int n;
    a[0] = -1;
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
	scanf("%d",a + i);
	tmp[i] = a[i];
    }
    sort (a + 1,a + n + 1);
    int lst;
    for (int i=1;i<=n;i++){
	if (a[i] != a[i-1]){
	    lst = i;
	}
	mp[a[i]] = lst;
    }
    for (int i=1;i<=n;i++){
	cout << mp[tmp[i]] << ' ';
    }
    cout << endl;
    return 0;
}
