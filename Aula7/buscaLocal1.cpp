#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;

struct item {
    int id;
    double peso;
    double valor;
};

struct interaction {
    vector<item> mochila;
    int peso;
    int valor;
};

interaction doTest(vector<item> items, int n, int W, default_random_engine generator) {
    interaction trying;
    int i;
    double j;

    random_device rd;
    generator.seed(rd());
    
    trying.peso = 0;
    trying.valor = 0;

    uniform_int_distribution<int> distribution(0, n-1);
    uniform_real_distribution<double> randDouble(0.0, 1.0);

    for(auto& el : items) {
        
        distribution.param(uniform_int_distribution<int>::param_type(0, n-1));
        i = distribution(generator);
        //cout << items[i].id << " " << items[i].peso << " " << items[i].valor;
        j = randDouble(generator);
        // Seleciona o objeto com 50% de chance
        if (j >= 0.5) {
            // Se couber bota na mochila
            if (items[i].peso + trying.peso <= W) {        
                trying.mochila.push_back(items[i]);
                trying.peso += items[i].peso;
                trying.valor += items[i].valor;
                //cout << " added!" << endl;
            } //else cout << " not added!" << endl;
            items.erase(items.begin() + i);
            n -= 1;
        }
        if (trying.peso >= W) break; 
    }

    return trying;
}


int main() {
    
    // n = numero objs, w = peso total da mochila, i = numero sorteado
    int n = 0;
    int W = 0;

    int amostras = 10;
    vector<item> items;
    items.reserve(n);
    double peso, valor;
    interaction actualTry;
    interaction bestTry;

    cin >> n >> W;

    // Cria um gerador aleatorio com seed 10
    default_random_engine generator;
    generator.seed(10);
    uniform_int_distribution<int> distribution(0, n-1);
    
    // Captura cada item individualmente
    for(int i = 0; i < n; i++) {
        cin >> peso;
        cin >> valor;
        items.push_back({i, peso, valor});
    }

    bestTry.valor = 0;

    // Testa o algoritmo por i amostras e pega a melhor iteração
    for (int i = 0; i < amostras; i++) {
        actualTry = doTest(items, n, W, generator);
        if (actualTry.valor > bestTry.valor) bestTry = actualTry;
    }

    // Deixa os itens escolhidos em ordem crescente
    sort(bestTry.mochila.begin(), bestTry.mochila.end(), [](auto& i , auto& j){return i.id < j.id;});

    // Imprime a melhor iteração
    cout << bestTry.peso << " " << bestTry.valor << " 0" << endl;

    for(auto& el: bestTry.mochila) {
        cout << el.id << " ";
    }
    cout << endl;

    return 0;
}