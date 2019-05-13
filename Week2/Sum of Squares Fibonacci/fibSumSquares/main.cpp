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


// (f1)^2 + ... + (fn)^2 = fn * (fn + f(n-1))
int fibonacci_sum_squares(long long n){
    if (n<=1) return n;
    int fn = get_fibonacci_huge_modulo(n, 10);
    int fn_minus_1 = get_fibonacci_huge_modulo(n-1, 10);
    return ( fn*(fn + fn_minus_1) )%10;

}


int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares(n) << '\n';
    return 0;
}
