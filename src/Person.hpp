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
        int damageTotal;
        int moveTotal;
    public:
        //************************************************** INICIO CONSTRUTORES */
        Person();
        Person(short int health, Inventario map, Bag bag, int damageTotal, int moveTotal);
        //************************************************** FINAL CONSTRUTORES *

        //************************************************** INICIO GETTERS AND SETTERS */
        short int getHealth();
        void setHealth(short int newHealth);
        Inventario getMap();
        void setMap(Inventario newMap);
        Bag getBag();
        void setBag(Bag newBag);
        int getDamageTotal();
        void setDamageTotal(int newDamageTotal);
        int getMoveTotal();
        void setMoveTotal(int newMoveTotal);
        //************************************************** FINAL GETTERS AND SETTERS */ 

        //*************************************************************** INICIO METODOS */
        void move(int *keyRow, int *keyColumn, int *currentRow, int *currentColumn, Matriz *matix, No **no);
        void regenerateHealth();
        void takesADamage(string data, Matriz matrix);
        void solveMaze();
        bool finishSolveMaze(No *currentNo, int keyRow, int keyColumn, int rowStart, int columnStart);
        void printResults(bool isDead);
        /************************************************************** FINAL METODOS */
};  

#endif