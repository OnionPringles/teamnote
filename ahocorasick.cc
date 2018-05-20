
#define CONVERT(c) (c)-'a'
class AhoCora{
public:
	struct Node{
		int ch[CHAR];
		int dic,link,dic_link;
	}nd[N];
	int Q[N]; int qs,qe;
	int size;
	int createNode(){
		int ret=size++;
		for(int i=0;i<CHAR;i++){
			nd[ret].ch[i]=-1;
		}
		nd[ret].dic=0;
		return ret;
	}
	void init(){
		size=0;
		createNode();
	}
	template<typename A>
	void add(A str,int sz){
		int cur=0;
		for(int i=0;i<sz;i++){
			int c=CONVERT(str[i]);
			if(nd[cur].ch[c]==-1){
				int nnd=createNode();
				nd[cur].ch[c]=nnd;
			}
			cur=nd[cur].ch[c];
		}
		nd[cur].dic=1;
	}
	inline int next(int u,int c){
		while(u&&nd[u].ch[c]<0)
			u=nd[u].link;
		if(nd[u].ch[c]<0)return 0;
		else return nd[u].ch[c];
	}
	void computelink(){
		qs=qe=0;
		nd[0].link=nd[0].dic_link=0;
		for(int x,i=0;i<CHAR;i++){
			if((x=nd[0].ch[i])>=0){
				Q[qe++]=x;
				nd[x].link=nd[x].dic_link=0;
			}
		}
		while(qs<qe){
			int u=Q[qs++];
			for(int v,i=0;i<CHAR;i++){
				if((v=nd[u].ch[i])>=0){
					Q[qe++]=v;
					int m=nd[u].link;
					int L=nd[v].link=next(m,i);
					if(nd[L].dic)nd[v].dic_link=L;
					else nd[v].dic_link=nd[L].dic_link;
				}
			}
		}
	}
};