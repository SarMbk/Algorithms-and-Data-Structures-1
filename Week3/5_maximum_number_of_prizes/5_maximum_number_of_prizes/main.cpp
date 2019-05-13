#include <iostream>
#include <vector>

using namespace std;

vector<int> optimal_summands(int n) {
  vector<int> summands;

  int sum = 0;
  int prizeNum = 1;

  while (sum!=n){

      if(sum+prizeNum < n || sum+prizeNum==n){
          sum+=prizeNum;
          summands.push_back(prizeNum);
          prizeNum++;
      }

      if (sum+prizeNum > n){
          summands[summands.size()-1]+= n-sum;
          sum = n;
      }

  }

  return summands;
}


int main() {
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
}
