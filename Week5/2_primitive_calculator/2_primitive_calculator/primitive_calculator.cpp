#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// This is a greedy algorithm, it doesn't work
vector<int> optimal_sequence(int n) {
    std::vector<int> sequence;
    while (n >= 1) {
        sequence.push_back(n);
        if (n % 3 == 0) {
            n /= 3;
        } else if (n % 2 == 0) {
            n /= 2;
        } else {
            n = n - 1;
        }
    }
    reverse(sequence.begin(), sequence.end());
    return sequence;
}


// This is a dynamic programming approach, very tricky to work out
vector<int> dp_optimal_sequence2(int n){
    // In this vector we record the sequence of numbers to reach the target n
    vector<int> sequence;

    // In this vector we record number of operations required to reach each number from 1 to n
    // i.e. element at index 6 will have value of 2 because it takes 2 operations to reach 6 from 1
    // namely 6 = 1 * 3 * 2 <--- 2 operations
    vector<int> numOps(n+1, 0);
    numOps[1]=0;

    // Here we build a vector memoIzing (cs jargon not a typo)
    // the number of operations required to reach each number from 1 to n
    for (int i=2; i<= n; i++){
        numOps[i] = numOps[i-1]+1;
        if (i%2==0) numOps[i] = min(1 + numOps[i/2], numOps[i]);
        if (i%3==0) numOps[i] = min(1 + numOps[i/3], numOps[i]);
    }

    // Here we build out the sequence in reverse order starting from n and going down
    for (int i=n; i>1;){
        sequence.push_back(i);
        if (numOps[i-1] == numOps[i] - 1) i--;
        else if( i%2==0 && numOps[i/2]==numOps[i]-1 ) i = i/2;
        else if( i%3==0 && numOps[i/3]==numOps[i]-1) i = i/3;
    }
    sequence.push_back(1);

    reverse(sequence.begin(), sequence.end());
    return sequence;
}


int main() {
    int n;
    std::cin >> n;
    vector<int> sequence = dp_optimal_sequence2(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
}
