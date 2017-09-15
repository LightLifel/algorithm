#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fod(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=1e5+10;
struct Node{int l,r,v,s,w,rnd;}tr[N];
int n,root,ans,size;
void update(int k){tr[k].s=tr[tr[k].l].s+tr[tr[k].r].s+tr[k].w;}
void rturn(int &k)
{
	int t=tr[k].l;tr[k].l=tr[t].r;tr[t].r=k;
	tr[t].s=tr[k].s;update(k);k=t;
}
void lturn(int &k)
{
	int t=tr[k].r;tr[k].r=tr[t].l;tr[t].l=k;
	tr[t].s=tr[k].s;update(k);k=t;
}
void insert(int &k,int x)
{
	if(k==0) {k=++size; tr[k].w=tr[k].s=1;tr[k].v=x;tr[k].rnd=rand();return ;}
	tr[k].s++;
	if(tr[k].v==x) tr[k].w++; 
	else if(tr[k].v<x) {
		insert(tr[k].r,x);
		if(tr[tr[k].r].rnd<tr[k].rnd) lturn(k);
	}else{
		insert(tr[k].l,x);
		if(tr[tr[k].l].rnd<tr[k].rnd) rturn(k);
	}
}
void del(int &k,int x)
{
	if(k==0) return ;
	if(tr[k].v==x) {
		if(tr[k].w>1) {tr[k].w--;tr[k].s--;return ;}
		if(tr[k].l*tr[k].r==0) k=tr[k].l+tr[k].r;
		else if(tr[tr[k].l].rnd<tr[tr[k].r].rnd) 
			rturn(k),del(k,x);
		else lturn(k),del(k,x);
	}else if(x>tr[k].v) 
		tr[k].s--,del(tr[k].r,x);
	else  tr[k].s--,del(tr[k].l,x);	
}
int query_rank(int k,int x)
{
	if(k==0) return 0;
	if(tr[k].v==x) return tr[tr[k].l].s+1;
	else if(x>tr[k].v) return tr[tr[k].l].s+tr[k].w+query_rank(tr[k].r,x);
		else return query_rank(tr[k].l,x);
}
int query_num(int k,int x)
{
	if(k==0) return 0;
	if(x<=tr[tr[k].l].s) return query_num(tr[k].l,x);
	else if(x>tr[tr[k].l].s+tr[k].w) return query_num(tr[k].r,x-tr[tr[k].l].s-tr[k].w);
	else return tr[k].v;
}
void query_pro(int k,int x)
{
	if(k==0) return ;
	if(tr[k].v<x) ans=k,query_pro(tr[k].r,x);
	else query_pro(tr[k].l,x);
}
void query_sub(int k,int x)
{
	if(k==0) return ;
	if(tr[k].v>x) ans=k,query_sub(tr[k].l,x);
	else query_sub(tr[k].r,x); 
}
int main()
{
	scanf("%d",&n);
	for(int op,x,i=1;i<=n;i++) {
		scanf("%d%d",&op,&x);	
		switch(op){
		case 1:insert(root,x);break;
		case 2:del(root,x);break;
		case 3:printf("%d\n",query_rank(root,x));break;
		case 4:printf("%d\n",query_num(root,x));break;
		case 5:ans=0;query_pro(root,x);printf("%d\n",tr[ans].v);break;
		case 6:ans=0;query_sub(root,x);printf("%d\n",tr[ans].v);break;
		}
	}
}
