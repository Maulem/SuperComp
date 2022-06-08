#include <iostream>
#include <vector> 
#include <algorithm>
#include <omp.h>

// Flags de compilação:
// g++ -Wall -fopenmp -O3 BuscaExaustivaParalela.cpp -o BuscaExaustivaParalela
// ./BuscaExaustivaParalela < Sequencias.seq


// Pesos para match, mismatch e gap respectivamente
#define WMAT 2
#define WMIS -1
#define WGAP -1


// Gera uma matriz de inteiros
typedef std::vector<std::vector<int>> matriz;


int smithWaterman(std::string dna_a, std::string dna_b) {

    // Calcula o tamanho das strings 
    int size_a = dna_a.length();
    int size_b = dna_b.length();

    // Inicia uma matriz de pontos chamada H com base no tamanho das sequencias
    matriz H;
    H.resize(size_a + 1);
    for (int x = 0; x <= size_a; x++)
        H[x].resize(size_b + 1);

    // Declara as variaveis usadas no algoritmo
    int diagon, deletion, insertion, wStatus;
    int maxH = 0;

    for (int i = 1; i <=size_a; i++) {
        for (int j = 1; j <= size_b; j++) {
            // Assume que o w é um mismatch ou gap na sequencia
            wStatus = WMIS;
            // Se a letra de ambas as sequencias forem iguais é um Match
            if (dna_a[i-1] == dna_b[j-1]) {
                // Portanto o w vira 2
                wStatus = WMAT;
            }

            // Calcula a diagonal, a deleção e inserção com base no número dos pontos anteriores
            diagon = H[i-1][j-1] + wStatus;
            deletion = H[i-1][j] + WMIS;
            insertion = H[i][j-1] + WMIS;

            // Calcula o máximo entre a diagonal, a deleção e inserção
            H[i][j] = std::max({0, diagon, deletion, insertion});

            // Checa pra ver se esse é o maior H até agora
            if (H[i][j] > maxH) maxH = H[i][j];
        }
    }
    return maxH;
}

// Gera todas as subsequencias a partir de uma sequencia
std::vector<std::string> generateSubsequences(std::string sequence, int size) {
    std::vector<std::string> subseqs_list;
    for (int i = 0; i < size; i++)
        for (int j = 1; j <= size - i; j++)
            subseqs_list.push_back(sequence.substr(i, j));
    return subseqs_list;
}

void printInit(std::string dna_a, int size_a, std::string dna_b, int size_b) {
    std::cout << std::endl
              << "============================================" << std::endl;
    std::cout << "               DNAs analisados              " << std::endl;
    std::cout << "          Primeiro DNA, tamanho: " << size_a << std::endl;
    std::cout << "      DNA a: ";
    for (int i = 0; i < size_a; i++) {
        std::cout << dna_a[i];
    }
    std::cout << std::endl;
    std::cout << std::endl
              << "--------------------------------------------" << std::endl;
    std::cout << "           Segundo DNA, tamanho: " << size_b << std::endl;
    std::cout << "      DNA b: ";
    for (int i = 0; i < size_b; i++) {
        std::cout << dna_b[i];
    }
    std::cout << std::endl;
}

void printEnd(int max_score, double final_time, std::string best_subsequence_a, std::string best_subsequence_b) {
    std::cout << std::endl << "--------------------------------------------";
    std::cout << std::endl << "          Pontuação máxima: " << max_score << std::endl ;

    std::cout << std::endl << "        Melhor subsequencia de A:" << std::endl;
    std::cout << "           ";
    for (auto& el : best_subsequence_a ){
        std::cout << el << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl << "        Melhor subsequencia de B:" << std::endl;
    std::cout << "           ";
    for (auto& el : best_subsequence_b){
        std::cout << el << " ";
    }
    std::cout << std::endl;
    std::cout << "Tempo total: " << final_time;
    std::cout << std::endl;
}

int main() {

    // Declara variaveis usadas
    std::string dna_a, dna_b;
    int size_a, size_b;
    double init_time, final_time;

    // Calcula o tamanho dos DNAs
    std::cin >> dna_a >> dna_b;
    size_a = dna_a.length();
    size_b = dna_b.length();

    // Printa os DNAs enviados para o usuario conferir
    printInit(dna_a, size_a, dna_b, size_b);

    // Inicia a contagem de tempo
    init_time = omp_get_wtime();

    // Gera todas as subsequencias possiveis não nulas dos DNAs A e B
    std::vector<std::string> subseqs_a_list = generateSubsequences(dna_a, size_a);
    std::vector<std::string> subseqs_b_list = generateSubsequences(dna_b, size_b);

    // Gera as variaveis usadas para checar as subsequencias
    std::string best_subsequence_a, best_subsequence_b;
    int score, max_score = 0;

    #pragma omp parallel for reduction(max: max_score)
    // Para cada subsequencia na lista de subsequencias a
    for (auto& subseq_a : subseqs_a_list) {
        // Para cada subsequencia na lista de subsequencias b
        for (auto& subseq_b : subseqs_b_list) {
            score = smithWaterman(subseq_a, subseq_b);
            if (score > max_score) {
                max_score = score;
                best_subsequence_a = subseq_a;
                best_subsequence_b = subseq_b;
            }
            // Zera o score
            score = 0;
        }
    }

    final_time = omp_get_wtime() - init_time;

    // Imprime a máxima pontuação e suas subsequencias
    printEnd(max_score, final_time, best_subsequence_a, best_subsequence_b);

    return 0;
}