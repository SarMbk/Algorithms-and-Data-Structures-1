#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>
using namespace std;


int getSum( const vector<int> &v){
    int sum = 0;
    for (size_t i=0; i<v.size(); i++)
        sum+=v[i];
    return sum;
}


// Helper function for solving 3 partition problem
// It return true if there exists three subsets with given sum
bool subsetSum(vector<int> &v, int n, int a, int b, int c, unordered_map<string, bool> &subsetMap){
    // return true if subset is found
    if (a == 0 && b == 0 && c == 0)
        return true;

    // base case: no items left
    if (n < 0)
        return false;

    // construct a unique map key from dynamic elements of the input
    string key = to_string(a) + "|" + to_string(b) + "|" + to_string(c) +
                "|" + to_string(n);

    // if sub-problem is seen for the first time, solve it and
    // store its result in a map
    if (subsetMap.find(key) == subsetMap.end())
    {
        // Case 1. current item becomes part of first subset
        bool A = false;
        if (a - v[n] >= 0)
            A = subsetSum(v, n - 1, a - v[n], b, c, subsetMap);

        // Case 2. current item becomes part of second subset
        bool B = false;
        if (!A && (b - v[n] >= 0))
            B = subsetSum(v, n - 1, a, b - v[n], c, subsetMap);

        // Case 3. current item becomes part of third subset
        bool C = false;
        if ((!A && !B) && (c - v[n] >= 0))
            C = subsetSum(v, n - 1, a, b, c - v[n], subsetMap);

        // return true if we get solution
        subsetMap[key] = A || B || C;
    }

    // return the subproblem solution from the map
    return subsetMap[key];
}


bool partition3(vector<int> &v, int n){
    if (n < 3)
        return false;
    unordered_map<string, bool> subsetMap;
    int sum = getSum(v);
    return !(sum % 3) && subsetSum(v, n - 1, sum/3, sum/3, sum/3, subsetMap);
}


// main function for 3-partition problem
int main() {
    int n;
    std::cin >> n;
    vector<int> v(n);
    for (size_t i = 0; i < v.size(); ++i) {
        std::cin >> v[i];
    }
    std::cout << partition3(v, n) << '\n';
}

