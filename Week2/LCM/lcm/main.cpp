#include <iostream>

long long int gcd_fast(long long int a, long long int b){
    if (a==0) return b;
    if (b==0) return a;

    if (a>b){
        int remainder = a%b;
        return gcd_fast(b, remainder);
    }

    if (a<b){
        int remainder = b%a;
        return gcd_fast(a, remainder);
    }
}


long long int lcm (long long int a, long long int b){
    if (a==b) return a;
    long long int product = a*b;
    long long int gcd = gcd_fast(a, b);
    return product/gcd;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm(a, b) << std::endl;
  return 0;
}
