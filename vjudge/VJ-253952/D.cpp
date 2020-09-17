#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

class Scanner{
private:
    istream& ist;

public:
    Scanner(istream& in):ist(in){}

    string next(){
        string r;
        ist >> r;
        return r;
    }

    string nextLine(){
        string r;
        getline(ist,r);
        return r;
    }

    int nextInt(){
        int r;
        ist >> r;
        return r;
    }

    double nextDouble(){
        double r;
        ist >> r;
        return r;
    }
};

const int N = 500005;
int a[N];

int main(){
    Scanner sc(cin);
    int n = sc.nextInt();
    int att = sc.nextInt(),heal = sc.nextInt();
    int h1 = sc.nextInt(),h2 = sc.nextInt();
    int atn = 0;
    int matn = 0;
    priority_queue < int >  dam;
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        atn++;
        h1 -= a[i];
        matn = max(atn,matn);
        if (atn * att >= h2){
            cout << "Win" << endl << i << endl;
            return 0;
        }
        dam.push(max(a[i],heal));
        while (h1 <= 0 && !dam.empty()){
            int tmp = dam.top();
            h1 += tmp;
            atn--;
            dam.pop();
        }
    }
    cout << "Lose" << endl << matn * att << endl;
    return 0;
}
