#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int n;
    std::cout << "Manda um int: " << "\n";
    std::cin >> n;
    std::vector<double> vec;
    for (int i = 0; i < n; i++) {
        double num;
        std::cin >> num;
        vec.push_back(num);
    }

    // Mean
    double mean = 0;
    for (int i = 0; i < n; i++) {
        mean += vec[i];
    }
    mean /= (n);

    // Std deviation
    double stddev = 0;
    for (int i = 0; i < n; i++) {
        stddev += std::pow((vec[i] - mean), 2);
    }
    stddev /= (n);
    stddev = std::sqrt(stddev);

    std::cout << "Média: " << mean << "\n";
    std::cout << "Desvio padrão: " << stddev << "\n";
    
    return 1;
}