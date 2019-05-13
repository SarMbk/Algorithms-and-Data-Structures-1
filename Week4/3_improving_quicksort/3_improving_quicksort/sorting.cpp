#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;


struct twoIndices{
    int m1, m2;
};


int partition2(vector<int> &a, int l, int r) {
    int pivot = a[l];
    int j = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] <= pivot) {
            j++;
            swap(a[i], a[j]);
        }
    }
    swap(a[l], a[j]);
    return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);   // pick a random number in range from l to r
    swap(a[l], a[k]);
    int m = partition2(a, l, r);

    randomized_quick_sort(a, l, m - 1);
    randomized_quick_sort(a, m + 1, r);
}



twoIndices partition3(vector<int> &a, int l, int r){
    // first perform a regular partition, m2 is the index of the rightmost element equal to pivot
    int pivot = a[l];

    int m2 = l;
    for (int i = l+1; i <= r; i++){
        if (a[i] <= pivot){
            m2++;
            swap(a[i], a[m2]);
        }
    }
    swap(a[l], a[m2]);

    /* Now index m2 is our rightmost pivot. Now we go to the left of m2 and find
     * elements equal to a[m2] to find m1 */
    int m1 = m2;
    for (int i = m2-1; i >= l; i--){
        if (a[i] == pivot){
            m1--;
            swap(a[i], a[m1]);
        }
    }

    twoIndices m1m2;
    m1m2.m1 = m1;
    m1m2.m2 = m2;
    return m1m2;
}


void quick_sort_3(vector<int> &a, int l, int r){
    if(l >= r) return;

    int k = l + rand() % (r - l +1);
    swap(a[l], a[k]);

    twoIndices m1m2 = partition3(a, l, r);

    int m1 = m1m2.m1;
    int m2 = m1m2.m2;

    quick_sort_3(a, l, m1-1);
    quick_sort_3(a, m2+1, r);
}


int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }

    quick_sort_3(a, 0, a.size() - 1);

    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }

    return 0;
}


//    vector<int> a {2, 9, 10, 1, 2, 1, 2, 1, 2, 1, 9, 2, 2, 5, 4, 23, 22};
//    partition3(a, 0 ,a.size()-1);
