//fill c before execution
#define fill(A,v,n) memset((A),(v),(n)*sizeof(*(A)))
template<typename Ct>
class Hungarian {
public:
	int n;
	Ct c[N][N], lx[N], ly[N], sl[N];
	int mx[N], my[N], par[N], S[N], T[N];
	int slx[N], q[N], qs, qe;
	void init() {
		for (int i = 0; i < n; i++) {
			lx[i] = c[i][0]; ly[i] = 0;
			for (int j = 1; j < n; j++) lx[i] = max(lx[i], c[i][j]);
		}
	}
	void add(int v) {
		S[v] = 1; q[qe++] = v;
		for (int i = 0; i < n; i++) {
			if(!T[i]&&sl[i]>lx[v]+ly[i]-c[v][i]){
				slx[i] = v;
				sl[i] = lx[v] + ly[i] - c[v][i];
			}
		}
	}
	int bfs() {
		while (qs < qe) {
			int u = q[qs++];
			for (int i = 0; i < n; i++) {
				if(T[i]||lx[u]+ly[i]!=c[u][i])
					continue;
				T[i] = 1; par[i] = u;
				if (my[i] == -1) return i;
				else add(my[i]);
			}
		}
		return -1;
	}
	Ct exe(int vn) {
		n = vn; init();
		fill(mx, -1, n);
		fill(my, -1, n);
		for (int u = 0; u < n;u++) {
			fill(S, 0, n); fill(T, 0, n);
			qs = qe = 0;
			S[u] = 1; q[qe++] = u;
			for (int i = 0; i < n; i++) {
				sl[i] = lx[u] + ly[i] - c[u][i];
				slx[i] = u;
			}
			int aug;
			while ((aug=bfs()) == -1) {
				qs = qe = 0;
				Ct alph; bool got = true;
				for (int i = 0; i < n; i++)
					if (!T[i]&&(got||sl[i]<alph))
						alph = sl[i], got = false;
				if (alph) {
					for (int i = 0; i < n; i++) {
						if (S[i]) lx[i] -= alph;
						if (T[i]) ly[i] += alph;
						sl[i] -= alph;
					}
				}
				for (int i = 0; i < n; i++) {
					if (!T[i] && !sl[i]) {
						T[i] = 1; par[i] = slx[i];
						if (my[i] == -1) {
							aug = i; break;
						}
						else add(my[i]);
					}
				}
				if (~aug) break;
			}
			for (int j, i = aug; ~i;) {
				j = par[i]; my[i] = j;
				swap(mx[j], i);
			}
		}
		Ct ret = 0;
		for (int i=0;i<n;i++)ret+=lx[i]+ly[i];
		return ret;
	}
	Hungarian() {}
};
#undef fill