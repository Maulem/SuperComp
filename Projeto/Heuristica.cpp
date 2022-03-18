#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>

int main() {
    // Inicia as variaveis dos DNAs e seus tamanhos
    
    int max_score;
    std::string string_dna_a, string_dna_b;
    std::vector<std::string> dna_a;
    std::vector<std::string> dna_b;
    int size_a, size_b;

    // Le os DNAs inseridos pelo usuario
    std::cin >> string_dna_a;
    std::cin >> string_dna_b;

    // Calcula o tamanho dos DNAs
    size_a = string_dna_a.size();
    size_b = string_dna_b.size();

    // Transfere os DNAs pra vetores pra ficar mais facil manipular
    for(int i = 0; i < size_a; i++){
        dna_a.push_back({string_dna_a[i]});
    }
    for(int i = 0; i < size_b; i++){
        dna_b.push_back({string_dna_b[i]});
    }

    // Printa os DNAs enviados para o usuario conferir
    std::cout << std::endl << "============================================" << std::endl;
    std::cout <<              "               DNAs analisados              " << std::endl;
    std::cout <<              "          Primeiro DNA, tamanho: " << size_a << std::endl;
    std::cout << "      DNA: ";
    for(int i = 0; i < size_a; i++){
        std::cout << dna_a[i];
    }
    std::cout << std::endl;
    std::cout << std::endl << "--------------------------------------------" << std::endl;
    std::cout <<              "           Segundo DNA, tamanho: " << size_b << std::endl;
    std::cout << "      DNA: ";
    for(int i = 0; i < size_b; i++){
        std::cout << dna_b[i];
    }
    std::cout << std::endl;


    return 0;
}
