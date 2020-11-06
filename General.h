//
// Created by jhnah on 2020-11-06.
//

#ifndef EUCLIDEAN_TSP_SOLVER_GENERAL_H
#define EUCLIDEAN_TSP_SOLVER_GENERAL_H

#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) (v).begin(), (v).end()
using namespace std;

using T = long double;
using P = pair<T, T>;
inline T dst(const P& a, const P& b){ return hypot(a.x-b.x, a.y-b.y); }
istream& operator >> (istream &in, P &t){ in >> t.x >> t.y; return in; }

#endif //EUCLIDEAN_TSP_SOLVER_GENERAL_H
