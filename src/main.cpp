#include <iostream>
#include <locale>
#include "Inventario.hpp"
#include "Person.hpp"
#include "Bag.hpp"

using namespace std;

int main(){
    setlocale(LC_ALL, "Portuguese");
    cout << "\n************* INICIO *************\n";
    Inventario BD = Inventario();
    BD.start("dataset/input.data");
    Bag mochila = Bag();
    Person luan = Person(10, BD, mochila, 0, 0);
    luan.solveMaze();
    return 0;
}
