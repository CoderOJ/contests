#include <stdio.h>
#define il inline
using namespace std;

il char gc()
{
    static char now[1<<20],*S,*T;
    if (T==S)
    {
        T=(S=now)+fread(now,1,1<<20,stdin);
        if (T==S) return EOF;
    }
    return *S++;
}//getchar
 
il int read()
{
    int res=0,sign=1;
    char c;
    while ((c=gc())<'0'||c>'9') if (c=='-') sign=-1;
    res=(c^48);
    while ((c=gc())>='0'&&c<='9') res=(res<<3)+(res<<1)+(c^48);
    return res*sign;
}//read a signed interger

int main()
{
	int n;
	n=read(),printf("%d",n);//example 
	
	return 0;
}
