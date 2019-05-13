#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

/* Explicitly defining LONG_MAX & LONG_MIN as constants because the grader does not understand LONG_MAX and LONG_MIN */
const long LARGENUM =  2147483647;
const long SMALLNUM = -2147483647;


/* Support function that prints a 2d matrix. Used only for debugging */
void print2Dvector(vector<vector<long> > &v){
    for (size_t i=0; i<v.size(); i++){
        for (int j=0; j<v.size(); j++){
            cout << v[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}


/* Returns true if the character is a +, - or * operator, else returns false */
bool isOperator(char ch){
    if (ch=='*' || ch == '+' || ch=='-') return true;
    return false;
}


/* Short quick helper function to conver character '1', '2', '3' etc to integers 1, 2, 3 etc. */
int ctoi(char c){
    int ans = c;
    return ans-'0';
}


/* Helper function, to help make calculations */
long operation(long a, char opk, long b){
    if (opk=='+') return a+b;
    else if (opk=='-') return a-b;
    else return a*b;
}


/* Function that helps populate the matrix of minimi at index i, j */
long getMins(size_t i, size_t j, vector<vector<long> > &minTable, vector<vector<long> > &maxTable, vector<char> &ops){
    long minVal = LARGENUM;
    for (size_t k=i; k<=j-1; k++){
        long a = operation(maxTable[i][k], ops[k], maxTable[k+1][j]);
        long b = operation(maxTable[i][k], ops[k], minTable[k+1][j]);
        long c = operation(minTable[i][k], ops[k], maxTable[k+1][j]);
        long d = operation(minTable[i][k], ops[k], minTable[k+1][j]);

        long min1 = min(a,b);
        long min2 = min(c,d);
        long min3 = min(min1, min2);

        minVal = min(minVal, min3);
    }
    return minVal;
}


/* Function that helps populate the matrix of maximi at index i, j */
long getMaxes(size_t i, size_t j, vector<vector<long> > &minTable, vector<vector<long> > &maxTable, vector<char> &ops){
    long maxVal = SMALLNUM;
    for (size_t k=i; k<=j-1; k++){
        long a = operation(maxTable[i][k], ops[k], maxTable[k+1][j]);
        long b = operation(maxTable[i][k], ops[k], minTable[k+1][j]);
        long c = operation(minTable[i][k], ops[k], maxTable[k+1][j]);
        long d = operation(minTable[i][k], ops[k], minTable[k+1][j]);

        long max1 = max(a,b);
        long max2 = max(c,d);
        long max3 = max(max1, max2);

        maxVal = max(maxVal, max3);
    }
    return maxVal;
}


/* Function to get the maximum value of an arithmetic expression, see lectures for explanation */
long get_maximum_value(string &str){
    //Store operators and numbers in different vectors
    vector<int> nums;
    vector<char> ops;

    //Loop through the string and get operators and numbers
    for (size_t i=0; i<str.size(); i++){
        if(isOperator(str[i])) ops.push_back(str[i]);
        else nums.push_back( ctoi(str[i]) );
    }

    // Initialize 2D tables of minimal and maximal values
    size_t n = nums.size();
    vector<vector<long> > maxTable(n, vector<long>(n, 0));
    vector<vector<long> > minTable(n, vector<long>(n, 0));

    // Initialize the  known diagonal values
    for (int i=0; i<n; i++){
        minTable[i][i] = nums[i];
        maxTable[i][i] = nums[i];
    }

    // Populate the matrices of maxes and mins
    for (size_t h=0; h<n; h++){
        for(size_t i=0; i<n-h; i++){
            size_t j=h+i;
            if(i!=j){
                long minij=getMins(i, j, minTable, maxTable, ops);
                minTable[i][j] = minij;

                long maxij = getMaxes(i, j, minTable, maxTable, ops);
                maxTable[i][j] = maxij;
            }
        }
    }

    // Print max and min matrices if you need to for debugging
    // print2Dvector(minTable);
    // print2Dvector(maxTable);

    return maxTable[0][n-1];

}


int main() {
  string str;
  std::cin >> str;
  std::cout << get_maximum_value(str) << '\n';
}






