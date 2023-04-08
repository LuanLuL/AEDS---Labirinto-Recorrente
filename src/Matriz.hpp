#ifndef __MATRIZ_HPP
#define __MATRIZ_HPP

#include <iostream>
#include <random>
#include "Numero.hpp"
using namespace std;

class Matriz{
    private:
        Numero **matriz;
        bool visit;
        short int linha, coluna, tamanhoLinha, tamanhoColuna;
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
        bool getVisit();
        void setVisit(bool newVisit);  
        /*************************************************************** FINAL GETTERS AND SETTERS */

        /*************************************************************** INICIO METODOS */
        void addNumber(short int number, bool visit);
        void print();
        void createPortals();
        short int randomStreet(int *keyRow, int *keyColumn, int *currentRow, int *currentColumn);
        void randomStart(int *keyRow, int *keyColumn, int *currentRow, int *currentColumn);
        int randomNumber(int breaksStart, int breaksEnd);
        bool isFirstElement(Numero *adreess);
        void allowedEntry(int keyRow, int keyColumn);
        /************************************************************** FINAL METODOS */
};

#endif


