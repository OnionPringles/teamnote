
void Manacher(T str[],int res[],int n){
	int r=0,c=-1;
	for(int i=0,j,k;i<n;i++){
		res[i]=i<r?min(res[c+c-i],r-i):1;
		for(j=i+res[i],k=i-res[i];j<n&&k>=0&&str[j]==str[k];j++,k--);
		res[i]=j-i;
		if(j>r+1)r=j-1,c=i;
	}
}