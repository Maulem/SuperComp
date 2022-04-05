#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>      // std::setprecision

// ATENÇÃO: COMPILE MANUALMENTE PRA USAR O VALGRIND
// g++ -Wall -O3 -g ex2.cpp -o ex2
// valgrind --tool=callgrind ./ex2 < ex2.txt
// callgrind_annotate callgrind.out.ex2 ex2.cpp
// kcachegrind callgrind.out.4588(pid aqui)

void calcDistancias(int n, std::vector<std::vector<double>> &matriz, std::vector<std::vector<double>> &ansmatriz) {
    for (int i = 0; i < n; i++) {
        std::vector<double> linha;
        for (int j = 0; j < n; j++) {
            if (i <= j) {
                double DX = matriz[j][0] - matriz[i][0];
                double DY = matriz[j][1] - matriz[i][1];
                linha.push_back(std::sqrt(DX*DX + DY*DY));
            }
            else {
                linha.push_back(0);
            }
            
        }
        ansmatriz.push_back(linha);
    }
}

int main() {
    int n;
    std::cout << "Numero de pontos: ";
    std::cin >> n;
    std::cout << "\n";

    std::vector<std::vector<double>> matriz;
    for (int i = 0; i < n; i++) {
        std::vector<double> linha;
        double x, y;

        std::cout << "X: ";
        std::cin >> x;
        std::cout << "\n";

        std::cout << "Y: ";
        std::cin >> y;
        std::cout << "\n";

        linha.push_back(x);
        linha.push_back(y);
        matriz.push_back(linha);
    }

    std::cout << "Matriz entrada: " << "\n";

    for (int i = 0; i < n; i++) {
        std::cout << std::setprecision(2) << std::fixed << matriz[i][0] << "  ";
        std::cout << std::setprecision(2) << std::fixed << matriz[i][1] << "\n";
    }
    
    // Calculo da distancia
    std::vector<std::vector<double>> ansmatriz;
    calcDistancias(n, matriz, ansmatriz);

    std::cout << "Matriz saida: " << "\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setprecision(2) << std::fixed << ansmatriz[i][j] << "  ";
        }
        std::cout << "\n";
    }
    
    return 1;
}