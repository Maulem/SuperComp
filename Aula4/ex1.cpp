#include <iostream>
#include <algorithm>

// ATENÇÃO: COMPILE MANUALMENTE PRA USAR O VALGRIND
// g++ -Wall -O3 -g ex1.cpp -o ex1
// valgrind --tool=callgrind ./ex1
// callgrind_annotate callgrind.out.ex1 ex1.cpp

constexpr int M = 2048;
constexpr int N = 2048;

double naive_sum(const double a[][N]){
    double sum = 0.0;
    for(int j = 0; j < N; ++j) {
        for(int i = 0; i < M; ++i)
            sum += a[i][j];
    }
    return sum;
}

double improved_sum(const double a[][N]) {
    double sum = 0.0;
    for(int i = 0; i < M; ++i)
        for(int j = 0; j < N; ++j)
            sum +=a[i][j];
    return sum;
}

int main() {
    static double a[M][N];
    std::fill_n(&a[0][0], M*N, 1.0 / (M*N));
    std::cout << naive_sum(a) << std::endl;
    static double b[M][N];
    std::fill_n(&b[0][0], M*N, 1.0 / (M*N));
    std::cout << improved_sum(b) << std::endl;
    return 0;
}