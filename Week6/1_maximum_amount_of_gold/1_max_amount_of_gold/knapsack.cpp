#include <iostream>
#include <vector>

using namespace std;

int optimal_weight(int W, const vector<int> &w) {
    //write your code here
    int current_weight = 0;
    for (size_t i = 0; i < w.size(); ++i) {
        if (current_weight + w[i] <= W) {
            current_weight += w[i];
        }
    }
    return current_weight;
}


/* Classical Knapsack with no repetitions algorithm, see DPV section 6.4 for a great explanation */
int dynamic_optimal_wt(int W, const vector<int> &weights){
    // Initialize a 2d table of optimal solutions K[w][j]
    int n = weights.size();

    // Initialize this table on the heap! Grader gives an allocation error when you initialize on the stack due to very large inputs.
    long** K = new long*[W+1];
    for(int i = 0; i <= W; ++i){
        K[i] = new long[n+1];
    }

    for (int w=0; w<=W; w++){
        K[w][0] = 0;
    }
    for (int j=0; j<=n; j++){
        K[0][j] = 0;
    }

    for(int j=1; j<=n; j++){
        for (int w=1; w<=W; w++){
            if(weights[j-1]>w){
                K[w][j] = K[w][j-1];
            }
            else{
                K[w][j] = max( K[w][j-1], K[w-weights[j-1]][j-1]+ weights[j-1] );
            }
        }
    }
    return K[W][n];
}


int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> weights[i];
    }
    std::cout << dynamic_optimal_wt(W, weights) << '\n';
}
