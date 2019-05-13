#include <iostream>
#include <vector>
using namespace std;

// Problem 1
int get_change(int m) {
    int remaining = m;
    vector <int> changeCoins {10, 5, 1};
    int coinCount=0;
    while(remaining != 0 ){
        for (size_t i=0; i<changeCoins.size(); i++){
            if (remaining >= changeCoins[i]){
                remaining-=changeCoins[i];
                coinCount++;
                break;
            }
        }
    }
    return coinCount;
}

int main() {
  int m;
  cin >> m;
  cout << get_change(m) << '\n';
}

