#include <iostream>
#include <locale>
#include "Inventario.hpp"

using namespace std;

int main(){
    setlocale(LC_ALL, "Portuguese");
    cout << "\n************* INICIO *************\n";
    Inventario BD = Inventario();
    BD.start("dataset/input.data");
    BD.solveMaze();
    cout << "\n************* FIM *************\n\n";
    return 0;
}
