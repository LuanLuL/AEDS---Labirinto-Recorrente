#include "Lista.hpp"

/************************************************** INICIO CONSTRUTORES */
Lista::Lista(){
    this->inicio = NULL;
    this->final = NULL;
    this->count = 0;
}

Lista::Lista(string first){
    this->inicio = new No(first);
    this->final = this->inicio;
    this->count = 1;
}
/************************************************** FINAL CONSTRUTORES */

/************************************************** INICIO GETTERS AND SETTERS */
No *Lista::getInicio(){
    return this->inicio;
}

void Lista::setInicio(No *newInicio){
    newInicio->setAnterior(this->inicio->getAnterior());
    newInicio->setProximo(this->inicio->getProximo());
    delete this->inicio;
    this->inicio = newInicio;
}

No *Lista::getFinal(){
    return this->final;
}

void Lista::setFinal(No *newFinal){
    newFinal->setAnterior(this->final->getAnterior());
    newFinal->setProximo(this->final->getProximo());
    delete this->final;
    this->final = newFinal;
}

int Lista::getCount(){
    return this->count;
}

void Lista::setCount(int newCount){
    this->count = newCount;
}
void Lista::setVisit(string name){
    No *aux = this->inicio;
    do{
        if(name == aux->getValor()){
            aux->setVisit(true);
            break;
        }
        aux = aux->getProximo();
    }while(aux != this->inicio);
}
/************************************************** FINAL GETTERS AND SETTERS */

/************************************************** INICIO METODOS */
int Lista::size(){
    if(empty()){
        return 0;
    }
    int tamanho = 0;
    No *aux = this->inicio;
    do{
        aux = aux->getProximo();
        tamanho = tamanho + 1;
    }while(aux != this->inicio);
    return tamanho;
}

void Lista::insertInicio(string newString){
    this->count = this->count + 1;
    No *newNo = new No(newString);
   
    if(empty()){
        this->inicio = newNo;
        this->final = newNo;
        newNo->setAnterior(this->final);
        newNo->setProximo(this->inicio);
    }
    else{
        newNo->setAnterior(this->final);
        newNo->setProximo(this->inicio);
        this->inicio->setAnterior(newNo);
        this->inicio = newNo;
        this->final->setProximo(newNo);
    }
}

void Lista::insertFinal(string newString){
    this->count = this->count + 1;
    No *newNo = new No(newString);
    if(empty()){
        this->inicio = newNo;
        this->final = newNo;
        newNo->setProximo(this->inicio);
        newNo->setAnterior(this->final);
    }
    else{
        newNo->setProximo(this->inicio);
        newNo->setAnterior(this->final);
        this->final->setProximo(newNo);
        this->final = newNo;
        this->inicio->setAnterior(this->final);
    }
}

void Lista::removeFinal(){
    this->count = this->count - 1;
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
        No *antesDoAnterior = this->inicio;
        No *anterior = this->inicio->getProximo();
        No *elemento = this->inicio->getProximo()->getProximo();
        while (elemento != this->inicio) {
            No *aux = anterior; 
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

bool Lista::empty(){
    return (this->inicio == NULL);
}

void Lista::print(){
    No *aux = this->inicio;
    if(empty()){
        cout << "---> A lista não possui elementos!";
    }
    else{
        do{
            aux->print();
            cout << endl;
            aux = aux->getProximo();
        }while (aux != this->inicio);
    }
}

void Lista::printInvertido(){
    No *aux = this->final;
    if(empty()){
        cout << "---> A lista nãoo possui elementos!";
    }
    else{
        do{
            aux->print();
            cout << endl;
            aux = aux->getAnterior();
        }while (aux != this->final);
    }
}

bool Lista::allVisit(){
	No *aux = this->inicio;
    do{
    	if(aux->getVisit() == false){
    		return false;
		}
        aux = aux->getProximo();
    }while(aux != this->inicio);
    return true;	
}
/************************************************** FINAL METODOS */