#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>      // std::setprecision

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

    for (int i = 0; i < n; i++) {
        std::vector<double> linha;
        for (int j = 0; j < n; j++) {
            double DX = matriz[j][0] - matriz[i][0];
            double DY = matriz[j][1] - matriz[i][1];
            linha.push_back(std::sqrt(DX*DX + DY*DY));
        }
        ansmatriz.push_back(linha);
    }

    std::cout << "Matriz saida: " << "\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setprecision(2) << std::fixed << ansmatriz[i][j] << "  ";
        }
        std::cout << "\n";
    }
    
    return 1;
}