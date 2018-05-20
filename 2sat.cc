
class TwoSAT { //use even numbers for indices
public:
	int n;
	vector<int> adj[2 * MN];
	vector<int> rev_adj[2 * MN];
	int scc[2 * MN];
	int clk_order[2 * MN];
	int vis[2 * MN];
	int clock = 0;
	int sccnum;
	int truthval[2 * MN];
	//input of init: number of variables.
	void init(int _n){
		n=_n<<1;
		for(int i=0;i<n;i++)adj[i].clear(),rev_adj[i].clear();
	}
	void addImplies(int a, int b) {
		adj[a].push_back(b);
		rev_adj[b].push_back(a);
		adj[b^1].push_back(a^1);
		rev_adj[a^1].push_back(b^1);
	}
	void dfs(int i) {
		vis[i] = 1;
		for (auto &x : rev_adj[i]) {
			if (vis[x]) continue;
			dfs(x);
		}
		clk_order[clock++] = i;
		return;
	}
	void dfs2(int i) {
		vis[i] = 1;
		scc[i] = sccnum;
		for (auto &x : adj[i]) {
			if (vis[x]) continue;
			dfs2(x);
		}
	}
	int check() {
		memset(vis, 0, sizeof(vis));
		clock = 0;
		for (int i = 0; i < n; i++) {
			if (vis[i]) continue;
			dfs(i);
		}
		memset(vis, 0, sizeof(vis));
		sccnum = 0;
		for (int i = n - 1; i >= 0; i--) {
			if (vis[clk_order[i]]) continue;
			sccnum++;
			dfs2(clk_order[i]);
		}
		for (int i = 0; i < n; i+=2)
			if (scc[i] == scc[i|1]) return 0;
		return 1;
	}
	void getTable() {
		for (int i = 0; i < n; i++) 
			truthval[i] = (scc[i] < scc[i^1]);
	}
};