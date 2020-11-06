//
// Created by jhnah on 2020-11-06.
//

#ifndef EUCLIDEAN_TSP_SOLVER_NAIVEOPTIMIZER_H
#define EUCLIDEAN_TSP_SOLVER_NAIVEOPTIMIZER_H

#include "../Header_Global/General.h"
#include "../Header_Global/FileManage.h"

namespace NaiveOptimizer{
    vector<P> pts;
    mt19937_64 rd;
    int rand(int l, int r){
        return uniform_int_distribution<int>(l, r)(rd);
    }
    T evaluate(const vector<int> &ord){
        T ret = 0;
        for(int i=0; i+1<ord.size(); i++) ret += dst(pts[ord[i]], pts[ord[i+1]]);
        return ret;
    }
    vector<int> transition(const vector<int> &prv){
        vector<int> ret = prv;
        int i = rand(1, int(ret.size())-3);
        int j = rand(i+1, int(ret.size())-2);
        reverse(ret.begin()+i, ret.begin()+j+1);
        return ret;
    }
    pair<T, vector<int>> optimize(const vector<P> &pt, const vector<int> &initialState, T ed){
        pts = pt;
        rd = mt19937_64(((unsigned)chrono::steady_clock::now().time_since_epoch().count()));
        
        int epoch = 0;
        vector<int> now = initialState;
        T val = evaluate(now);
        
        cerr << "Epoch #" << epoch << ": " << sqrt(val) << "\n";
        while(val > ed){
            for(int i=0; i<100; i++){
                vector<int> nxt = transition(now);
                T nxtVal = evaluate(nxt);
                if(nxtVal <= val){
                    now = nxt; val = nxtVal;
                    break;
                }
            }
            cerr << "Epoch #" << ++epoch << ": " << sqrt(val) << "\n";
            if(epoch % 1000 == 0){
                openOutputFile();
                for(auto i : now) cout << i+1 << "\n";
                closeOutputFile();
            }
        }
        return {val, now};
    }
}

#endif //EUCLIDEAN_TSP_SOLVER_NAIVEOPTIMIZER_H
