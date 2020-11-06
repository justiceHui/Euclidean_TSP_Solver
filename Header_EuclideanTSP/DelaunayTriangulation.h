//
// Created by jhnah on 2020-11-06.
//

#ifndef EUCLIDEAN_TSP_SOLVER_DELAUNAYTRIANGULATION_H
#define EUCLIDEAN_TSP_SOLVER_DELAUNAYTRIANGULATION_H

#include "../Header_Global/General.h"

// https://github.com/bqi343/USACO/blob/master/Implementations/content/geometry%20(13)/Misc/DelaunayFast.h
namespace Triangulation{
#define sz(v) (int)((v).size())
#define pb push_back
#define f first
#define s second
    typedef __int128_t lll;
    typedef vector<P> vP;
    T   sq (T a) { return a*a; }
    
    T norm(const P& p) { return sq(p.f)+sq(p.s); }
    P conj(const P& p) { return {p.f, -p.s}; }
    
    P operator-(const P& l) { return {-l.f, -l.s}; }
    P operator+(const P& l, const P& r) { return {l.f+r.f,l.s+r.s}; }
    P operator-(const P& l, const P& r) { return {l.f-r.f,l.s-r.s}; }
    P operator*(const P& l, const T& r) { return {l.f*r,l.s*r}; }
    P operator*(const T& l, const P& r) { return r*l; }
    P operator/(const P& l, const T& r) { return {l.f/r,l.s/r}; }
    P operator*(const P& l, const P& r) { return {l.f*r.f-l.s*r.s,l.s*r.f+l.f*r.s}; }
    P operator/(const P& l, const P& r) { return l*conj(r)/norm(r); }
    P& operator+=(P& l, const P& r) { return l = l+r; }
    P& operator-=(P& l, const P& r) { return l = l-r; }
    P& operator*=(P& l, const T& r) { return l = l*r; }
    P& operator/=(P& l, const T& r) { return l = l/r; }
    P& operator*=(P& l, const P& r) { return l = l*r; }
    P& operator/=(P& l, const P& r) { return l = l/r; }
    
    T cross(const P& t1, const P& t2) { return t1.f*t2.s-t1.s*t2.f; }
    T cross(const P& t1, const P& t2, const P& t3) { return cross(t2-t1,t3-t1); }
    bool inCircle(P p, P a, P b, P c) {
        a -= p, b -= p, c -= p;
        lll x = (lll)norm(a)*cross(b, c) + (lll)norm(b)*cross(c, a) + (lll)norm(c)*cross(a, b);
        return x * (cross(a, b, c)>0 ? 1 : -1) > 0;
    }
    
    P arb(LLONG_MAX, LLONG_MAX); // not equal to any other point
    typedef struct Quad* Q;
    struct Quad {
        bool mark; Q o, rot; P p;
        P F() const { return r()->p; }
        Q r() const { return rot->rot; }
        Q prev() const { return rot->o->rot; }
        Q next() const { return r()->prev(); }
    };
    Q makeEdge(P orig, P dest) {
        Q q[] = {
                new Quad{ false,nullptr,nullptr,orig },
                new Quad{ false,nullptr,nullptr,arb },
                new Quad{ false,nullptr,nullptr,dest },
                new Quad{ false,nullptr,nullptr,arb } };
        for (int i = 0; i<4; i++) q[i]->o = q[-i & 3], q[i]->rot = q[(i + 1) & 3];
        return *q;
    }
    void splice(Q a, Q b) { swap(a->o->rot->o, b->o->rot->o); swap(a->o, b->o); }
    Q connect(Q q1, Q q2) {
        Q q = makeEdge(q1->F(), q2->p);
        splice(q, q1->next()); splice(q->r(), q2);
        return q;
    }
    
    pair<Q, Q> rec(const vP& s) {
        if (sz(s) <= 3) {
            Q a = makeEdge(s[0], s[1]), b = makeEdge(s[1], s.back());
            if (sz(s) == 2) return { a, a->r() };
            splice(a->r(), b);
            auto side = cross(s[0], s[1], s[2]);
            Q c = side ? connect(b, a) : nullptr;
            return { side < 0 ? c->r() : a, side < 0 ? c : b->r() };
        }
#define H(e) e->F(), e->p
#define valid(e) (cross(e->F(),H(base)) > 0)
        Q A, B, ra, rb;
        int half = sz(s) / 2;
        auto AA = rec({ all(s) - half }), BB = rec({ sz(s) - half + all(s) });
        ra = AA.first; A = AA.second;
        B = BB.first; rb = BB.second;
        while ((cross(B->p, H(A)) < 0 && (A = A->next())) ||
               (cross(A->p, H(B)) > 0 && (B = B->r()->o)));
        Q base = connect(B->r(), A);
        if (A->p == ra->p) ra = base->r();
        if (B->p == rb->p) rb = base;

#define DEL(e, init, dir) Q e = init->dir; if (valid(e)) \
		while (inCircle(e->dir->F(), H(base), e->F())) { \
			Q t = e->dir; \
			splice(e, e->prev()); \
			splice(e->r(), e->r()->prev()); \
			e = t; \
		}
        while (true) {
            DEL(LC, base->r(), o)
            DEL(RC, base, prev())
            if (!valid(LC) && !valid(RC)) break;
            if (!valid(LC) || (valid(RC) && inCircle(H(RC), H(LC))))
                base = connect(RC, base->r());
            else base = connect(base->r(), LC->r());
        }
        return { ra, rb };
    }
    vector<array<P, 3>> triangulate(vP pts) {
        sort(all(pts));
        if (sz(pts) < 2) return {};
        Q e = rec(pts).first; vector<Q> q = { e };
        while (cross(e->o->F(), e->F(), e->p) < 0) e = e->o;
#define ADD { Q c = e; do { c->mark = 1; pts.pb(c->p); \
	q.pb(c->r()); c = c->next(); } while (c != e); }
        ADD
        pts.clear();
        int qi = 0; while (qi < sz(q)) if (!(e = q[qi++])->mark) ADD
        vector<array<P, 3>> ret(sz(pts) / 3);
        for (int i = 0; i<sz(pts); i++) ret[i / 3][i % 3] = pts[i];
        return ret;
    }
#undef sz
#undef pb
#undef f
#undef s
}

#endif //EUCLIDEAN_TSP_SOLVER_DELAUNAYTRIANGULATION_H
