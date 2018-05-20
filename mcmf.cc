
template <typename Ct>
class MCMF {
public:
	class Edge {
	public:
		int u, v, f, c; Ct cost;
		Edge() {}
		Edge(int uu,int vv,int cc,Ct cst):u(uu), v(vv), c(cc), cost(cst), f(0) {}
	} el[E<<1];
	int S, T, n, en;
	Ct dist[V], pot[V];
	int vis[V], par[V];
	vector<int> adj[V];
	int cflow; Ct ccost;
	void init(int nn) {
		n = nn, en = 0;
		for (int i=0;i<n;i++)adj[i].clear(); 
	}
	void addEdge(int u,int v,int c,Ct cost) {
		el[en] = Edge(u,v,c,cost);
		adj[u].push_back(en++);
		el[en] = Edge(v,u,0,-cost);
		adj[v].push_back(en++);
	}
	int dijk() {
		priority_queue<pair<Ct, int> > pq;
		for (int i=0; i<n; i++)dist[i]=TMAX, vis[i]=0, par[i]=-1;
		dist[S]=0;
		pq.push(make_pair(-dist[S], S));
		while (!pq.empty()) {
			int u = pq.top().second;  pq.pop();
			if (vis[u])continue;
			vis[u] = 1;
			for (auto &i : adj[u]) {
				int v = el[i].v;
				if (vis[v] || el[i].f == el[i].c)
					continue;
				Ct tmpc = el[i].cost+pot[u]-pot[v];
				if (dist[u] + tmpc<dist[v]) {
					dist[v] = dist[u] + tmpc;
					pq.push(make_pair(-dist[v], v));
					par[v] = i;
				}
			}
		}
		return vis[T];
	}
	void exe(int s, int t) {
		S=s; T=t;
		cflow = 0; ccost = 0;
		memset(pot, 0, n*sizeof(*pot));
		while (dijk()) {
			int nf = inf_flow;
			for (int i=par[T];~i;i=par[el[i].u])
				nf=min(nf,el[i].c-el[i].f);
			for(int i=par[T];~i;i=par[el[i].u]) {
				el[i].f+=nf, el[i^1].f-=nf;
			}
			cflow += nf;
			for (int i=0;i<n;i++)pot[i]+=dist[i];
			ccost+=pot[T]*nf;
		}
	}
};