#include <iostream>
#include <locale>
#include "Inventario.hpp"

using namespace std;

int main(){
    srand(time(0));
    setlocale(LC_ALL, "Portuguese");
    cout << "\n************* INICIO *************\n";
    Inventario BD = Inventario();
    BD.start("dataset/input.data");
    cout << "\n************* FIM *************\n\n";
    return 0;
}