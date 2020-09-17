#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
char a[N];
char mka[N];
char mkb[N];
char ans1[N];
char ans2[N];

int _div (int a,int b){
    if (a % b == 0){
        return a / b;
    }else{
        return a / b + 1;
    }
}

void makeTot(int& na,int& nb,int len){
    for (int i=0;i<len;i++){
        if (a[i] == 'a'){
            na ++ ;
        }else{
            nb ++ ;
        }
    }
}

int makeChar(char x[],int n,int loop,char ful){
    int idx = 0;
    int res = 0;
    for (int i=0;i<n;i++){
        if (i != 0 && i % loop == 0){
            x[idx++] = '*';
            res++;
        }
        x[idx++] = ful;
    }
    x[idx] = '\0';
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int x,y;
        scanf("%s",a);
        scanf("%d%d",&x,&y);
        int na = 0;
        int nb = 0;
        int len = strlen(a);
        makeTot(na,nb,len);
        int bka = _div(na,x) - 1;
        int bkb = _div(nb,y) - 1;
        int len1 = 0x3f3f3f3f;
        int len2 = 0x3f3f3f3f;
        if (nb == 0){
            makeChar(ans1,na,x,'a');
            puts(ans1);
            continue;
        }
        if (na == 0){
            makeChar(ans2,nb,y,'b');
            puts(ans2);
            continue;
        }
        if (bka <= nb){
            int more = nb - bka;
            int idx = 0;
            for (int i=0;i<bka;i++){
                for (int j=0;j<x;j++){
                    ans1[idx++] = 'a';
                }
                int loop = min(y - 1,more);
                for (int j=0;j<=loop;j++){
                    ans1[idx++] = 'b';
                }
                more -= loop;
            }
            int left = na - bka * x;
            for (int i=0;i<left;i++){
                ans1[idx++] = 'a';
            }
            len1 = makeChar(&ans1[idx],more,y,'b');
        }else{
            int idx = 0;
            int more = na;
            for (int i=0;i<nb;i++){
                for (int j=0;j<x;j++){
                    ans1[idx++] = 'a';
                    more--;
                }
                ans1[idx++] = 'b';
            }
            len1 = makeChar(&ans1[idx],more,x,'a');
        }
        if (bkb <= na){
            int more = na - bkb;
            int idx = 0;
            for (int i=0;i<bkb;i++){
                for (int j=0;j<y;j++){
                    ans2[idx++] = 'b';
                }
                int loop = min(x - 1,more);
                for (int j=0;j<=loop;j++){
                    ans2[idx++] = 'a';
                }
                more -= loop ;
            }
            int left = nb - bkb * y;
            for (int i=0;i<left;i++){
                ans2[idx++] = 'b';
            }
            len2 = makeChar(&ans2[idx],more,x,'a');
        }else{
            int idx = 0;
            int more = nb;
            for (int i=0;i<na;i++){
                for (int j=0;j<y;j++){
                    ans2[idx++] = 'b';
                    more--;
                }
                ans2[idx++] = 'a';
            }
            len2 = makeChar(&ans2[idx],more,y,'b');
        }
        //puts(ans1);
        //puts(ans2);
        if (len1 < len2){
            puts(ans1);
        }else{
            puts(ans2);
        }
    }
    return 0;
}
