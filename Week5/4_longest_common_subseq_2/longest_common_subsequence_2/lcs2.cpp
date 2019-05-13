#include <iostream>
#include <vector>

using namespace std;


/* Classical longest common subsequence algorithm, read CLRS 3rd ed, ch 15.4 p390 for a great explanation */
int lcs2(vector<int> &x, vector<int> &y) {
    // Initialize value table c[0..m, 0..n]
    size_t m = x.size();
    size_t n = y.size();
    int c[m+1][n+1];

    // Populate value table
    for (size_t i=0; i<=m; i++){
        c[i][0] = 0;
    }

    for(size_t j=0; j<=n; j++){
        c[0][j] = 0;
    }

    for(size_t i=1; i<=m; i++){
        for(size_t j=1; j<=n; j++){
            if( x[i-1] == y[j-1] ){
                c[i][j] = c[i-1][j-1] + 1;
            }
            else if ( c[i-1][j] >= c[i][j-1] ){
                c[i][j] = c[i-1][j];
            }
            else {
                c[i][j] = c[i][j-1];
            }
        }
    }

    return c[m][n];
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i];
    }

    size_t m;
    std::cin >> m;
    vector<int> y(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> y[i];
    }

    std::cout << lcs2(x, y) << std::endl;
}
