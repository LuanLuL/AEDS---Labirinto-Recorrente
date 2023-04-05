#include "Numero.hpp"

/************************************************** INICIO CONSTRUTORES */
Numero::Numero(){
    this->valor = 0;
    this->visit = false;
}

Numero::Numero(short int number){
    this->valor = number;
    this->visit = false;
}
/************************************************** FINAL CONSTRUTORES */

/************************************************** INICIO GETTERS AND SETTERS */
short int Numero::getValor(){
    return this->valor;
}

void Numero::setValor(short int newValor){
    this->valor = newValor;
}

bool Numero::getVisit(){
    return this->visit;
}

void Numero::setVisit(bool newVisit){
    this->visit = newVisit;
}
/************************************************** FINAL GETTERS AND SETTERS */

