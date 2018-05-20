
class KMP{
public:
	char* str;int len;
	int fail[N];
	int next(int u,char c){
		while(u==len||u&&str[u]!=c)u=fail[u];
		if(str[u]==c)return u+1;
		else return 0;
	}
	void init(char* _str,int _len){
		str=_str;
		len=_len;
		fail[0]=fail[1]=0;
		for(int i=2;i<=len;i++){
			fail[i]=next(fail[i-1],str[i-1]);
		}
	}
};