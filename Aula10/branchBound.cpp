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

int num_leaf=0, num_copy=0; // variáveis inicializadas como zero aqui para serem globais. num_leaf: toda vez que chegássemos a uma solução completa (final de recursão). num_copy faz algo semelhante, mas toda vez que comparar a solução atual com a melhor possível (num_leaf), se for melhor, soma mais um. Ver linha L67 para entender os comentários explicando o funcionamento dessas duas variáveis

bool my_compare(item a, item b){
    return b.valor < a.valor; // ordenando pelo mais caro
}

double knapSack2(int W, vector<item> items, vector<item>& usados, vector<item>& melhor){
    double valor = 0.0;
    double peso = 0.0;
    double sem_i = 0.0, com_i = 0.0;
    vector<item> items2 = items;
    //sort(items.begin(), items.end(), my_compare);
    if(items.empty() || W == 0)
        return 0;
    else {
        // Vamos calcular inicialmente o valor_atual, valor_melhor e o bound para saber se continuamos ou não
        
        double valor_atual = 0.0, valor_melhor = 0.0, bound = 0.0;
        
        for(auto& el : usados){
            valor_atual += el.valor; //nova solução
        }
        
        for(auto& el : melhor){
            valor_melhor += el.valor; //melhor que tivemos até agora
        }
        
        for(auto& el: items)
            bound+=el.valor; //soma todo mundo que não está na mochila
            
            
        // se o valor atual + bound <= valor_melhor, não conseguiremos melhorar o valor_melhor
        
        if (valor_atual+bound<=valor_melhor)  
           return 0;
        
        // se o valor_atual + bound tem chance de melhorar
        if(items[0].peso <= W){
            usados.push_back(items[0]);
            valor = items[0].valor;
            peso = items[0].peso;
            items.erase(items.begin());
            com_i = knapSack2(W - peso, items, usados, melhor);
        }
        items2.erase(items2.begin());
        sem_i = knapSack2(W, items2, usados, melhor);
        
        valor_atual = 0.0;
        valor_melhor = 0.0;
        
        for(auto& el : usados){
            valor_atual += el.valor;
        }
        for(auto& el : melhor){
            valor_melhor += el.valor;
        }
    
        num_leaf++;
        if(valor_atual > valor_melhor){ //L67: num_leaf++ é somada toda vez que esta comparação é feita
            melhor = usados;
            num_copy++; //num_copy é somada se a comparação for verdadeira (continuação explicação L67)
        }
    }
    usados.clear();
    return max(sem_i, valor + com_i);
    
}


int main() {

    int n = 0;
    int W = 0;

    vector<item> mochila;

    cin >> n >> W; //numero de elementos e peso
    vector<item> items;
    vector<item> usado;
    vector<item> melhor;
    items.reserve(n);
    usado.reserve(n);
    double peso, valor;
    for(int i = 0; i < n; i++) {
        cin >> peso;
        cin >> valor;
        items.push_back({i, peso, valor});
    }
    
    cout << "RESULTADO = " << knapSack2(W, items, usado, melhor) << "\n";
    cout << "ELEMENTOS NA MOCHILA = "; 
    for(auto& el: melhor) {
            cout << el.id << " ";
    }
    cout<<"\n num_leaf = "<<num_leaf<<"\n num_copy = "<<num_copy<<"\n";

    
    return 0;
}