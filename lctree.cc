
class Node_t {
public:
	Node_t *l, *r, *p, *u;
	//additional data
	Node_t(int v = -inf) :l(NULL), r(NULL), p(NULL), u(NULL){}
};
typedef Node_t* Np;
Np& L(Np nd) { return nd->l; }
Np& R(Np nd) { return nd->r; }
void push(Np nd) {
}
void pull(Np nd) {
	//if dependent of push (e.g. lazy value propagation), then add more pull accordingly
}
template<typename A>
void rot(Np nd, A L, A R) {
	Np p = nd->p; Np g = p->p;
	nd->p = g; if (g) ((L(g) == p) ? L(g) : R(g)) = nd;
	p->p = nd;
	L(p) = R(nd); if (R(nd)) R(nd)->p = p;
	R(nd) = p;
}
void splay(Np nd) {
	while (nd->p) {
		Np p = nd->p;
		if (!(p->p)) {
			push(p); push(nd);
			if (L(p) == nd) rot(nd, L, R);
			else rot(nd, R, L);
			pull(p); pull(nd);
		}
		else {
			Np g = p->p;
			push(g); push(p); push(nd);
			if (L(g) == p) {
				if (L(p) == nd) {
					rot(p, L, R); rot(nd, L, R);
				}
				else {
					rot(nd, R, L); rot(nd, L, R);
				}
			}
			else {
				if (R(p) == nd) {
					rot(p, R, L); rot(nd, R, L);
				}
				else {
					rot(nd, L, R); rot(nd, R, L);
				}
			}
			pull(g); pull(p); pull(nd);
		}
	}
	push(nd);
}
template<typename A>
Np getEx(Np a, A R) {
	push(a);
	while (R(a)) {
		a = R(a);
		push(a);
	}
	splay(a);
	return a;
}
Np getMax(Np a) {
	return getEx(a, R);
}
Np getMin(Np a) {
	return getEx(a, L);
}
void cutpc(Np a) {
	splay(a);
	if (R(a)) {
		R(a)->p = NULL;
		getMin(R(a))->u = a;
		R(a) = NULL;
		pull(a);
	}
}
void access(Np a) {
	cutpc(a);
	for (Np it = getMin(a); it->u;) {
		Np u = it->u;
		cutpc(u);
		R(u) = it; it->p = u; it->u = NULL;
		pull(u);
		it = getMin(u);
	}
	splay(a);
}
void link(Np c, Np p) {
	access(c); access(p);
	R(p) = c; c->p = p;
	pull(p);
}
void cut(Np v) {
	access(v);
	L(v)->p = NULL;
	L(v) = NULL;
	pull(v);
}
Np getParent(Np v) {
	splay(v);
	return v->l ? getMax(v->l) : v->u;
}
void toroot(Np u) {//define rev before use
	access(u);
	u->rev = true;
}
Np getRoot(Np v) {
	access(v);
	return getMin(v);
}
Np LCA(Np u, Np v) {
	access(u); access(v);
	splay(u);
	Np um = getMin(u);
	splay(v);
	Np vm = getMin(v);
	if (um == vm)return u;
	else return um->u;
}
Np GetParent(Np c) {
	splay(c);
	return L(c)? getMax(L(c)) : c->u;
}