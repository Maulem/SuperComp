#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct item
{
    int id;
    double peso;
    double valor;
    
};



double knapSack2(int W, vector<item> items, vector<item>& usados, vector<item>& melhor){
    double valor = 0.0;
    double peso = 0.0;
    double sem_i = 0.0, com_i = 0.0;
    vector<item> items2 = items;

    // Condição de retorno: Sem mais items ou sem espaço na mochila
    if(items.empty() || W == 0)
        return 0;

    // Se o item couber na mochila adiciona ele nos usados e roda recursão
    if(items[0].peso <= W){
        usados.push_back(items[0]);
        valor = items[0].valor;
        peso = items[0].peso;
        items.erase(items.begin());
        com_i = knapSack2(W - peso, items, usados, melhor);
    }
    // Roda recursão sem o elemento em questão
    items2.erase(items2.begin());
    sem_i = knapSack2(W, items2, usados, melhor);


    // Salva os resultados até agora
    double valor_atual = 0.0, valor_melhor = 0.0;
    for(auto& el : usados){
        valor_atual += el.valor;
    }
    for(auto& el : melhor){
        valor_melhor += el.valor;
    }
    if(valor_atual > valor_melhor)
        melhor = usados;
    usados.clear();
    // Retorna o máximo obtido com a recursão até agr
    return max(sem_i, valor + com_i);
    
}

// double knapSack(int W, std::vector<item> items){
//     if(items.empty() || W == 0){
//         return 0;
//     }
//     if(items[0].peso > W){
//         items.erase(items.begin());
//         return knapSack(W,items);
//     }    
//     else {
//         double valor = items[0].valor;
//         double peso = items[0].peso;
       
//         items.erase(items.begin());
//         return max(valor + knapSack(W - peso,items), knapSack(W, items));
//      }
// }

int main() {

    int n = 0;
    int W = 0;

    vector<item> mochila;

    cin >> n >> W; //numero de elementos e peso


    vector<item> items, usado, melhor;

    items.reserve(n);
    usado.reserve(n);
    double peso, valor;

    // Pega os items
    for(int i = 0; i < n; i++) {
        cin >> peso;
        cin >> valor;
        items.push_back({i, peso, valor});
    }
    
    cout << "RESULTADO = " << knapSack2(W, items, usado, melhor) << "\n";
    for(auto& el: melhor) {
            cout << el.id << " ";
    }
    cout << endl;

    return 0;
}