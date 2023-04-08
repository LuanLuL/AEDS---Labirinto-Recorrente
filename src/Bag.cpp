#include "Bag.hpp"

/******************************************************************************************** INICIO CONSTRUTORES */
Bag::Bag(){
    this->itens.clear();
    this->forget = true;
    this->itensTotal = 0;
}

Bag::Bag(vector<short int> qtdItens, bool abandonada, int qtdItensTotal){
    this->itens = qtdItens;
    this->forget = abandonada;
    this->itensTotal = qtdItensTotal;
}
/******************************************************************************************** FINAL CONSTRUTORES */

/******************************************************************************************** INICIO GETTERS AND SETTERS */
vector<short int> Bag::getItens(){
    return this->itens;
}

void Bag::setItens(vector<short int> newItens){
    this->itens = newItens;
}

int Bag::getItensTotal(){
    return this->itensTotal;
}

void Bag::setItensTotal(bool newItensTotal){
    this->itensTotal = newItensTotal;
}

bool Bag::isForget(){
    return this->forget;
}

void Bag::setForget(bool newForget){
    this->forget = newForget;
}
/******************************************************************************************** FINAL GETTERS AND SETTERS */

/******************************************************************************************** INICIO METODOS */
bool Bag::addItem(){
    if(this->itens.size() < 4){
        this->itensTotal = itensTotal + 1;
        this->itens.push_back(this->itens.size() + 1);
        this->forget = false;
    }
    return returnHealthPoint();
}

bool Bag::returnHealthPoint(){
    if(this->itens.size() == 4){
        this->itens.clear();
        return true;
    }
    return false;
}

void Bag::print(){
    short int tam = this->itens.size();
    for(short int i=0; i<tam; i++){
        cout << this->itens[i] << endl;
    }
}
/******************************************************************************************** FINAL METODOS */