#include "ListMatrizes.hpp"

/************************************************** INICIO CONSTRUTORES */
ListMatrizes::ListMatrizes(){
    this->inicio = NULL;
    this->final = NULL;
}

ListMatrizes::ListMatrizes(Matriz firstMatriz){
    this->inicio = new Matriz(firstMatriz);
    this->final = this->inicio;
}
/************************************************** FINAL CONSTRUTORES */

/************************************************** INICIO GETTERS AND SETTERS */
Matriz *ListMatrizes::getInicio(){
    return this->inicio;
}

void ListMatrizes::setInicio(Matriz *newInicio){
    this->inicio = newInicio;
}

Matriz *ListMatrizes::getFinal(){
    return this->final;
}

void ListMatrizes::setFinal(Matriz *newFinal){
    this->final = newFinal;
}
/************************************************** FINAL GETTERS AND SETTERS */

/************************************************** INICIO METODOS */
int ListMatrizes::size(){
    if(empty()){
        return 0;
    }
    int tamanho = 0;
    Matriz *aux = this->inicio;
    do{
        aux = aux->getProximo();
        tamanho = tamanho + 1;
    }while(aux != this->inicio);
    return tamanho;
}

void ListMatrizes::insertInicio(Matriz newMatriz){
    Matriz *newM = new Matriz(newMatriz);
    newM->setAnterior(this->final);
    if(empty()){
        this->inicio = newM;
        this->final = newM;
        newM->setProximo(this->inicio);
    }
    else{
        newM->setProximo(this->inicio);
        this->inicio->setAnterior(newM);
        this->inicio = newM;
        this->final->setProximo(newM);
    }
}

void ListMatrizes::insertFinal(Matriz newMatriz){
    Matriz *newM = new Matriz(newMatriz);
    newM->setProximo(this->inicio);
    if(empty()){
        newM->setAnterior(this->final);
        this->inicio = newM;
        this->final = newM;
    }
    else{
        newM->setAnterior(this->final);
        this->final->setProximo(newM);
        this->final = newM;
        this->inicio->setAnterior(final);
    }
}

void ListMatrizes::removeFinal(){
    if(this->inicio->getProximo() == this->inicio){
        delete this->inicio->getProximo();
        delete this->inicio->getAnterior();
        this->inicio = NULL;
        this->final = NULL;
    }
    else if(this->inicio->getProximo()->getProximo() == this->inicio){
        this->inicio->getProximo()->setAnterior(NULL);
        delete this->inicio->getProximo();
        this->inicio->setProximo(this->inicio);
        this->final = this->inicio;
    }
    else{
        Matriz *antesDoAnterior = this->inicio;
        Matriz *anterior = this->inicio->getProximo();
        Matriz *elemento = this->inicio->getProximo()->getProximo();
        while (elemento != this->inicio) {
            Matriz *aux = anterior; 
            anterior = elemento;
            antesDoAnterior = aux;
            elemento = elemento->getProximo();
        }
        anterior->setAnterior(NULL);
        delete antesDoAnterior->getProximo();
        antesDoAnterior->setProximo(this->inicio);
        this->final = antesDoAnterior;
    }
}

bool ListMatrizes::empty(){
    return (this->inicio == NULL);
}

void ListMatrizes::print(){
    Matriz *aux = this->inicio;
    if(empty()){
        cout << "---> A lista não possui elementos!";
    }
    else{
        do{
            aux->print();
            aux = aux->getProximo();
        }while (aux != this->inicio);
    }
}

void ListMatrizes::printInvertido(){
     Matriz *aux = this->final;
    if(empty()){
        cout << "---> A lista não possui elementos!";
    }
    else{
        do{
            aux->print();
            aux = aux->getAnterior();
        }while (aux != this->final);
    }
}
void ListMatrizes::solveMaze(){
    int column = 0, row = 0;
    bool caminho = false, alternateMatriz;
    Matriz *matriz = this->inicio;
    while(!caminho || !(matriz == this->inicio) || !allVisit()){
        alternateMatriz = matriz->randomStreet(&row, &column, &caminho);
        matriz->setVisit(true);
        if(alternateMatriz == true){
            matriz = matriz->getProximo();
        }
        else{
            matriz = matriz->getAnterior();
            
        }
    }
    
}

bool ListMatrizes::allVisit(){
	Matriz *aux = this->inicio;
	bool returnBool = true;
    do{
    	if(aux->getVisit() == false){
    		returnBool = false;
		}
        aux = aux->getProximo();
    }while(aux != this->inicio);
    return returnBool;	
}
/************************************************** FINAL METODOS */
