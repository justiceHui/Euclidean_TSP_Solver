#include "./General.h"
#include "./Header_EuclideanTSP/EuclideanTSP.h"

void OpenDataFile(const int TEST_NO){
    const string FILE_NAME = (TEST_NO < 10 ? "../TSP_data/0" : "../TSP_data/") + to_string(TEST_NO);
    const string INPUT_FILE = FILE_NAME + ".in";
    const string OUTPUT_FILE = FILE_NAME + ".out";
    const string ERROR_FILE = FILE_NAME + ".err";
    freopen(INPUT_FILE.c_str(), "r", stdin);
    freopen(OUTPUT_FILE.c_str(), "w", stdout);
    //freopen(ERROR_FILE.c_str(), "w", stderr);
}

int main() {
    const int TEST_NO = 1;
    const int MAX_TRIAL = 1000;
    OpenDataFile(TEST_NO);
    int N; cin >> N;
    vector<P> V(N); for(auto &i : V) cin >> i;
    auto res = EuclideanTSP::euclideanTSP(V, 0);
    
    vector<int> trial(N);
    iota(all(trial), 0);
    shuffle(all(trial), std::mt19937(std::random_device()()));
    for(int i=0; i<min(N, MAX_TRIAL); i++){
        res = min(res, EuclideanTSP::euclideanTSP(V, trial[i]));
    }
    cerr << "score : " << sqrt(res.x) << "\n";
    for(auto i : res.y) cout << i+1 << "\n";
}
