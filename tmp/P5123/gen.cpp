#include <bits/stdc++.h>
using namespace std;
int cnt = 0;
int main(){
    int n = 50000;
    printf("%d\n", n);
    for (register int i = 1;i <= n;i ++){
        for (register int j = 1;j <= 5;j ++) printf("%d ", ++ cnt);
        putchar(10);
    }
}
