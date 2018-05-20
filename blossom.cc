
class Blossom{
public:
	int mat[N],q[N],qs,qe,vis[N],trp[N],par[N],rnk[N];
	typedef vector<int> VI;
	typedef vector<VI> Graph;
	void del(VI& V, int LCA){
		auto it=remove_if(V.begin(),V.end(),
		[&](int x){return vis[x]==3;});
		if(it!=V.end()){
			V.erase(it,V.end());
			if(LCA>=0)V.push_back(LCA);
		}
	}
	vector<int> blossom(const Graph& adj,int u,int v,VI& vts){
		if(rnk[u]<rnk[v])swap(u,v);
		VI P[2];
		while(rnk[u]!=rnk[v]){
			P[0].push_back(u);
			vis[u]=3;u=trp[u];
		}
		while(1){
			vis[u]=vis[v]=3;
			P[0].push_back(u);
			P[1].push_back(v);
			if(u==v)break;
			v=trp[v];u=trp[u];
		}
		int LCA=P[0].back();
		Graph nadj=adj;
		for(int i:vts){
			if(vis[i]==3&&i!=LCA){
				nadj[LCA].insert(nadj[LCA].end(),nadj[i].begin(),nadj[i].end());
				nadj[i].clear();
				continue;
			}
			del(nadj[i],LCA);
		}
		del(nadj[LCA],-1);
		vts.erase(remove_if(vts.begin(),vts.end(),[&](int x){return vis[x]==3;}),vts.end());
		vts.push_back(LCA);
		VI augP=find_aug(nadj,vts);
		int sz=augP.size(),pos;
		for(pos=0;pos<sz;pos++)
			if(augP[pos]==LCA)break;
		if(pos==sz)return augP;
		if(pos%2==0){
			reverse(augP.begin(),augP.end());
			pos=augP.size()-1-pos;
		}
		VI retP;
		retP.insert(retP.end(),augP.begin(),augP.begin()+pos);
		int vt=-1;int rk=-1;
		for(int j=0;j<2;j++){
			for(int i=0;i<(int)P[j].size();i++){
				int x=P[j][i];
				for(auto &y:adj[x])if(y==augP[pos-1]){
					vt=x;rk=i;
					break;
				}
			}
			if(vt==-1)continue;
			if(rk%2==0)retP.insert(retP.end(),P[j].begin()+rk,P[j].end());
			else{
				retP.insert(retP.end(),P[j].rend()-rk-1,P[j].rend());
				retP.insert(retP.end(),P[j^1].begin(),P[j^1].end());
			}
			break;
		}
		retP.insert(retP.end(),augP.begin()+pos+1,augP.end());
		return retP;
	}
	VI find_aug(const Graph& adj, VI& vts){
		qs=qe=0;
		for(int i:vts)vis[i]=0;
		for(int i:vts)if(mat[i]==-1){
			q[qe++]=i;
			vis[i]=1;par[i]=i;rnk[i]=0;
			trp[i]=-1;
		}
		while(qs<qe){
			int u=q[qs++];
			for(int v:adj[u]){
				if(vis[v]){
					if((rnk[v]-rnk[u])&1)
						continue;
					else if(par[u]==par[v]){
						if(u==v)continue;
						return blossom(adj,u,v,vts);
					}
					else{
						VI P(rnk[u]+rnk[v]+2);
						int rv=rnk[v];int ru=rnk[u];
						for(int i=ru;i>=0;i--,u=trp[u])P[i]=u;
						for(int i=0;i<=rv;i++,v=trp[v])P[ru+1+i]=v;
						return P;
					}
				}
				else{
					int mv=mat[v];
					vis[v]=1;vis[mv]=1;
					par[v]=par[mv]=par[u];
					rnk[v]=rnk[u]+1;rnk[mv]=rnk[u]+2;
					q[qe++]=mv;
					trp[mv]=v;trp[v]=u;
				}
			}
		}
		return vector<int>();
	}
	void solve(const Graph& adj){
		int n=adj.size();
		for(int i=0;i<n;i++)mat[i]=-1;
		while(1){
			VI V(n);
			for(int i=0;i<n;i++)V[i]=i;
			VI P=find_aug(adj,V);
			if(P.empty())return;
			else{
				for(int i=0;i<P.size();i+=2)
					mat[P[i]]=P[i+1],
					mat[P[i+1]]=P[i];
			}
		}
	}
};