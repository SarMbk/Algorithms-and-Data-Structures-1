#include <iostream>
using namespace std;

long long int gcd_fast(long long int a, long long int b){
    if (a==0) return b;
    if (b==0) return a;

    if (a>b){
        long long int remainder = a%b;
        return gcd_fast(b, remainder);
    }

    if (a<b){
        long long int remainder = b%a;
        return gcd_fast(a, remainder);
    }
}

int main() {
  long long int a, b;
  std::cin >> a >> b;
  std::cout << gcd_fast(a, b) << std::endl;
  return 0;
}
