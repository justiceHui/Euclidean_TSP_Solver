//
// Created by jhnah on 2020-11-06.
//

#ifndef EUCLIDEAN_TSP_SOLVER_EUCLIDEANTSP_H
#define EUCLIDEAN_TSP_SOLVER_EUCLIDEANTSP_H

#include "./EuclideanMST.h"

namespace EuclideanTSP{
    vector<vector<int>> g;
    vector<int> in;
    int pv;
    void dfs(int v){ in[v] = ++pv; for(auto i : g[v]) if(!in[i]) dfs(i); }
    pair<T, vector<int>> euclideanTSP(vector<P> v, int root){
        g = vector<vector<int>>(v.size());
        in = vector<int>(v.size());
        pv = 0;
        vector<Edge> mstEdge = EuclideanMST::euclideanMST(v);
        for(auto i : mstEdge) g[i.s].push_back(i.e), g[i.e].push_back(i.s);
        dfs(root);
        vector<int> ord(v.size()); iota(all(ord), 0);
        sort(all(ord), [&](int a, int b){ return in[a] < in[b]; });
        ord.push_back(ord[0]);
        T ans = 0;
        for(int i=0; i<v.size(); i++) ans += dst(v[ord[i]], v[ord[i+1]]);
        return make_pair(ans, ord);
    }
}

#endif //EUCLIDEAN_TSP_SOLVER_EUCLIDEANTSP_H
