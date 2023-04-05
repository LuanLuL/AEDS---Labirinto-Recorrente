#ifndef __NUMERO_HPP
#define __NUMERO_HPP

#include <iostream>
using namespace std;

class Numero{
    private:
        short int valor;
        bool visit; 
    public:
        /************************************************** INICIO CONSTRUTORES */
        Numero();
        Numero(short int number);
        /************************************************** FINAL CONSTRUTORES */

        /************************************************** INICIO GETTERS AND SETTERS */
        short int getValor();
        void setValor(short int newValor);
        bool getVisit();
        void setVisit(bool newVisit);
        /************************************************** FINAL GETTERS AND SETTERS */
        
};

#endif

