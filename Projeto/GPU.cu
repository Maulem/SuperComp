%%writefile GPU.cu

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <cstdlib>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/reduce.h>
#include <thrust/fill.h>

using namespace std;
using namespace std::chrono;

struct subsequenceIndex {
    int start;
    int end;
};

std::vector<subsequenceIndex> generateSubsequences(int max_size) {
    vector<subsequenceIndex> indexes;
    subsequenceIndex index;

    for(int i = 0; i < max_size; i++) {
        for(int j = 1; j <= max_size; j++) {
            index.start = i;
            index.end = j;
            if (i < j)
                indexes.push_back(index);
        }
    }
    return indexes;
}


struct nucleobaseMatch{
    __host__ __device__
    int operator()(const char& dna_a, const char& dna_b) {
        if (dna_a != 'A' && dna_a != 'T' && dna_a != 'C' && dna_a != 'G' && dna_a != '-') {
            return 0;
        }
        if (dna_b != 'A' && dna_b != 'T' && dna_b != 'C' && dna_b != 'G' && dna_b != '-') {
            return 0;
        }
        if (dna_a == dna_b) {
            return 2;
        }
        return -1;
    }
};

int main() {

    // Declara as variaveis de contagem de tempo
    steady_clock::time_point init_time, final_time;

    // Inicia a contagem de tempo
    init_time = steady_clock::now();
    
    // Declara as variaveis usadas
    std::string dna_a, dna_b;
    int size_a, size_b;
    
    // Recebe e calcula o tamanho dos DNAs
    std::cin >> dna_a >> dna_b;
    size_a = dna_a.length();
    size_b = dna_b.length();

    // Gera as variaveis usadas pra checar as subsequencias
    int score = 0, max_score = 0;
    int min_size = min(size_a,size_b);
    int max_size = max(size_a,size_b);

    // Gera as subsequencias possiveis diferentes de 0
    std::vector<subsequenceIndex> smaller_index_list = generateSubsequences(min_size), bigger_index_list = generateSubsequences(max_size);

    // Cria os vetores que vao ser usados na GPU
    thrust::device_vector<char> smaller_gpu(min_size), bigger_gpu(max_size);

    // Salva a menor string no menor vetor da GPU
    for(int i = 0; i < min_size; i++) {
        if (size_a < size_b) {
            smaller_gpu[i] = dna_a[i];
        }
        else {
            smaller_gpu[i] = dna_b[i];
        }
        //cout << smaller_gpu[i];
    }
    //cout << endl;

    // Salva a maior string no maior vetor da GPU
    for(int i = 0; i < max_size; i++) {
        if (size_a > size_b) {
            bigger_gpu[i] = dna_a[i];
        }
        else {
            bigger_gpu[i] = dna_b[i];
        }
        //cout << bigger_gpu[i];
    }
    //cout << endl;

    // Varre todos os indices
    for (auto& small_index : smaller_index_list) {
        for(auto& big_index : bigger_index_list) {
            // Se os indices nao tem o mesmo tamanho descarta fora 
            if (small_index.end - small_index.start == big_index.end - big_index.start) {
                // Cria o vetor que vai receber a pontuacao da comparacao de duas sequencias com o menor tamanho do menor indice
                thrust::device_vector<char> sequence_score(small_index.end);

                // Compara 2 vetores usando uma operacao e salva no vetor final os resultados
                thrust::transform(
                    smaller_gpu.begin() + small_index.start,    // Inicio vetor 1
                    smaller_gpu.end() + small_index.end,        // Fim vetor 1
                    bigger_gpu.begin() + big_index.start,       // Inicio vetor 2
                    sequence_score.begin(),                     // Inicio vetor final
                    nucleobaseMatch()                           // Operacao a ser feita
                );
                
                // Calcula o tamanho da menor subsequencia
                int dif = small_index.end - small_index.start;

                // Soma os valores do vetor comecando no inicio ate o tamanho da menor subsequencia
                score = thrust::reduce(sequence_score.begin(), sequence_score.begin() + dif, score, thrust::plus<int>());

                // Atualiza a novo pontuacao maxima
                if (max_score < score) {
                    // cout << "----------------------------------------" << endl;
                    // cout << small_index.start << " " << small_index.end << endl;
                    // for(int i = small_index.start; i < small_index.end; i++) {
                    //     cout << smaller_gpu[i];
                    // }
                    // cout << endl;
                    // cout << big_index.start << " " << big_index.end << endl;
                    // for(int i = big_index.start; i < big_index.end; i++) {
                    //     cout << bigger_gpu[i];
                    // }
                    // cout << endl;
                    // for (int i = 0; i < dif; i++) {
                    //     cout << (int)sequence_score[i];
                    // }
                    // cout << endl;
                    // cout << score << endl;
                    // cout << "----------------------------------------" << endl;
                    max_score = score;
                }
                // Zera o score por precaucao
                score = 0;
            }
        }
    }
    
    // Para a contagem de tempo
    final_time = steady_clock::now();

    // Printa os tamanhos das sequencias
    std::cout << size_a << std::endl;
    std::cout << size_b << std::endl;

    // Printa a duracao
    auto ms = duration_cast<milliseconds>(final_time - init_time);
    std::cout << (double)ms.count() / 1000 << std::endl;

    //std::cout << "Score: " << max_score << endl;

    return 0;
}