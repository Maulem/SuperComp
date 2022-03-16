// g++ -Wall ex2.cpp -o ex2

#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include <cmath>

int main() {
    int n;
    double s = 0.0;
    std::cin >>n;
    for (int i = 0; i <=n; i++) {
         s += 1 / std::pow(2, i);
    }
    std::cout << std::fixed; // Faz sempre aparecer os valores até 15 casa>
    std::cout << std::setprecision(15) << s << '\n';
    return 0;
}
