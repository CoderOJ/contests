#include <bits/stdc++.h>
using namespace std;
 
int main(){
    srand(time(NULL));
    const int N = 10;
    int n = rand() % N + 1;
    int k = rand() % N + 1;
    int p = rand() % N + 1;
    printf("%d %d %d\n",n,k,p);
    for (int i=1;i<=n;i++){
        printf("%d ",rand() % 2);
    }
    puts("");
    for (int i=1;i<=p;i++){
        if (rand() % 2){
            putchar('!');
        }else{
            putchar('?');
        }
    }
    puts("");
    return 0;
}
