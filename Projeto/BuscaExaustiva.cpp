#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// Flags de compilação:
// g++ -Wall -O3 BuscaExaustiva.cpp -o BuscaExaustiva
// ./BuscaExaustiva < Sequencias.seq


// Pesos para match, mismatch e gap respectivamente
#define WMAT 2
#define WMIS -1
#define WGAP -1

/*
    Struct de cada grupo de subsequencias "a" e "b" correspondentes
    incluindo o score entre elas. 
*/
struct subsequenceGroup {
    int score;
    std::vector<std::string> subsequence_a;
    std::vector<std::string> subsequence_b;
};

/*
    Struct de cada ponto da matriz final, tendo um número
    com o seu valor, e suas origens (se seu salto veio da
    diagonal, de cima ou da esquerda)
*/
struct point {
    int number;
    int iJump;
    int jJump;
};

// Gera todas as subsequencias a partir de uma sequencia
void generateSubsequences(std::vector<std::string> sequence, std::vector<std::vector<std::string>> &subseqs_list) {

    std::vector<std::string> subsequence;

    for(int i = 0; i <= int(sequence.size()); i++) {
        for(int j = 1; j <= int(sequence.size()); j++) {
            subsequence.clear();
            for (int k = i; k < j; k++){
                subsequence.push_back(sequence[k]);
            }
            if (subsequence.size() > 0) subseqs_list.push_back(subsequence);
        }
    }
}

// Compara duas sequencias iguais e retorna o Score delas
int scoreEqualSequences(std::vector<std::string> sequence_a, std::vector<std::string> sequence_b) {
    int score = 0; 
    std::vector<std::string> melhor_subseq_a, melhor_subseq_b;
    for (int i = 0; i < (int)sequence_a.size(); i++) {

        // Caso seja um Match
        if (sequence_a[i] == sequence_b[i]) score += WMAT;

        // Caso seja um Mismatch
        else if (sequence_a[i] != sequence_b[i]) score += WMIS;

        // Caso seja um Gap
        else score += WGAP;
    }  
    return score;
}

point max(int diagon, int deletion, int insertion){

    // Cria um ponto local em que será calculado o máximo
    point local;

    // Calcula o máximo entre a diagonal, a deleção e inserção
    int max = std::max({0, diagon, deletion, insertion});
    
    // Salva o máximo no ponto local
    local.number = max;

    // Se a diagonal foi o máximo
    if (diagon == max) {
        // Salta na diagonal
        local.iJump = 1;
        local.jJump = 1;
    }
    // Se a deleção foi o máximo
    else if (deletion == max) {
        // Salta pra baixo
        local.iJump = 1;
        local.jJump = 0;
    }
    // Se a inserção foi o máximo
    else if (insertion == max) {
        // Salta pra direita
        local.iJump = 0;
        local.jJump = 1;
    }

    // Retorna o ponto a ser inserido na matriz final
    return local;
}

int smithWaterman(std::vector<std::string> dna_a, std::vector<std::string> dna_b, subsequenceGroup &smith_waterman_result) {

    // Inicia uma matriz de pontos chamada H com base no tamanho das sequencias
    point H[(int)dna_a.size() + 1][(int)dna_b.size() + 1];

    // Zera a primeira coluna
    for (int i = 1; i <= (int)dna_a.size(); i++) {
        H[i][0].number = 0;
    }
    // Zera a primeira linha
    for (int j = 0; j <= (int)dna_b.size(); j++) {
        H[0][j].number = 0;
    }

    // Declara as variaveis usadas no algoritmo
    int diagon, deletion, insertion, wStatus;

    // Cria um ponto pra saber qual o ponto máximo
    point maxPoint;
    maxPoint.number = 0;
    maxPoint.iJump  = 0;
    maxPoint.jJump  = 0;

    // Percorre toda a matriz H calculando seus valores
    for (int i = 1; i <= (int)dna_a.size(); i++) {
        for (int j = 1; j <= (int)dna_b.size(); j++) {
            // Assume que o w é um mismatch ou gap na sequencia
            wStatus = -1;
            // Se a letra de ambas as sequencias forem iguais é um Match
            if (dna_a[i-1] == dna_b[j-1]) {
                // Portanto o w vira 2
                wStatus = 2;
            }

            // Calcula a diagonal, a deleção e inserção com base no número dos pontos anteriores
            diagon = H[i-1][j-1].number + wStatus;
            deletion = H[i-1][j].number - 1;
            insertion = H[i][j-1].number - 1;

            // Calcula quem é o máximo valor entre a diagonal, a deleção e inserção e salva o ponto atual
            H[i][j] = max(diagon, deletion, insertion);

            // Checa pra ver se esse é o maior número de um ponto até agora
            if (H[i][j].number > maxPoint.number) {
                // Se for o maior salva no maxPoint uma copia do ponto
                maxPoint.number = H[i][j].number;
                maxPoint.iJump  = i;
                maxPoint.jJump  = j;
            }
        }
    }

    // Vetores em que será guardado as sequencias de DNA com base na matriz criada
    std::vector<std::string> seq_dna_a;
    std::vector<std::string> seq_dna_b;

    // O inicio será pela posição do ponto de máximo valor na matriz
    int i = maxPoint.iJump, j = maxPoint.jJump;


    // Enquanto não voltar ao ponto (0,0) e o ponto analisado tiver origens
    while ((i > 0 && j > 0) && (!(H[i][j].jJump == 0 && H[i][j].iJump == 0))) {
        // Anota o ponto atual
        int iActual = i, jActual = j;

        // Se chegar em alguma parede ou sequencia nada a ver para
        if (H[i][j].number == 0) {
            break;
        }
        // Caso de deleção (veio de cima para baixo)
        if (H[iActual][jActual].iJump == 0 && H[iActual][jActual].jJump == 1) {
            seq_dna_a.push_back("_");
            seq_dna_b.push_back(dna_b[j-1]);
        }
        // Caso de inserção (veio da esquerda para direita)
        else if (H[iActual][jActual].iJump == 1 && H[iActual][jActual].jJump == 0) {
            seq_dna_a.push_back(dna_a[i-1]);
            seq_dna_b.push_back("_");
        }
        // Caso da diagonal (normal)
        else {
            seq_dna_a.push_back(dna_a[i-1]);
            seq_dna_b.push_back(dna_b[j-1]);
        }
        
        // Volta na direção que o ponto atual veio
        i = i - H[iActual][jActual].iJump;
        j = j - H[iActual][jActual].jJump;
    }

    // Como as sequencias são feitas de trás pra frente é necessario inverte-las
    std::reverse(seq_dna_a.begin(),seq_dna_a.end());
    std::reverse(seq_dna_b.begin(),seq_dna_b.end());

    smith_waterman_result.score = maxPoint.number;
    smith_waterman_result.subsequence_a = seq_dna_a;
    smith_waterman_result.subsequence_b = seq_dna_b;

    return maxPoint.number;
}


int main() {
    
    // Declara variaveis usadas
    std::string string_dna_a, string_dna_b;
    std::vector<std::string> dna_a;
    std::vector<std::string> dna_b;
    std::vector<std::vector<std::string>> subseqs_a_list;
    std::vector<std::vector<std::string>> subseqs_b_list;
    int size_a, size_b;

    // Le os DNAs inseridos pelo usuario
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


    // Gera todas as subsequencias possiveis dos DNAs A e B
    generateSubsequences(dna_a, subseqs_a_list);
    generateSubsequences(dna_b, subseqs_b_list);

    // Gera as variaveis usadas para checar as subsequencias
    subsequenceGroup best_result, smith_waterman_result;
    std::vector<std::string> best_local_subseq_a, best_local_subseq_b;
    int score, max_score = 0;
    
    // Para cada subsequencia na lista de subsequencias a
    for (auto& subseq_a : subseqs_a_list) {
        // Para cada subsequencia na lista de subsequencias b
        for (auto& subseq_b : subseqs_b_list) {
            best_local_subseq_a.clear();
            best_local_subseq_b.clear();
            // Quando as subsequencias tem tamanhos iguais compara cada base entre si
            if ((int)subseq_a.size() == (int)subseq_b.size()){
                score = scoreEqualSequences(subseq_a, subseq_b);
                best_local_subseq_a = subseq_a;
                best_local_subseq_b = subseq_b;
            }
            // Quando as subsequencias tem tamanhos diferentes faz Smith Waterman
            else{
                score = smithWaterman(subseq_a, subseq_b, smith_waterman_result);
                best_local_subseq_a = smith_waterman_result.subsequence_a;
                best_local_subseq_b = smith_waterman_result.subsequence_b;
            }
            // Salva novo score máximo se tiver
            if (score > max_score){
                max_score = score;
                best_result.score = max_score;
                best_result.subsequence_a = best_local_subseq_a;
                best_result.subsequence_b = best_local_subseq_b;
            }
        }
    }
    

    // Imprime a máxima pontuação e suas subsequencias
    std::cout << std::endl << "--------------------------------------------";
    std::cout << std::endl << "          Pontuação máxima: " << best_result.score << std::endl ;

    std::cout << std::endl << "        Melhor subsequencia de A:" << std::endl;
    std::cout << "           ";
    for (auto& el : best_result.subsequence_a ){
        std::cout << el << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl << "        Melhor subsequencia de B:" << std::endl;
    std::cout << "           ";
    for (auto& el : best_result.subsequence_b){
        std::cout << el << " ";
    }
    std::cout << std::endl;

    return 0;
}