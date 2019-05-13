#include <iostream>


long long paisano_period(long long m){
    long long previous = 0, current = 1;
    for (long long i=0; i<m*m; i++){
        long long int tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%m;
        if(previous==0 && current==1) return i+1;
    }
}


int get_fibonacci_huge_modulo(long long n, long long m) {
    long long int period = paisano_period(m);
    long long int remainder = n%period;

    if (remainder<=1) return remainder;

    long long int previous = 0;
    long long int current = 1;

    for (long long int i=0; i<remainder-1; ++i){
        long long int tmp_previous = previous;
        previous = current;
        current = (tmp_previous+current)%m;
    }

    return current;

}


int fibonacci_sum(long long int n) {
    if(n<=1) return n;
    int ans = get_fibonacci_huge_modulo(n+2, 10)-1;
    if (ans < 0) ans = 10+ans;
    return ans;
}


int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum(n) << '\n';
    return 0;
}
