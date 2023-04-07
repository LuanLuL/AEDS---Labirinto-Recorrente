#ifndef __BAG_HPP
#define __BAG_HPP

#include <iostream>
#include <vector>
using namespace std;

class Bag{
    private:
        vector<short int> itens;
        bool forget;
        int itensTotal;
    public:
        /************************************************** INICIO CONSTRUTORES */
        Bag();
        Bag(vector<short int> qtdItens, bool abandonada, int qtdItensTotal);
        /************************************************** FINAL CONSTRUTORES */

        /************************************************** INICIO GETTERS AND SETTERS */
        vector<short int> getItens();
        void setItens(vector<short int> newItens);
        int getItensTotal();
        void setItensTotal(bool newItensTotal);
        bool isForget();
        void setForget(bool newForget);
        /************************************************** FINAL GETTERS AND SETTERS */ 

        /*************************************************************** INICIO METODOS */
        bool addItem();
        bool returnHealthPoint();
        void print();
        /************************************************************** FINAL METODOS */
};  

#endif