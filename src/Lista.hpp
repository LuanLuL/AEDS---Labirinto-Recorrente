#ifndef __LISTA_HPP
#define __LISTA_HPP

#include <iostream>
#include "No.hpp"
using namespace std;

class Lista{
    private:
        No *inicio;
        No *final;
        int count;
        
    public:
        /************************************************** INICIO CONSTRUTORES */
        Lista();
        Lista(string first);
        /************************************************** FINAL CONSTRUTORES */

        /************************************************** INICIO GETTERS AND SETTERS */
        No *getInicio();
        void setInicio(No *newInicio);
        No *getFinal();
        void setFinal(No *newFinal);
        int getCount();
        void setCount(int newCount);
        void setVisit(string name);
        /************************************************** FINAL GETTERS AND SETTERS */

        /************************************************** INICIO METODOS */
        int size();
        void insertInicio(string newString);
        void insertFinal(string newString);
        void removeFinal();
        bool empty();
        void print();
        void printInvertido();
        bool allVisit();
        void setAllVisit(bool value);
        /************************************************** FINAL METODOS */ 
};

#endif


