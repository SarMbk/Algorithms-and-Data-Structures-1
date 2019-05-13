#include <iostream>
#include <vector>
using namespace std;


long long merge_count_spit_inversions(vector<int> &v, vector<int> &v1, vector<int> &v2){
    int p, p1, p2;
    p=p1=p2=0;
    long long numInversions = 0;
    while (p1 < (int)v1.size() && p2 < (int)v2.size()){
        if(v2[p2] < v1[p1]){
            v[p++] = v2[p2++];
            numInversions += v1.size() - p1;
        }
        else
            v[p++] = v1[p1++];
    }
    while(p1<(int)v1.size()) v[p++] = v1[p1++];
    while(p2<(int)v2.size()) v[p++] = v2[p2++];
    return numInversions;
}


long long merge_sort_count_inversions(vector<int> &v){
    if (v.size()==1) return 0;
    else{
        int n1 = v.size()/2;
        int n2 = v.size() - n1;
        vector<int> v1(v.begin(), v.begin()+n1);
        vector<int> v2(v.begin()+n1, v.begin()+n1+n2);
        long long x = merge_sort_count_inversions(v1);
        long long y = merge_sort_count_inversions(v2);
        long long z = merge_count_spit_inversions(v, v1, v2);
        return x+y+z;
    }
}


int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << merge_sort_count_inversions(a) << '\n';

    return 0;
}
