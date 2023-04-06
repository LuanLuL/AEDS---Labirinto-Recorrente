#ifndef __INVENTARIO_HPP
#define __INVENTARIO_HPP

#include <iostream>
#include <locale>
#include <string>
#include <fstream>
#include "Lista.hpp"
#include "Matriz.hpp"

using namespace std;

class Inventario{
	private:
		Lista lista;
	public:
		/************************************************** INICIO CONSTRUTORES */
        Inventario();
        /************************************************** FINAL CONSTRUTORES */

        /************************************************** INICIO GETTERS AND SETTERS */
        Lista getLista();
        void setLista(Lista newLista);
        /************************************************** FINAL GETTERS AND SETTERS */

        /************************************************** INICIO METODOS */
        void start(string data);
        void insert(string name, Matriz matrix);
        /************************************************** FINAL METODOS */		
};

#endif
