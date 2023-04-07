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
            throw "../Inventario::start(string data) ---> Não foi possível abrir o arquivo de entrada";
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
                m.addNumber(numberInt, false);
                limite++;
                if(limite == (m.getTamanhoLinha() * m.getTamanhoColuna())){
                    aux = 0;
                    limite = 0;
                    this->lista.insertFinal("matriz" + to_string(i) + ".data");
                    create("dataset/matriz" + to_string(i) + ".data", m);
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
void Inventario::create(string name , Matriz matrix){
    try{
        ofstream outFile (name.c_str()); 
        if(!outFile){
            throw "../Inventario::insertMatriz(string name) ----> Não foi possível abrir o arquivo de saída";
        }
        outFile << matrix.getTamanhoLinha() << " " << matrix.getTamanhoColuna() << " " << matrix.getVisit()<< endl;
        matrix.createPortals();
        for(int row = 0; row < matrix.getTamanhoLinha(); row++){
            for(int column = 0; column < matrix.getTamanhoColuna(); column++){
                outFile << matrix.getMatriz()[row][column].getVisit() << " " << matrix.getMatriz()[row][column].getValor() << " ";
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

Matriz Inventario::retrive(string data){
    Matriz returnMatriz;
    try{
        fstream inFile;
        inFile.open(data.c_str());
        if(!inFile){
            throw "../Inventario::retrive(string data) ---> N�o foi poss�vel abrir o arquivo de entrada";
        }
        string numberStr;
        int aux = 0, numberInt, i = 0;
        bool visit;
        while (!inFile.eof()){
            if(aux == 0){
                getline(inFile, numberStr);Matriz newM(atoi(&numberStr.at(0)), atoi(&numberStr.at(2)));
                if(atoi(&numberStr.at(4)) == 0){
                    newM.setVisit(false);
                }
                else{
                    newM.setVisit(true);
                    lista.setVisit(data);
                }
                returnMatriz = newM;
                aux = aux + 1;
            }
            else{
                inFile >> numberStr;
                numberInt = atoi(numberStr.c_str());
                if(i % 2 == 0){
                    if(numberInt == 0){
                        visit = false;
                    }
                    else{
                        visit = true;
                    }
                }
                else{
                    returnMatriz.addNumber(numberInt, visit);
                }
                i++;
            }
        }
        inFile.close();
        return returnMatriz;
    }
    catch(const char *msg){
        cerr << "\n\n" << msg << "\n\n";
        exit(0);
    }
}
/******************************************************************************************** FINAL METODOS */
