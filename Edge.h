//
// Created by jhnah on 2020-11-06.
//

#ifndef EUCLIDEAN_TSP_SOLVER_EDGE_H
#define EUCLIDEAN_TSP_SOLVER_EDGE_H

#include "General.h"

struct Edge{
    int s, e; T x;
    Edge() : Edge(0, 0, 0) {}
    Edge(int s, int e, T x) : s(s), e(e), x(x) {}
    bool operator < (const Edge &t) const { return tie(x, s, e) < tie(t.x, t.s, t.e); }
};

#endif //EUCLIDEAN_TSP_SOLVER_EDGE_H
