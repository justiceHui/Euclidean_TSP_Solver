#include <random>

#include "./Header_Global/General.h"
#include "./Header_Global/FileManage.h"
#include "./Header_EuclideanTSP/EuclideanTSP.h"
#include "./Header_Optimize/NaiveOptimizer.h"

bool validate(const vector<int> &vec){
    vector<bool> chk(vec.size()-1);
    for(int i=0; i<vec.size()-1; i++){
        if(chk[vec[i]]) return false;
        chk[vec[i]] = true;
    }
    return true;
}

int main() {
    const int TEST_NO = 1;
    const int TARGET_SCORE = 4817;
    const int MAX_TRIAL = 1000;
    setFileName(TEST_NO);
    
    openInputFile();
    int N; cin >> N;
    vector<P> V(N); for(auto &i : V) cin >> i;
    closeInputFile();
    
    auto res = EuclideanTSP::euclideanTSP(V, 0);
    
    vector<int> trial(N);
    iota(all(trial), 0);
    shuffle(all(trial), std::mt19937(std::random_device()()));
    for(int i=0; i<min(N, MAX_TRIAL); i++){
        res = min(res, EuclideanTSP::euclideanTSP(V, trial[i]));
        cerr << "Euclidean Epoch #" << i+1 << ": " << sqrt(res.x) << "\n";
    }
    assert(validate(res.y));
    
    cerr << "score : " << sqrt(res.x) << "\n";
    auto opt = NaiveOptimizer::optimize(V, res.y, TARGET_SCORE);
    cerr << "score : " << sqrt(opt.x) << "\n";
    
    openOutputFile();
    for(auto i : res.y) cout << i+1 << "\n";
    closeOutputFile();
}
