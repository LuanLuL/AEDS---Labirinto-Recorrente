#include "Inventario.hpp"

/************************************************** INICIO CONSTRUTORES */
Inventario::Inventario(){
	this->lista = Lista();
}
/************************************************** FINAL CONSTRUTORES */

Lista Inventario::getLista(){
    return this->lista;
}

void Inventario::setLista(Lista newLista){
    this->lista = newLista;
}
/******************************************************************************************** FINAL GETTERS AND SETTERS */

/******************************************************************************************** INICIO METODOS */
void Inventario::start(string data){
    try{
        fstream inFile;
        inFile.open(data.c_str());
        if(!inFile){
            throw "../main.cpp::lerTxt ---> Não foi poss?vel abrir o arquivo de entrada";
        }
        string numberStr;
        int aux = 0, tamanhoLinha = 0, tamanhoColuna = 0, aux2 =0, numberInt, limite = 0, i = 1;
        No element;
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
                    this->lista.insertFinal("matriz" + to_string(i));
                    insert("dataset/matriz" + to_string(i) + ".data", m);
                    i++;
                }
            }
        }
        inFile.close();
    }
    catch(const char *msg){
        cerr << "\n\n" << msg << "\n\n";
        exit(0);
    }
}
void Inventario::insert(string name , Matriz matrix){
    try{
        ofstream outFile (name.c_str()); 
        if(!outFile){
            throw "../Inventario::insertMatriz(string name) ----> Não foi possível abrir o arquivo de saíida";
        }
        outFile << matrix.getTamanhoLinha() << " " << matrix.getTamanhoColuna() << " " << matrix.getVisit()<< endl;
        matrix.createPortals();
        for(int row = 0; row < matrix.getTamanhoLinha(); row++){
            for(int column = 0; column < matrix.getTamanhoColuna(); column++){
                outFile << matrix.getMatriz()[row][column].getValor() << " " << matrix.getMatriz()[row][column].getVisit() << " ";
            }
            outFile << endl;
        }
        outFile.close();
    }
    catch(const char *msg){
        cerr << "\n\n" << msg << "\n\n";
        exit(0);
    }
}
/******************************************************************************************** FINAL METODOS */