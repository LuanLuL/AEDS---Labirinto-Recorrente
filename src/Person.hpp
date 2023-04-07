#ifndef __PERSON_HPP
#define __PERSON_HPP

#include <iostream>
#include "Numero.hpp"
#include "Matriz.hpp"
#include "Inventario.hpp"
#include "Bag.hpp"
using namespace std;

class Person{
    private:
        short int health;
        Inventario map;
        Bag bag;
        Numero * lastVisit;
        int damageTotal;
    public:
        //************************************************** INICIO CONSTRUTORES */
        Person();
        Person(short int pntsVidas, Inventario labirinto, Bag bag, Numero * ultimoNumero);
        //************************************************** FINAL CONSTRUTORES *

        //************************************************** INICIO GETTERS AND SETTERS */
        short int getHealth();
        void setHealth(short int newHealth);
        Inventario getMap();
        void setMap(Inventario newMap);
        Bag getBag();
        void setBag(Bag newBag);
        Numero *getLastVisit();
        void setLastVisit(Numero *newLastVisit);
        int getDamageTotal();
        void setDamageTotal(int newDamageTotal);
        //************************************************** FINAL GETTERS AND SETTERS */ 

        //*************************************************************** INICIO METODOS */
        void move();
        void regenerateHealth();
        void takesADamage(string data, Matriz matrix);
        void solveMaze();
        bool finishSolveMaze(No *currentNo, int keyRow, int keyColumn);
        /************************************************************** FINAL METODOS */
};  

#endif