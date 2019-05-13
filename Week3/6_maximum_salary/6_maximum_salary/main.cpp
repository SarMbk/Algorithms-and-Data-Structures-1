#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isGreaterOrEqual(string num, string maxDigit){
    if (stoi(num+maxDigit) >= stoi(maxDigit+num)) return true;
    return false;
}


string largest_number(vector<string> numbers) {
    string ans = "";
    while(numbers.size()>0){
        string maxDigit = numbers[0];
        size_t maxIndex;
        for (size_t i = 0; i<numbers.size(); i++){
            if (isGreaterOrEqual(numbers[i], maxDigit)){
                maxDigit = numbers[i];
                maxIndex = i;
            }
        }
        ans+= maxDigit;
        numbers.erase(numbers.begin()+maxIndex);
    }
    return ans;
}

int main() {
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a) << endl;
}
