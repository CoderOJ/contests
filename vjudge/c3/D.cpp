#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

#define long long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)

const int N = 300005;
char a[N];
int len;
int mmoovvee[3];

void init(){
    cin >> len;
    cin >> a;
    for (int i=0;i<len;i++){
        a[i] -= '0';
    }
}

void makeMove(){
    mmoovvee[0] = mmoovvee[1] = mmoovvee[2] = -(len / 3);
    for (int i=0;i<len;i++){
        mmoovvee[(int)(a[i])]++;
    }
}

void replace(){
    for (int i=0;i<len;i++){
        if (a[i] == 2 && mmoovvee[2] > 0){
            if (mmoovvee[0] < 0){
                a[i] = 0;
                mmoovvee[2]--;
                mmoovvee[0]++;
            }else if (mmoovvee[1] < 0){
                a[i] = 1;
                mmoovvee[2] --;
                mmoovvee[1] ++;
            }
        }else if (a[i] == 1 && mmoovvee[1] > 0 && mmoovvee[0] < 0){
            a[i] = 0;
            mmoovvee[1]--;
            mmoovvee[0]++;
        }
    }
    for (int i=len - 1;i>=0;i--){
        if (a[i] == 0 && mmoovvee[0] > 0){
            if (mmoovvee[2] < 0){
                a[i] = 2;
                mmoovvee[2]++;
                mmoovvee[0]--;
            }else if(mmoovvee[1] < 0){
                a[i] = 1;
                mmoovvee[1]++;
                mmoovvee[0]--;
            }
        }else if (a[i] == 1 && mmoovvee[1] > 0 && mmoovvee[2] < 0){
            a[i] = 2;
            mmoovvee[2] ++;
            mmoovvee[1] --;
        }
    }
}

void put(){
    for (int i=0;i<len;i++){
        cout << (int)a[i];
    }
    puts("");
}

int main(){
    init();
    makeMove();
    replace();
    put();
    return 0;
}
