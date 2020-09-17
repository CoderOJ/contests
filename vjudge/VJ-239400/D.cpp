#include <bits/stdc++.h>
using namespace std;
 
const int N = 100005;
const int M = 30;
char a[N];
char b[N];
int ta[M];
int tb[M];
int ma[M];
int mb[M];
int afta[N][M];
 
void makeTon(int len){
    for (int i=0;i<len;i++){
        ta[a[i] - 'A'] ++;
        tb[b[i] - 'A'] ++;
    }
}
 
void makeMore(){
    for (int i=0;i<26;i++){
        if (ta[i] > tb[i]){
            ma[i] += ta[i] - tb[i];
        }
        if (ta[i] < tb[i]){
            mb[i] += tb[i] - ta[i];
        }
    }
}

void makeAfter(int len){
    for (int i=len-1;i>=0;i--){
        for (int j=0;j<26;j++){
            if (a[i] == j + 'A'){
                afta[i][j] = afta[i + 1][j] + 1;
            }else{
                afta[i][j] = afta[i + 1][j];
            }
        }
    }
}
 
int change(int len){
    int ans = 0;
    for (int i=0;i<len;i++){
        if (ma[a[i] - 'A'] == 0){
            continue;
        }
        for (int j=0;j<26;j++){
            char chg = j + 'A';
            if (mb[j]){
                if (chg < a[i]){
                    int co = a[i];
                    a[i] = chg;
                    ma[co - 'A']--;
                    mb[j]--;
                    ans++;
                    break;
                }else{
                    if (afta[i+1][a[i] - 'A'] >= ma[a[i] - 'A']){
                        break;
                    }else{
                        int co = a[i];
                        a[i] = chg;
                        ma[co - 'A']--;
                        mb[j]--;
                        ans++;
                        break;
                    }
                }
            }
        }
    }
    return ans;
}
 
int main(){
//  FILE* in,out;
//  in.open("input.txt","r");
//  out.open("output.txt","w");
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%s%s",a,b);
    int len = strlen(a);
    makeTon(len);
    makeMore();
    makeAfter(len);
    int ans = change(len);
    printf("%d\n",ans);
    printf("%s\n",a);
//  in.close();
//  out.close();
    return 0;
}
