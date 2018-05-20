
namespace NT {
	int powmod(long long n, int e, int p) {
		int ret = 1;
		while (e) {
			if (e&1) ret=ret*n%p, e--;
			else n=n*n%p, e/=2;
		}
		return ret;
	}
	//zQ should have order 2^S
	int sqrt_modp(long long a, int p,
long long zQ, int& stat) {
		stat = 1;
		if (!a) return 0;
		if (powmod(a, (p-1)/2, p)==p-1) {
			stat = 0; return 0;
		}
		int Q = p - 1; int S = 0;
		while (!(Q & 1)) Q /= 2, S++;
		if (S == 1) {
			return powmod(a,(p + 1) / 4, p);
		}
		long long R = powmod(a, (Q+1)/2, p);
		long long t = powmod(a, Q, p);
		int M = S;
		while (t != 1) {
			int i = 0; long long x = t;
			while (x != 1)x = x*x%p, i++;
			long long b = zQ;
			for (int j=0; j<M-i-1; j++)b = b*b%p;
			R = R*b%p;
			t = t*(b*b%p) % p;
			zQ = b*b%p;
			M = i;
		}
		return (int)R;
	}
}