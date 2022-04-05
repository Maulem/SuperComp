#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;

int main() {

    struct item {
        int id;
        double peso;
        double valor;
        
    };

    // n = numero objs, w = peso total da mochila
    int n = 0;
    int W = 0;

    vector<item> mochila;

    cin >> n >> W;

    // Cria um gerador aleatorio com seed 10
    default_random_engine generator;
    generator.seed(10);
    
    // Cria um intervalo de destribuicao de 0.0 a 1.0 real
    uniform_real_distribution<double> distribution(0.0, 1.0);


    vector<item> items;
    items.reserve(n);
    double peso, valor;

    // Captura cada item individualmente
    for(int i = 0; i < n; i++) {
        cin >> peso;
        cin >> valor; 
        items.push_back({i, peso, valor});
    }

    // Ordena os itens por valor maior para o menor
    sort(items.begin(), items.end(), [](auto& i, auto& j){return i.valor > j.valor;});

    peso = 0;
    valor = 0;

    // Controla a posicao para selecionar item ainda nao obtido 
    int i = 1;

    for(auto& el : items){
        // Se o peso do elemento + peso até agora <= peso maximo
        if (el.peso + peso <= W) {
            mochila.push_back(el);
            peso = peso + el.peso;
            valor = valor + el.valor;
            //cout<<"inclui o elemento = " << el.id << "\n";
            
        }
        // Se a chance de 25% for ativa e n tiver chegado no fim dos elem
        if (distribution(generator) > 0.75 && i < n) {
            // Escolha aleatoria nos outros itens que ainda não foram coletados
            uniform_int_distribution<int> distributionInt(i,n-1);
            int p = distributionInt(generator);
            //cout << "obtive o valor p = " << p << " com id = " << i <<  "\n";
            if(items[p].peso + peso <= W){
                mochila.push_back(items[p]);
                peso = peso + items[p].peso;
                valor = valor + items[p].valor;
                //cout<<"removi elemento p = " << p << " com id de = " << items[p].id << "\n";
                // Apaga o item da lista para não ter perigo de escolher dnv o msm item
                items.erase(items.begin()+p-1);
                n = n-1; 
                //cout << "n = " << n << endl;
            }
        }
        i = i+1;
    }

    // Deixa os itens escolhidos em ordem crescente
    sort(mochila.begin(), mochila.end(), [](auto& i , auto& j){return i.id < j.id;});
    cout << peso << " " << valor << " 0" << endl;

    for(auto& el: mochila) {
        cout << el.id << " ";
    }
    cout << endl;
    return 0;
}