#include "No.hpp"

/******************************************************************************************** INICIO CONSTRUTORES */
No::No(){
    this->valor = "";
    this->proximo = NULL;
    this->anterior = NULL;
}

No::No(string first){
    this->valor = first;
    this->proximo = NULL;
    this->anterior = NULL;
}
/******************************************************************************************** FINAL CONSTRUTORES */

/******************************************************************************************** INICIO GETTERS AND SETTERS */
string No::getValor(){
    return this->valor;
}

void No::setValor(string newValor){
    this->valor = newValor;
}

No *No::getProximo(){
    return this->proximo;
}

void No::setProximo(No *newProximo){
    this->proximo = newProximo;
}

No *No::getAnterior(){
   return this->anterior;
}

void No::setAnterior(No *newAnterior){
    this->anterior = newAnterior;
}
/******************************************************************************************** FINAL GETTERS AND SETTERS */

/******************************************************************************************** INICIO METODOS */
void No::print(){
    cout << this->valor;
}
/******************************************************************************************** FINAL METODOS */
