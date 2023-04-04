#ifndef __MATRIZ_HPP
#define __MATRIZ_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Numero.hpp"
using namespace std;

class Matriz{
    private:
        Numero **matriz;
        Numero *lastVisit;
        bool visit;
        short int linha, coluna, tamanhoLinha, tamanhoColuna;
        Matriz *proximo;
        Matriz *anterior;

    public:
        /*************************************************************** INICIO CONSTRUTORES */
        Matriz();
        Matriz(short int numeroLinha, short int numeroColuna);
        /*************************************************************** FINAL CONSTRUTORES */

        /*************************************************************** INICIO GETTERS AND SETTERS */
        Numero **getMatriz(); 
        void setMatriz(Numero **newMatriz);
        short int getTamanhoLinha();
        short int getTamanhoColuna();
        void setTamanho(short int newTamanhoLinha, short int newTamanhoColuna);
        short int getLinha();
        void setLinha(short int newLinha);
        short int getColuna();
        void setColuna(short int newColuna);
        Matriz *getProximo();
        void setProximo(Matriz *newProximo);
        Matriz *getAnterior();
        void setAnterior(Matriz *newAnterior);
        Numero *getLastVisit();
        void setLastVisit(Numero *newLastVisit);
        bool getVisit();
        void setVisit(bool newVisit);
        /*************************************************************** FINAL GETTERS AND SETTERS */

        /*************************************************************** INICIO METODOS */
        void addNumber(short int number);
        void print();
        void createPortals();
        bool randomStreet(int *keyRow, int *keyColumn, bool *caminho);
        /************************************************************** FINAL METODOS */
};

#endif
