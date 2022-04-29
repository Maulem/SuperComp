#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>

// Flags de compilação:
// g++ -Wall -O3 BuscaLocal.cpp -o BuscaLocal
// ./BuscaLocal < Sequencias.seq

// Seed utilizada pelo gerador de números aleatorios
#define SEED 10

// Pesos para match, mismatch e gap respectivamente
#define WMAT 2
#define WMIS -1
#define WGAP -1

// Máximo de subsequencias geradas por vez
#define SUBSEQUENCES_P_MAX 100

// Numero de vezes que vai tentar melhorar o resultado
#define RUNTIMES 100

// Cria a random engine generator
std::default_random_engine generator(SEED);

/*
    Struct de cada grupo de subsequencias "a" e "b" correspondentes
    incluindo o score entre elas. 
*/
struct subsequenceGroup {
    int score;
    std::vector<std::string> subsequence_a;
    std::vector<std::string> subsequence_b;
};

subsequenceGroup buscaLocal(std::vector<std::string> dna_a, std::vector<std::string> dna_b, int size_a, int size_b) {

    /*
        Declara as variaveis que serão usadas na busca local, sendo k um número
        aleatório menor que o tamanho das sequencias usado pra calcular o tamanho
        das subsequencias, sendo p um número aleatorio de sequencias que serão 
        criadas menor que SUBSEQUENCES_P_MAX, sendo i o número aleatorio por onde
        a subsequencia de a vai iniciar e por fim j o número aleatorio por onde
        a subsequencia de b vai iniciar, o max_k só não deixa k > tamanhos das seqs.
    */
    int k, p, i = 0, j = 0, max_k = 0, score, max_score = 0;;

    // Impede que o k gerado seja maior que o tamanho da maior das sequencias
    size_a < size_b ? max_k = size_a: max_k = size_b;

    // Declara as subsequencias e a lista de subsequencias de "a" a ser gerada 
    std::vector<std::string> subsequence_a, subsequence_b;
    std::vector<std::vector<std::string>> subsequence_a_list;

    // Declara a melhor subsequencia dessa iteração
    subsequenceGroup subsequence;

    // Define que o k deve ser entre 1 e max_k
    std::uniform_int_distribution<int> random_k(1, max_k);
    
    // Gera o k
    k = random_k(generator);
    
    // Define que o i e o j devem ser menores que os tamanhos menos k
    std::uniform_int_distribution<int> random_i(0, size_a - k);
    std::uniform_int_distribution<int> random_j(0, size_b - k);

    // Define que o numero de sequencias deve ser entre 1 e SUBSEQUENCES_P_MAX
    std::uniform_int_distribution<int> random_p(1, SUBSEQUENCES_P_MAX);

    // Gera o "j" e o "p"
    j = random_j(generator);
    p = random_p(generator);
    
    // Reserva espaço na memoria para alocar as subsequencias
    subsequence_a.reserve(k);
    subsequence_b.reserve(k);

    // Gera uma subsequencia de "b"
    for (int n = j; n < j + k; n++) {
        subsequence_b.push_back(dna_b[n]);
    }
    
    // Gera p subsequencias de "a"
    for (int n = 0; n < p; n++) {
        // Limpa o vetor para anotar a proxima subsequencia
        subsequence_a.clear();
        // Gera um novo i de inicio por onde a sequencia vai iniciar
        i = random_i(generator);
        // Gera a subsequencia de "a"
        for (int m = i; m < k + i; m++) {
            subsequence_a.push_back(dna_a[m]);
        }
        // Anota a subsequencia na lista de subsequencias
        subsequence_a_list.push_back(subsequence_a);
    }
    // Para cada subsequencia na lista de subsequencias
    for (auto &subsequence_a : subsequence_a_list) {
        // Zera a pontuação
        score = 0;
        // Calcula o score dessa subsequencia de b
        for (int i = 0; i < k; i++) {
            // Deu match
            if (subsequence_a[i] == subsequence_b[i])      score += WMAT;
            // Deu mismatch
            else if (subsequence_a[i] != subsequence_b[i]) score += WMIS;
            // Deu gap
            else                                           score += WGAP; 
        }
        // Checa se essa subsequencia foi a melhor até agora
        if (score > max_score) {
            max_score = score;
            subsequence.subsequence_a = subsequence_a;
        }
    }

    // Adciona o score e a subsequencia b no objeto de saida
    subsequence.score = max_score;
    subsequence.subsequence_b = subsequence_b;

    // Printa as melhores subsequencias dessa iteração
    std::cout << std::endl << "++++++++++++++++++++++++++++++++++++++++++++"   << std::endl;
    std::cout              << "                k: " << k << " | " << "p: "<< p << std::endl;
    std::cout              << "   Melhores subsequencias dessa iteração:   "   << std::endl;
    std::cout << std::endl;
    std::cout << "      DNA a: ";

    // For melhorado: para cada elemento de best_subsequence_a faz uma ação (imprime cada letra)
    for (auto &element : subsequence.subsequence_a) {
        std::cout << element;
    }
    std::cout << std::endl << std::endl;
    std::cout << "      DNA b: ";

    // For melhorado: para cada elemento de subsequence_b faz uma ação (imprime cada letra)
    for (auto &element : subsequence_b) {
        std::cout << element;
    }
    std::cout << std::endl;
    

    return subsequence;
}

int main() {

    // Inicia as variaveis dos DNAs e seus tamanhos
    std::string string_dna_a, string_dna_b;
    std::vector<std::string> dna_a;
    std::vector<std::string> dna_b;
    int size_a, size_b;

    // Lê os DNAs inseridos pelo usuario
    std::cin >> string_dna_a;
    std::cin >> string_dna_b;

    // Calcula o tamanho dos DNAs
    size_a = string_dna_a.size();
    size_b = string_dna_b.size();

    // Transfere os DNAs pra vetores pra ficar mais facil manipular
    for (int i = 0; i < size_a; i++) {
        dna_a.push_back({string_dna_a[i]});
    }
    for (int i = 0; i < size_b; i++) {
        dna_b.push_back({string_dna_b[i]});
    }

    // Printa os DNAs enviados para o usuario conferir
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

    // Inicia as variaveis a serem usadas na busca local
    subsequenceGroup best_exec;
    int  best_score = 0;
    std::vector<int> score_list;
    std::vector<std::string> best_dna_a, best_dna_b;

    // Executa a busca local pelo número de vezes definido em RUNTIMES e salva a melhor sequencia
    for (int exec = 1; exec <= RUNTIMES; exec++) {
        best_exec = buscaLocal(dna_a, dna_b, size_a, size_b);
        if (best_exec.score > best_score) {
            best_score = best_exec.score;
            best_dna_a = best_exec.subsequence_a;
            best_dna_b = best_exec.subsequence_b;
        }
        score_list.push_back(best_exec.score);
    }

    // Imprime a máxima pontuação
    std::cout << std::endl << "--------------------------------------------" << std::endl;
    std::cout << std::endl << "            Pontuação máxima: " << best_score << std::endl << std::endl;
    
    // Imprime as melhores subsequencias do DNA a e b respectivamente
    std::cout << "    Melhor subsequência do primeiro DNA:" << std::endl;
    std::cout << "      DNA a: ";

    // For melhorado: para cada elemento de best_dna_a faz uma ação (imprime cada letra)
    for (auto &element : best_dna_a) {
        std::cout << element;
    }
    std::cout << std::endl << std::endl;

    std::cout << "  Subsequência equivalente do segundo DNA:" << std::endl;
    std::cout << "      DNA b: ";

    // For melhorado: para cada elemento de best_dna_b faz uma ação (imprime cada letra)
    for (auto &element : best_dna_b) {
        std::cout << element;
    }
    std::cout << std::endl << std::endl;

    return 0;
}