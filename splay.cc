
class Node_t {
public:
    int val;
    Node_t *l, *r, *p;
    bool rev;
    int M, m; long long sum; int cnt;
    Node_t(int x = 0) :val(x), rev(false), M(x), m(x), sum(x), cnt(1), l(NULL), r(NULL), p(NULL) {}
    inline void upd_rev() {
        if (!rev)return;
        else {
            rev = false;
            if (l) l->rev = !(l->rev);
            if (r) r->rev = !(r->rev);
            swap(l, r);
        }
    }
    void upd_info() {
        sum = M = m = val; cnt = 1;
        if (l) {
            M = max(M, l->M); m = min(m, l->m); sum += l->sum;
            cnt += l->cnt;
        }
        if (r) {
            M = max(M, r->M); m = min(m, r->m); sum += r->sum;
            cnt += r->cnt;
        }
    }
} nds[N];
typedef Node_t* Np;
Np root;
Np& L(Np nd) { return nd->l; }
Np& R(Np nd) { return nd->r; }
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
            p->upd_rev(); nd->upd_rev();
            if (L(p) == nd) rot(nd, L, R);
            else rot(nd, R, L);
            p->upd_info(); nd->upd_info();
        }
        else {
            Np g = p->p;
            g->upd_rev(); p->upd_rev(); nd->upd_rev();
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
            g->upd_info(); p->upd_info(); nd->upd_info();
        }
    }
    root = nd; nd->upd_rev();
}
Np getMax(Np nd) {
    nd->upd_rev();
    while (R(nd)) {
        nd = R(nd); nd->upd_rev();
    }
    splay(nd);
    return nd;
}
Np join(Np nd1, Np nd2) {
    nd1 = getMax(nd1); 
    R(nd1) = nd2; nd2->p = nd1;
    nd1->upd_info();
    return nd1;
}
Np split(Np nd) {
    splay(nd);
    Np nr = R(nd);
    if(nr) nr->p = NULL;
    R(nd) = NULL;
    nd->upd_info();
    return nr;
}
Np find_kth(Np nd, int k) {
    while (1) {
        nd->upd_rev();
        int lcnt = (L(nd)) ? (L(nd)->cnt) : 0;
        if (lcnt == k) break;
        else if (lcnt > k) nd = L(nd);
        else {
            nd = R(nd);
            k -= lcnt + 1;
        }
    }
    splay(nd);
    return nd;
}
int order_of_node(Np nd) {
    splay(nd);
    return ((L(nd)) ? (L(nd)->cnt) : 0) + 1;
}
void split_range(int l, int r, Np& left, Np& mid, Np& right) {
    Np rth = find_kth(root, r);
    right = split(rth);
    if (l == 0) {
        left = NULL;
        mid = rth;
    }
    else {
        left = find_kth(rth, l - 1);
        mid = split(left);
    }
}
void reverse(int l, int r, int& M, int& m, long long& sum) {
    if (l > r) return;
    Np cur, left_tree, right_tree;
    split_range(l, r, left_tree, cur, right_tree);
    M = cur->M;
    m = cur->m;
    sum = cur->sum;
    cur->rev = !(cur->rev);
    if(left_tree) cur = join(left_tree, cur);
    if(right_tree) cur = join(cur, right_tree);
    root = cur;
}