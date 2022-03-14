#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<double> vec;
    for (int i = 0; i < n; i++) {
        vec.push_back(i * i);
    }
    std::cout << "Tamanho do vetor: " << vec.size() << "\n";
    std::cout << "Primeiro elemento: " << vec.front() << "\n";
    std::cout << "Último elemento: " << vec.back() << "\n";
    std::cout << "Elemento 3: " << vec[2] << "\n";
    return 1;
}