
//use round(x) not (int)x for cast
typedef complex<double> cpx;
void FFT(cpx a[],int lg,bool inv=false){
	int n=1<<lg;cpx w;
	if(!inv)w=exp(cpx(0,2*acos(-1)/n));
	else w=exp(cpx(0,-2*acos(-1)/n));
	for (int i=1,j=0,k;i<n;i++){
		for(k=n>>1; j>=k;k>>=1)j-=k;j+=k;
		if(i<j)swap(a[i],a[j]);
	}
	for (int i=0;i<lg;i++) {
		int s=1<<i;
		cpx ww=w;
		for (int j=1; j<lg-i; j++)ww=ww*ww;
		for (int j=0;j<n;j+=(s<<1)){
			cpx w=1.0;
			for (int k=j;k<s+j;k++) {
				cpx x=a[k];
				a[k]+=w*a[s+k];
				a[s+k]=x-w*a[s+k];
				w*=ww;
			}
		}
	}
	if(inv)for(int i=0;i<n;i++)a[i]/=n;
}