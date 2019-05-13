#include <iostream>
#include <vector>
using namespace std;


size_t getMostValuable(const vector<int> &weights, const vector<int> &values){
    size_t maxIndex = 0;
    double maxVal = 0.0;

    for (size_t i=0; i<weights.size(); i++){
        if (weights[i]!=0){
            double itemVal = (double)values[i]/weights[i];
            if(itemVal>maxVal){
                maxVal = itemVal;
                maxIndex = i;
            }
        }
    }

    if (maxVal==0) maxIndex = -1;
    return maxIndex;
}



double get_optimal_value(int capacity, vector<int> &weights, vector<int> &values) {
    double lootPrice = 0.0;
    int remaining_capacity = capacity;

    while(remaining_capacity > 0 ){

        size_t maxIndex = getMostValuable(weights, values);
        if (maxIndex == -1) break;

        if( remaining_capacity >= weights[maxIndex] ){
            remaining_capacity-=weights[maxIndex];
            lootPrice+=values[maxIndex];
            weights[maxIndex] = 0;
            values[maxIndex] = 0;
        }

        else if ( remaining_capacity < weights[maxIndex] ){
            lootPrice += (double)remaining_capacity * values[maxIndex] / weights[maxIndex];
            remaining_capacity = 0;
        }

    }

    return lootPrice;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
