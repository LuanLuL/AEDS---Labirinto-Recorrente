#include <iostream>
#include <locale>
#include <string>
#include <fstream>
#include "ListMatrizes.hpp"
#include "Matriz.hpp"

using namespace std;

ListMatrizes lerMatrizesQuadradas(string txt){
    ListMatrizes returnListMatrizes;
    try{
        fstream inFile;
        inFile.open(txt.c_str());
        if(!inFile){
            throw "../main.cpp::lerTxt ---> Não foi possível abrir o arquivo de entrada";
        }
        string numberStr;
        short int aux = 0, tamanhoLinha = 0, tamanhoColuna = 0, aux2 =0, numberInt, limite = 0;
        Matriz m;
        while (!inFile.eof()){
            if(aux == 0){
                getline(inFile, numberStr);
                if(aux2 == 0){
                    tamanhoLinha = atoi(&numberStr.at(0));
                    tamanhoColuna = atoi(&numberStr.at(2));
                    aux2 = aux2 + 1;
                }
                Matriz newM(tamanhoLinha, tamanhoColuna);
                m = newM;
                aux = aux + 1;
            }
            else{
                inFile >> numberStr;
                if(numberStr == "*"){
                    numberInt = -1;
                }
                else if(numberStr == "#"){
                    numberInt = -2;
                }
                else{
                    numberInt = atoi(numberStr.c_str());
                }
                m.addNumber(numberInt);
                limite++;
                if(limite == (m.getTamanhoLinha() * m.getTamanhoColuna())){
                    aux = 0;
                    limite = 0;
                    m.createPortals();
                    returnListMatrizes.insertFinal(m);
                }
            }
        }
        inFile.close();
    }
    catch(const char *msg){
        cerr << "\n\nERRO...ERRO... " << msg << " ...ERRO...ERRO\n\n";
    }
    return returnListMatrizes;
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    cout << "\n************* INICIO *************\n";
    ListMatrizes listaM;
    listaM = lerMatrizesQuadradas("input.data");
    listaM.solveMaze();
    cout << "\n************* FIM *************\n\n";
    return 0;
}
