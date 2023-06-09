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
        if(this->lista.size() == 1){
            this->lista.getInicio()->setVisit(true);
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
        outFile << matrix.getTamanhoLinha() << " " << matrix.getTamanhoColuna() << endl;
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
            throw "../Inventario::retrive(string data) ---> Não foi possível abrir o arquivo de entrada";
        }
        string numberStr;
        int aux = 0, numberInt, i = 0;
        bool visit;
        while (!inFile.eof()){
            if(aux == 0){
                getline(inFile, numberStr);
                Matriz newM(atoi(&numberStr.at(0)), atoi(&numberStr.at(2)));
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

int Inventario::selectNumbersNotAccess(string data)
{
    int numberNotAccess = 0;
    Matriz mAux = retrive("dataset/" + data);
    for(int row = 0; row < mAux.getTamanhoLinha()-1; row++){
        for(int column = 0; column < mAux.getTamanhoColuna()-1; column++){
            if(mAux.getMatriz()[row][column].getVisit() == false){
                numberNotAccess = numberNotAccess + 1;
            }
        }
    }
    return numberNotAccess;
}

void Inventario::createOutput(){
    try{
        fstream inFile;
        ofstream outFile ("dataset/output.data"); 
        if(!outFile){
            throw "../Inventario::createOutPut() ----> Não foi possível abrir o arquivo de saída";
        }
        No *noAux = this->lista.getInicio();
        string numberStr;
        int aux = 0, aux2 = 0, tamanhoLinha = 0, tamanhoColuna = 0, limite = 0, i = 1;
        do{
            inFile.open(("dataset/" + noAux->getValor()).c_str());
            if(!inFile){
                throw "../Inventario::createOutPut() ---> Não foi possível abrir o arquivo de entrada";
            }            
            while (!inFile.eof()){
                if(aux == 0){
                    getline(inFile, numberStr);
                    if(aux2 == 0){
                        tamanhoLinha = atoi(&numberStr.at(0));
                        tamanhoColuna = atoi(&numberStr.at(2));
                        outFile << tamanhoLinha << " " << tamanhoColuna  << " " << this->lista.getCount() << endl;
                        aux2 = aux2 + 1;
                    }
                    aux = aux + 1;
                }
                else{
                    inFile >> numberStr;
                    if(i % 2 == 0){
                        if(numberStr == "-2" || numberStr == "-3" || numberStr == "-4"){
                            outFile << "# ";
                        }
                        else if(numberStr == "-1"){
                            outFile << "* ";
                        }
                        else{
                            outFile << numberStr << " ";
                        }
                        limite++;
                        if(i % (tamanhoColuna * 2) == 0){
                            outFile << endl;
                        }
                        if(limite == (tamanhoLinha * tamanhoColuna) && noAux != this->lista.getFinal()){
                            aux = 0;
                            limite = 0;
                            outFile << endl;
                            i = 1;
                            break;
                        }
                    }
                    else{
                       // FAZ NADA 
                    }
                    i++;
                }
            }
            inFile.close();
            remove(("dataset/" + noAux->getValor()).c_str());
            noAux = noAux->getProximo();
        }while(noAux != this->lista.getInicio());  
    }
    catch(const char *msg){
        cerr << "\n\n" << msg << "\n\n";
        exit(0);
    }
}
/******************************************************************************************** FINAL METODOS */
