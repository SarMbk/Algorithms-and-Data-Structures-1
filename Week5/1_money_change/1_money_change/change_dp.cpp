#include <iostream>
#include <vector>
using namespace std;


// Change with coins of denominations 1, 3, 4
int get_change(int m) {
    const vector<int> coinDenoms {1, 3, 4};
    vector<int> numCoinsTable(m+1);
    numCoinsTable[0] = 0;

    for (int amount = 1; amount<=m; amount++){
        numCoinsTable[amount] = 1000000;
        for(int coin=0; coin<coinDenoms.size(); coin++){
            if(amount >= coinDenoms[coin]){
                int numCoins = numCoinsTable[amount - coinDenoms[coin]] + 1;
                if(numCoins < numCoinsTable[amount]){
                    numCoinsTable[amount] = numCoins;
                }
            }
        }
    }

    return numCoinsTable[m];
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
