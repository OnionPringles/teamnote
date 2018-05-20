
class Suffix_A {
public:
	int len[N<<1];int link[N<<1];
	int ch[N<<1][W];
	int last = 1; int size = 1;
	void add(int c) {
		int cur=last; int newnode=++size;
		len[newnode]=len[cur]+1; last=newnode;
		for (;cur&&!ch[cur][c];cur=link[cur]) 
			ch[cur][c] = newnode;
		if (cur) {
			int ncur = ch[cur][c];
			if (len[ncur] == len[cur]+1)
				link[newnode] = ncur;
			else {
				int nncur = ++size;
				link[nncur]=link[ncur];
				link[newnode] = link[ncur] = nncur;
				for (int i = 0; i < W; i++)
					ch[nncur][i] = ch[ncur][i];
				len[nncur] = len[cur]+1;
				for (;cur&&ch[cur][c]==ncur;cur=link[cur]) ch[cur][c] = nncur;
			}
		}
		else link[newnode] = 1;
	}
};