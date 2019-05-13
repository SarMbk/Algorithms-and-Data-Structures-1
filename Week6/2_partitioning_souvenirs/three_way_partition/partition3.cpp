#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int getSum(vector<int> &v){
    int sum = 0;
    for (size_t i=0; i<v.size(); i++)
        sum+=v[i];
    return sum;
}



int subsets(vector<int> &v, size_t n_sub, int a, int b, int c, map<string, int> &subsetMap){
    if (a==0 && b==0 && c==0) return true;
    if (n_sub<0) return false;

    //Construct a map key from elements of the input
    string key = to_string(a) + "," + to_string(b) + "," + to_string(c) + "," + to_string(n_sub);

    //If such subproblem was not encountered before, solve it and record the result
    if(subsetMap.find(key) == subsetMap.end()){
        //Classical subset sum problem
        bool A = false;
        if( a-v[n_sub]>=0 ) A = subsets(v, n_sub-1, a-v[n_sub], b, c, subsetMap );

        bool B = false;
        if( !A && (b-v[n_sub] >= 0) ) B = subsets(v, n_sub-1, a, b-v[n_sub], c, subsetMap);

        bool C = false;
        if( (!A && !B) && (c-v[n_sub] >=0) ) C = subsets(v, n_sub-1, a, b, c-v[n_sub], subsetMap);

        if (A || B || C) {
            subsetMap[key] = 1;
        } else {
            subsetMap[key] = 0;
        }
    }
    subsetMap[key];
}

int partition3(vector<int> &v) {
    size_t n = v.size();

    if(n < 3){
        return 0;
    }

    map<string, int> subsetMap;
    int sum = getSum(v);

    if ( !(sum%3) && subsets(v, n-1, sum/3, sum/3, sum/3, subsetMap) ){
        return 1;
    }
    return 0;
}


int main() {
    int n;
    std::cin >> n;
    vector<int> v(n);
    for (size_t i = 0; i < v.size(); ++i) {
        std::cin >> v[i];
    }
    std::cout << partition3(v) << '\n';
}
