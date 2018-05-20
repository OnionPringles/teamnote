
//robust to p+p overflow
//15*(1<<27)+1, 7*(1<<26)+1, 5*(1<<25)+1
//w is an element with order 1<<LG
int LG,w,wi;int p=()*(1<<LG)+1;
void FFT(int a[],int lg,bool inv=false){
	int n=1<<lg,E= (1<<LG)/n,w=::w;
	if(inv)w=winv;
	while(E>1)w=mul(w,w),E=E>>1;
	for (int i=1, j=0,k; i<n; i++) {
		for (k=n>>1;j>=k;k>>=1)j-=k;j+=k;
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
		for (int j=1;j<lg-i;j++)ww=mul(ww,ww);
		for (int j=0; j<n; j+=(s<<1)) {
			int w = 1;
			for (int k=j; k<s+j; k++) {
				int x=a[k];
				a[k]-=p-mul(w,a[s+k]);
				if(a[k]<0)a[k]+=p;
				a[s+k] = x - mul(w,a[s+k]);
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