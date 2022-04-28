

#include<bits/stdc++.h>
char ibuf[1<<24],*ih=ibuf,obuf[1<<23],*oh=obuf;
inline void read(int&x){
	for(;!isdigit(*ih);++ih);
	for(x=0;isdigit(*ih);x=x*10+*ih++-48);
}
inline void out(int x){
	if(!x){*oh++='0';return;}
	static int buf[30];int xb=0;
	for(;x;x/=10)buf[++xb]=x%10;
	for(;xb;)*oh++=buf[xb--]|48;
}
const int N=5e5+5;
int n,m,ty,la,o,l,r,x,i,val[N];
struct node{
	int l,r,cov,su;
}t[N*130];
int rt[N],tcnt;
void mdy(int x,int&y,int l,int r,int al,int ar,int v){
	y=++tcnt;if(al<=l && r<=ar){t[y].cov=v;t[y].su=(r-l+1)*val[v];return;}
	int m=(l+r)>>1;
	if(t[x].cov){
		t[++tcnt]=t[t[x].l];t[x].l=tcnt;t[++tcnt]=t[t[x].r];t[x].r=tcnt;
		t[t[x].l].cov=t[t[x].r].cov=t[x].cov;
		t[t[x].l].su=(m-l+1)*val[t[x].cov];t[t[x].r].su=(r-m)*val[t[x].cov];
		t[x].cov=0;
	}t[y]=t[x];
	if(al<=m)mdy(t[x].l,t[y].l,l,m,al,ar,v);
	if(ar>m)mdy(t[x].r,t[y].r,m+1,r,al,ar,v);t[y].su=t[t[y].l].su+t[t[y].r].su;
}
int ask(int x,int l,int r,int k){
	if(l==r || t[x].cov)return t[x].cov;
	int m=(l+r)>>1;return k<=m?ask(t[x].l,l,m,k):ask(t[x].r,m+1,r,k);
}
int query(int x,int l,int r,int al,int ar){
	if(l==al && r==ar)return t[x].su;
	if(t[x].cov)return (ar-al+1)*val[t[x].cov];
	int m=(l+r)>>1;
	if(ar<=m)return query(t[x].l,l,m,al,ar);
		else if(al>m)return query(t[x].r,m+1,r,al,ar);
				else return query(t[x].l,l,m,al,m)+query(t[x].r,m+1,r,m+1,ar);
}
int main(){
	fread(ibuf,1,1<<24,stdin);
	read(n);read(m);read(ty);
	for(i=1;i<=m;++i){
		read(o);read(l);l=(l+ty*la)%n+1;rt[i]=rt[i-1];
		if(o&1){read(r),r=(r+ty*la)%n+1;if(l>r)std::swap(l,r);}
		if(o==1)out(la=query(rt[i],1,n,l,r)),*oh++='\n';
		if(o==2){
			x=ask(rt[i-1],1,n,l);if(!x)continue;
			x=ask(rt[x-1],1,n,l);mdy(rt[i],rt[i],1,n,l,l,x);
		}
		if(o==3)read(x),val[i]=x,mdy(rt[i],rt[i],1,n,l,r,i);
	}
	fwrite(obuf,1,oh-obuf,stdout);
	return 0;
}

