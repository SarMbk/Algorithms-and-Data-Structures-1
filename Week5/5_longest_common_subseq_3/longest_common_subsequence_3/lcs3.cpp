#include <iostream>
#include <vector>
using namespace std;


/* LCS of 3 sequences a, b and c. Implemented using a similar algorithm to that of 2 sequences
 * uses a 3d array as a value table calculates the length of LCS dynamically from bottom up */

int lcs3(vector<int> &x, vector<int> &y, vector<int> &z) {
    // Initialize the 3d value table c[0..m, 0..n, 0..p]
    size_t m = x.size();
    size_t n = y.size();
    size_t p = z.size();
    int c[m+1][n+1][p+1];

    // Populate the remaining slots similar to how we did it in a 2d case
    for(size_t i=0; i<=m; i++){
        for(size_t j=0; j<=n; j++){
            for(size_t k=0; k<=p; k++){
                if (i==0 || j==0 || k==0){
                    c[i][j][k] = 0;
                }
                else if(x[i-1] == y[j-1] && x[i-1] == z[k-1]){
                    c[i][j][k] = c[i-1][j-1][k-1]+1;
                }
                else{
                    c[i][j][k] = max( max(c[i-1][j][k], c[i][j-1][k]) , c[i][j][k-1] );
                }
            }
        }
    }

    return c[m][n][p];
}


int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
}
