//
// Created by jhnah on 2020-11-06.
//

#ifndef EUCLIDEAN_TSP_SOLVER_EUCLIDEANMST_H
#define EUCLIDEAN_TSP_SOLVER_EUCLIDEANMST_H

#include "./DelaunayTriangulation.h"
#include "./Edge.h"

namespace EuclideanMST{
    namespace UnionFind{
        vector<int> par;
        void init(int n){ par.resize(n); iota(all(par), 0); }
        int find(int v){ return v == par[v] ? v : par[v] = find(par[v]); }
        bool merge(int u, int v){
            u = find(u); v = find(v);
            if(u == v) return false;
            par[u] = v; return true;
        }
    }
    vector<Edge> euclideanMST(vector<P> v){
        map<P, int> id; vector<Edge> edge, ret;
        UnionFind::init(v.size());
        for(int i=0; i<v.size(); i++) id[v[i]] = i;
        auto res = Triangulation::triangulate(v);
        for(const auto &i : res){
            for(int j=0; j<3; j++) edge.emplace_back(id[i[j]], id[i[(j+1)%3]], dst(i[j], i[(j+1)%3]));
        }
        sort(all(edge));
        for(auto i : edge){
            if(!UnionFind::merge(i.s, i.e)) continue;
            ret.push_back(i);
        }
        return ret;
    }
}

#endif //EUCLIDEAN_TSP_SOLVER_EUCLIDEANMST_H
