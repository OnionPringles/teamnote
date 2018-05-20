
template<typename F>
class PRL {
public:
	PRL() {}
	F c[N][N], f[N][N], e[N];
	int l[N], chk[N];
	int n, S, T;
	queue<int> Q;
	void init(int vn) { n = vn; }
	void push(int u, int v) {
		F del = min(e[u], c[u][v] - f[u][v]);
		e[u] -= del; e[v] += del;
		f[u][v] += del; f[v][u] -= del;
		if (!chk[v] && v != S && v != T) {
			chk[v] = 1;
			Q.push(v);
		}
	}
	F exe(int s, int t) {
		S = s; T = t;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				f[i][j] = 0;
			e[i] = 0;
		}
		l[S] = n;
		for (int i = 0; i < n; i++) {
			if (i != S) {
				f[S][i] = c[S][i];
				f[i][S] = -f[S][i];
				e[i] += f[S][i];
				e[S] -= f[S][i];
				l[i] = 0;
				if (i != T && e[i]) {
					Q.push(i);
				}
			}
		}
		while (!Q.empty()) {
			int u = Q.front(); int m = 3*n+10;
			for (int v = 0; v < n && e[u]; v++) {
				if (c[u][v] > f[u][v]) {
					if (l[u] > l[v]) push(u, v);
					else m = min(m, l[v]);
				}
			}
			if (e[u])l[u] = 1 + m;
			else {
				Q.pop(); chk[u] = 0;
			}
		}
		return e[T];
	}
};