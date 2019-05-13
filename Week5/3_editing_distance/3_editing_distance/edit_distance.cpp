#include <iostream>
#include <string>
using namespace std;


/* Classical edit distance algorithm. For a good explanation read DPV Algorithms section 6.3 Editing Distance.
 * The algorithm is implemented almost verbatim from that book */

int diff(char chi, char chj){
    return chi!=chj;
}

int edit_distance(const string &str1, const string &str2) {
    // Initialize a value table E(m,n)
    size_t m = str1.size();
    size_t n = str2.size();
    int E[m+1][n+1];

    // Populate the value table
    for (size_t i=0; i<=m; i++){
        E[i][0] = i;
    }

    for (size_t j=0; j<=n; j++){
        E[0][j] = j;
    }

    for (size_t i=1; i<=m; i++){
        for (size_t j=1; j<=n; j++){
            E[i][j] = min( E[i-1][j-1] + diff(str1[i-1], str2[j-1]) ,  min( E[i-1][j]+1 , E[i][j-1]+1 ) );
        }
    }

    return E[m][n];
}


int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
