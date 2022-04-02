#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct item {
    int id;
    double peso;
    double valor;
};

bool lowestWeightCompare(item a, item b){
    return a.peso < b.peso;
}

int main() {
    int n = 0;
    int W = 0;
    double peso, valor;
    vector<item> mochila;
    vector<item> items;

    cin >> n >> W;
    items.reserve(n); // Reserve memory for "n" elements

    // Get all itens
    for(int i = 0; i < n; i++){
        cin >> peso;
        cin >> valor;
        items.push_back({i, peso, valor});
    }

    // Order itens from value
    sort(items.begin(), items.end(), lowestWeightCompare);

    // Add itens in the backpack
    peso = 0;
    valor = 0;

    for(auto& el : items){
        if(el.peso + peso <= W){
            mochila.push_back(el);
            peso += el.peso;
            valor += el.valor;
        }
    }

    // Order itens selected in crescent way 
    sort(mochila.begin(), mochila.end(), [](auto& i, auto&j){return i.id < j.id;});

    // Pretty print
    if (true) {
        cout << "Peso: "<< peso << " |Valor total: " << valor << " |Heuristica/Busca local(0) ou Otimo global(1): 0" << endl;
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