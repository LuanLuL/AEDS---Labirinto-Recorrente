#ifndef __NO_HPP
#define __NO_HPP

#include <iostream>
#include <string>

using namespace std;

class No{
    private:
        string valor;
        No *proximo;
        No *anterior;

    public:
        /*************************************************************** INICIO CONSTRUTORES */
        No();
        No(string first);
        /*************************************************************** FINAL CONSTRUTORES */

        /*************************************************************** INICIO GETTERS AND SETTERS */
        string getValor(); 
        void setValor(string newValor);
        No *getProximo();
        void setProximo(No *newProximo);
        No *getAnterior();
        void setAnterior(No *newAnterior);
        No *getLastVisit();
        /*************************************************************** FINAL GETTERS AND SETTERS */

        /*************************************************************** INICIO METODOS */
        void print();
        /************************************************************** FINAL METODOS */
};

#endif

