void calcLCP(int* str,int* SA,int* LCP,int* rnk,int n) {
	for (int i=0;i<n;i++) rnk[SA[i]]=i;
	int k = 0;
	for (int i=0;i<n;i++) {
		if (rnk[i] == n-1) {
			k=0; continue;
		}
		int j = SA[rnk[i]+1];
		while(i+k<n&&j+k<n&&str[i+k]==str[j+k])k++;
		LCP[rnk[i]] = k;
		if (k)k--;
	}
}