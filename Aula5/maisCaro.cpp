#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct item {
    int id;
    double peso;
    double valor;
};

bool highestValueCompare(item a, item b){
    return b.valor < a.valor;
}

int main() {
    // Número de elementos
    int n = 0;
    // Peso máximo da mochila
    int W = 0;
    // Peso e valor de cada item individual
    double peso, valor;
    // Vetor da mochila final
    vector<item> mochila;
    // Vetor dos items iniciais
    vector<item> items;
    // Captura o número e o peso máximo da mochila
    cin >> n >> W;
    // Reserva a memoria pra n elementos
    items.reserve(n);

    // Captura todos os itens
    for(int i = 0; i < n; i++){
        cin >> peso;
        cin >> valor;
        items.push_back({i, peso, valor});
    }

    // Ordena os itens com base no valor
    sort(items.begin(), items.end(), highestValueCompare);

    // Zera o peso e o valor pra usar na mochila
    peso = 0;
    valor = 0;
    // Adiciona itens sem estourar o peso da mochila
    for(auto& el : items){
        if(el.peso + peso <= W){
            mochila.push_back(el);
            peso += el.peso;
            valor += el.valor;
        }
    }

    // Ordena os itens em ordem crescente
    sort(mochila.begin(), mochila.end(), [](auto& i, auto&j){return i.id < j.id;});

    // Pretty print
    if (true) {
        cout << "Peso: "<< peso << " | Valor total: " << valor << " | Heuristica/Busca local(0) ou Otimo global(1): 0" << endl;
        for(auto& el: mochila){
            cout << "|Item id: " << el.id << " ";
        }
        cout << "|" << endl;
    }

    // Regular print
    if (false) {
        cout << peso << " " << valor << " 0" << endl;
        for(auto& el: mochila){
            cout << el.id << " ";
        }
    }
    
    return 0;
}