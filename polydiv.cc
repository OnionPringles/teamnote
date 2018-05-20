
//Divide f by g, f=gq+r
//Assume the highest coefficient of g is 1
//Rev(f)=Rev(q)Rev(g) mod(x^{deg(f)-deg(g)})
//To solve g^-1 mod x^M, where g_0=1, iterate g=g(2-fg)
//good to keep FFT(Rev(g)) and FFT(Rev(g)^-1modx^big)
//then compute Rev(q) then Rev(g)Rev(q)
//the following code is for rng problem of boj
//input: k,m,c_1,...,c_k meaning
//a_n=sum c_ia_{n-i} solving for a_m
#include <stdio.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define mul(a,b) ((long long)(a)*(b)%p)
const int LG=22;
const int p=25*(1<<LG)+1;
int w,winv;
int modpow(int n,int e){
	if(!e)return 1;
	int t=modpow(n,e/2);
	t=mul(t,t);
	if(e&1)t=mul(t,n);
	return t;
}
int modinv(int n){
	if(n==1)return 1;
	else return mul(p-p/n,modinv(p%n));
}
void FFT(int a[],int lg,bool inv=false){
	int n=1<<lg,E= (1<<LG)/n,w=::w;
	if(inv)w=winv;
	while(E>1)w=mul(w,w),E=E>>1;
	for (int i=1, j=0,k; i<n; i++) {
		for (k = n>>1; j>=k; k>>=1) j-=k;
		j+=k;
		if (i<j) swap(a[i],a[j]);
	}
	for(int j=0;j<n;j+=2){
		int x=a[j];
		a[j] -= p-a[j+1];
		if(a[j]<0)a[j]+=p;
		a[j+1]=x-a[j+1];
		if(a[j+1]<0)a[j+1]+=p;
	}
	for (int i = 1; i<lg; i++) {
		int s = 1 << i;
		int ww = w;
		for (int j = 1; j<lg - i; j++)ww = mul(ww,ww);
		for (int j = 0; j<n; j += (s << 1)) {
			int w = 1;
			for (int k = j; k<s+j; k++) {
				int x = a[k];
				a[k] -= p-mul(w,a[s + k]);
				if(a[k]<0)a[k]+=p;
				a[s + k] = x - mul(w,a[s + k]);
				if(a[s+k]<0)a[s+k]+=p;
				w = mul(w,ww);
			}
		}
	}
	if(inv){
		int j=p-(p-1)/n;
		for(int i=0;i<n;i++)a[i]=mul(a[i],j);
	}
}
const int SZ = 16;
const int B=1<<SZ;
int u[B],t[B];
int divset(const int g[]){//g[0] must be 1
	u[0]=1;
	for(int i=2;i<=SZ;i++){
		const int m=1<<i;
		for(int j=0;j<m>>1;j++)t[j]=g[j];
		FFT(t,i);FFT(u,i);
		for(int j=0;j<m;j++)t[j]=mul(t[j],u[j]);
		FFT(t,i,true);
		t[0]=(t[0]>2)?p+2-t[0]:2-t[0];
		for(int j=1;j<m>>1;j++)t[j]=t[j]?p-t[j]:0;
		for(int j=m>>1;j<m;j++)t[j]=0;
		FFT(t,i);
		for(int j=0;j<m;j++)u[j]=mul(u[j],t[j]);
		FFT(u,i,true);
		for(int j=m>>1;j<m;j++)u[j]=0;
	}
}
int A[300000],C[300000];
int g[B],r[B],n;
void solve(long long E){
	if(!E){
		r[0]=1;return;
	}
	solve(E/2);
	FFT(r,SZ);
	for(int i=0;i<B;i++)r[i]=mul(r[i],r[i]);
	FFT(r,SZ,true);
	int df;
	for(df=B-1;df>=0;df--)if(r[df])break;    
	int m=df-n+1;
    if(m<=0)goto done;
	for(int i=0;i<m;i++)t[i]=r[df-i];
	for(int i=m;i<B;i++)t[i]=0;
	FFT(t,SZ);
	for(int i=0;i<B;i++)t[i]=mul(t[i],u[i]);
	FFT(t,SZ,true);
	for(int i=m;i<B;i++)t[i]=0;
	FFT(t,SZ);
	for(int i=0;i<B;i++)t[i]=mul(t[i],g[i]);
	FFT(t,SZ,true);
	for(int i=0;i<=df;i++){
		r[i] -= t[df-i];
		if(r[i]<0)r[i]+=p;
	}
	for(int i=n;i<B;i++)assert(r[i]==0);
	//for(int i=n;i<B;i++)r[i]=0;
done:
	if(E&1){
		int cf=r[n-1];
		for(int i=n-1;i;i--)r[i]=r[i-1];r[0]=0;
		for(int i=0;i<n;i++){
			r[i]+=mul(C[n-1-i],cf);
			if(r[i]>=p)r[i]-=p;
		}
	}
}
int main(){
	for(w=2;;w++){
		int x=modpow(w,(p-1)/2);
		if(x==1)continue;
		x=modpow(w,(p-1)/5);
		if(x==1)continue;
		break;
	}
	w=modpow(w,25);
	winv=modinv(w);
	long long k;
	scanf("%d%lld",&n,&k);k--;
	for(int i=0;i<n;i++)scanf("%d",A+i);
	for(int i=0;i<n;i++)scanf("%d",C+i);
	for(int i=0;i<n;i++)g[i]=(C[n-1-i]==0)?0:(p-C[n-1-i]);
	g[n]=1;
	reverse(g,g+n+1);
	divset(g);
	FFT(u,SZ); FFT(g,SZ);
	solve(k);
	int ans=0;
	for(int i=0;i<n;i++){
		ans += mul(r[i],A[i]);
		if(ans>=p)ans-=p;
	}
	printf("%d\n",ans);
}