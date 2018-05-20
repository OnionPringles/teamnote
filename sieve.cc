
//compute sum of multiplicative function such as \sum_i=1^n phi(i)
//let f(n) = \sum_i=1^n phi(i), then one can easily show that
//f(n) = n*(n+1)/2 - \sum_{i=2}^n f(n/i)
//each f(n) can be computed in f(sqrtn) knowing f(n/i) values for all i
//precompute f(n) up to big M and do dp for the rest of f(n/i)
//code from GP of china computing sum i^k phi(i) for k=0,1,2
#include <stdio.h>
const int p = 1000000007;
#define mul(a,b) ((long long)(a)*(b)%p)
int sq(int n){
	int low=1,high=44722;
	while(low<high){
		int mid=(low+high)/2;
		if(mid*mid<=n)low=mid+1;
		else high=mid;
	}
	return low-1;
}
int sum1(int n){n=n%p;return mul(n,mul(n+1,(p+1)/2));}
int sum2(int n){n=n%p;return mul(n,mul(n+1,mul(2*n+1,(p+1)/6)));}
int sum3(int n){n=n%p;return mul(mul(mul(n,n),mul(n+1,n+1)),(p+1)/4);}
const int M=3000000;
const int M2 = 2000;
int chk[M],phi[M],a[M],b[M],c[M];
int dp[M2];
void g0(int m, int D){
	int s = sq(m);
	int ret = sum1(m);
	for(int d=2;m/d>s;d++){
		int md = m/d;
		if(md<M)ret-=a[md];
		else ret-=dp[D*d];
		if(ret<0)ret+=p;
	}
	for(int q=s;q>=1;q--){
		int L = m/(q+1)+1;
		int R = m/q;
		if(L>R)continue;
		else ret-=mul(R-L+1,a[q]);
		if(ret<0)ret+=p;
	}
	dp[D]=ret;
}
void g1(int m,int D){
	int s = sq(m);
	int ret = sum2(m);
	for(int d=2;m/d>s;d++){
		int md = m/d;
		if(md<M)ret-=mul(d,b[md]);
		else ret-=mul(d,dp[D*d]);
		if(ret<0)ret+=p;
	}
	for(int q=s;q>=1;q--){
		int L = m/(q+1)+1;
		int R = m/q;
		if(L>R)continue;
		int X = sum1(R)-sum1(L-1);
		if(X<0)X+=p;
		ret-=mul(X,b[q]);
		if(ret<0)ret+=p;
	}
	dp[D]=ret;
}
void g2(int m,int D){
	int s = sq(m);
	int ret = sum3(m);
	for(int d=2;m/d>s;d++){
		int md = m/d;
		if(md<M)ret-=mul(mul(d,d),c[md]);
		else ret-=mul(mul(d,d),dp[D*d]);
		if(ret<0)ret+=p;
	}
	for(int q=s;q>=1;q--){
		int L = m/(q+1)+1;
		int R = m/q;
		if(L>R)continue;
		int X = sum2(R)-sum2(L-1);
		if(X<0)X+=p;
		ret-=mul(X,c[q]);
		if(ret<0)ret+=p;
	}
	dp[D]=ret;
}
void preproc(){
	for(int i=1;i<M;i++)phi[i]=i;
	for(int i=2;i<M;i++){
		if(!chk[i]){
			phi[i]--;
			for(int j=i+i;j<M;j+=i){
				chk[j]=1;
				phi[j]=phi[j]/i*(i-1);
			}
		}
	}
	for(int i=1;i<M;i++){
		a[i]=a[i-1]+phi[i];
		if(a[i]>=p)a[i]-=p;
		b[i]=b[i-1]+mul(i,phi[i]);
		if(b[i]>=p)b[i]-=p;
		c[i]=c[i-1]+mul(mul(i,i),phi[i]);
		if(c[i]>=p)c[i]-=p;
	}
}
int main(){
	preproc();
	int n;
	while(scanf("%d",&n)==1){
		n--;int f1,f2;
		long long ans=0;
		
		for(int j=n/M;j;j--)g0(n/j,j);
		f1 = (n<M)?a[n]:dp[1];
		f2 = (n/2<M)?a[n/2]:dp[2];
		int X = sum1(n+1);
		X = mul(X,f1-f2);
		ans += X;
		
		for(int j=n/M;j;j--)g1(n/j,j);
		f1 = (n<M)?b[n]:dp[1];
		f2 = (n/2<M)?b[n/2]:dp[2];
		f1 = (f1-2LL*f2)%p;
		X = ((long long)n+1+(p+1)/2)%p;
		X = mul(X,f1);
		ans -= X;
		
		for(int j=n/M;j;j--)g2(n/j,j);
		f1 = (n<M)?c[n]:dp[1];
		f2 = (n/2<M)?c[n/2]:dp[2];
		f1 = (f1 - 4LL*f2)%p;
		X = (p+1)/2;
		X = mul(X,f1);
		ans += X;
		ans = (ans%p +p)%p;
		printf("%lld\n",ans*3%p);
	}
}