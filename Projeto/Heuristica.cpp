#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


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

int smithWaterman(std::vector<std::string> dna_a, std::vector<std::string> dna_b, int size_a, int size_b){

    // Inicia uma matriz de pontos chamada H com base no tamanho das sequencias
    point H[size_a+1][size_b+1];
    

    // Zera a primeira coluna
    for (int i = 1; i <= size_a; i++) {
        H[i][0].number = 0;
    }
    // Zera a primeira linha
    for (int j = 0; j <= size_b; j++) {
        H[0][j].number = 0;
    }


    // Declara as variaveis usadas no algoritmo
    int diagon, deletion, insertion, wStatus;

    // Cria um ponto pra saber qual o ponto máximo
    point maxPoint;
    maxPoint.number = 0;

    // Percorre toda a matriz H calculando seus valores
    for (int i = 1; i <= size_a; i++) {
        for (int j = 1; j <= size_b; j++) {
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


    // Imprime a matriz de saida depois de aplicado o algoritmo
    std::cout << std::endl << "--------------------------------------------" << std::endl;
    std::cout <<              "              Matriz de saida               " << std::endl;
    std::cout << std::endl;

    // Inicia em -2 para poder imprimir a sequencia de DNA b e uma linha em branco na matriz
    for (int i = -2; i <= size_a; i++){
        // Imprime coisas diferentes dependendo de cada linha
        switch (i) {
            case -2:
                // Linha com DNA b
                std::cout << "         ";
                break;
            case -1:
                // Linha em branco
                break;
            case  0:
                // Linha da matriz só de zeros
                std::cout << "       ";
                break;
            default:
                // Imprime as letras do DNA a na vertical e o resto das linhas
                std::cout << "    " << dna_a[i-1] << "  ";
                break;
        }

        // Imprime cada linha
        for (int j = 0; j <= size_b; j++){
            // Imprime coisas diferentes dependendo de cada linha
            switch (i) {
                case -2:
                    // Primeira linha com o DNA b
                    if (j < size_b) {
                        std::cout << "  " << dna_b[j];
                    }
                    break;
                case -1:
                    // Linha vazia
                    break;
                default:
                    // Para alinhamento se o número for menor que 10 imprime um espaço na frente
                    if (H[i][j].number <= 9) {
                        std::cout << " " << H[i][j].number << " ";
                    }
                    else {
                        std::cout << H[i][j].number << " ";
                    }
            }
        }
        std::cout << std::endl;
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

    // Imprime os DNAs reconstruidos
    std::cout << std::endl << "--------------------------------------------" << std::endl;
    std::cout <<              "            DNAs reconstruidos:             " << std::endl;
    std::cout << "      DNA a: ";
    for(int i = 0; i < seq_dna_a.size(); i++){
        std::cout << seq_dna_a[i];
    }
    std::cout << std::endl;
    std::cout << "      DNA b: ";
    for(int i = 0; i < seq_dna_b.size(); i++){
        std::cout << seq_dna_b[i];
    }

    return maxPoint.number;
}

int main() {

    // Inicia as variaveis dos DNAs e seus tamanhos
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
    std::cout << "      DNA a: ";
    for(int i = 0; i < size_a; i++){
        std::cout << dna_a[i];
    }
    std::cout << std::endl;
    std::cout << std::endl << "--------------------------------------------" << std::endl;
    std::cout <<              "           Segundo DNA, tamanho: " << size_b << std::endl;
    std::cout << "      DNA b: ";
    for(int i = 0; i < size_b; i++){
        std::cout << dna_b[i];
    }
    std::cout << std::endl;

    // Usa o algoritimo Smith-Waterman para calcular as sequencias 
    int score = smithWaterman(dna_a, dna_b, size_a, size_b);

    // Imprime a máxima pontuação
    std::cout << std::endl << "--------------------------------------------" << std::endl;
    std::cout << std::endl << "           Pontuação máxima:" << score << std::endl << std::endl;

    return 0;
}
