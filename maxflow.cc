
struct MF {
	struct Edge {
		int u,v; F f,c;
		Edge(int uu,int vv,F cc):u(uu),v(vv),c(cc),f(0) {}
		Edge() {}
	} el[E<<1];
	int S, T, n, en;
	int dist[V], vis[V], it[V], Q[V];
	vector<int> adj[V];
	int qs, qe;
	void init(int vn) {
		for(int i=0; i<vn; i++) adj[i].clear();
		n = vn, en = 0;
	}
	void addEdge(int u, int v, F c) {
		el[en]=Edge(u,v,c);
		adj[u].push_back(en++);
		el[en]=Edge(v,u,0);
		adj[v].push_back(en++);
	}
	int bfs() {
		qs = qe = 0;
		for(int i=0;i<n;i++)vis[i]=0,dist[i]=n;
		Q[qe++] = S; vis[S] = 1; dist[S] = 0;
		while (qs<qe) {
			int u = Q[qs++];
			for (auto &j : adj[u]) {
				int v = el[j].v;
				if (vis[v]||el[j].f==el[j].c)
					continue;
				dist[v]=dist[u]+1,vis[v]=1;
				Q[qe++]=v;
			}
		}
		return vis[T];
	}
	F dfs(int u, F f) {
		if (u == T) return f;
		F cf = 0;
		for(;it[u]<(int)adj[u].size();it[u]++){
			int j=adj[u][it[u]]; int v=el[j].v;
			if (dist[v]!=dist[u]+1||el[j].f==el[j].c) continue;
			F a=dfs(v,min(f-cf,el[j].c-el[j].f));
			el[j].f+=a; el[j^1].f-=a; cf+=a;
			if (f == cf) break;
		}
		return cf;
	}
	F exe(int s, int t) {
		S=s;T=t;
		F cf = 0;
		while (bfs()) {
			memset(it, 0, n*sizeof(*it));
			cf += dfs(S, inf_flow);
		}
		return cf;
	}
};