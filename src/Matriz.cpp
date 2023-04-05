#include "Matriz.hpp"

/******************************************************************************************** INICIO CONSTRUTORES */
Matriz::Matriz(){
    this->tamanhoLinha = 0;
    this->tamanhoColuna = 0;
    this->linha = 0;
    this->coluna = 0;
    this->proximo = NULL;
    this->visit = false;
}

Matriz::Matriz(short int numeroLinha, short int numeroColuna){
    this->tamanhoLinha = numeroLinha;
    this->tamanhoColuna = numeroColuna;
    this->matriz = (Numero**) calloc(this->tamanhoLinha, sizeof(Numero*));
    for(int i=0;i<this->tamanhoLinha;i++){
        this->matriz[i] = (Numero*) calloc(this->tamanhoColuna, sizeof(Numero));
    }
    this->linha = 0;
    this->coluna = 0;
    this->proximo = NULL;
    this->visit = false;
}
/******************************************************************************************** FINAL CONSTRUTORES */

/******************************************************************************************** INICIO GETTERS AND SETTERS */
Numero **Matriz::getMatriz(){
    return this->matriz;
}

void Matriz::setMatriz(Numero **newMatriz){
    this->matriz = newMatriz;
}

short int Matriz::getTamanhoLinha(){
    return this->tamanhoLinha;
}

short int Matriz::getTamanhoColuna(){
    return this->tamanhoColuna;
}

void Matriz::setTamanho(short int newTamanhoLinha, short int newTamanhoColuna){
    this->tamanhoLinha = newTamanhoLinha;
    this->tamanhoColuna = newTamanhoColuna;
    this->matriz = (Numero**) calloc(this->tamanhoLinha, sizeof(Numero*));
    for(int i=0;i<this->tamanhoLinha;i++){
        this->matriz[i] = (Numero*) calloc(this->tamanhoColuna, sizeof(Numero));
    }
    this->linha = 0;
    this->coluna = 0;
}

short int Matriz::getLinha(){
    return this->linha;
}

void Matriz::setLinha(short int newLinha){
    this->linha = newLinha;
}

short int Matriz::getColuna(){
    return this->coluna;
}

void Matriz::setColuna(short int newColuna){
    this->coluna = newColuna;
}

Matriz *Matriz::getProximo(){
    return this->proximo;
}

void Matriz::setProximo(Matriz *newProximo){
    this->proximo = newProximo;
}

Matriz *Matriz::getAnterior(){
   return this->anterior;
}

void Matriz::setAnterior(Matriz *newAnterior){
    this->anterior = newAnterior;
}

Numero *Matriz::getLastVisit(){
    return this->lastVisit;
}

void Matriz::setLastVisit(Numero *newLastVisit){
    this->lastVisit = newLastVisit;
}

bool Matriz::getVisit(){
    return this->visit;
}

void Matriz::setVisit(bool newVisit){
    this->visit = newVisit;
}
/******************************************************************************************** FINAL GETTERS AND SETTERS */

/******************************************************************************************** INICIO METODOS */
void Matriz::addNumber(short int number){
    try{
        if(this->linha == this->tamanhoLinha && this->coluna == this->tamanhoColuna){
			throw "../Matriz.cpp::addNumberMatriz ---> Matriz cheia";
		}
        Numero n(number);
        this->matriz[this->linha][this->coluna] = n;
        if(this->coluna == this->tamanhoColuna-1){
            this->linha++;
            this->coluna = 0;
        }
        else if(this->coluna != this->tamanhoColuna-1){
            this->coluna++;
        }
    }
    catch(const char *msg){
        cerr << "\n\nERRO...ERRO " << msg << " ...ERRO...ERRO\n\n";
    }
}

void Matriz::print(){
    cout << endl;
    for(int i=0;i<this->tamanhoLinha;i++){
        for(int j=0;j<this->tamanhoColuna;j++){
            cout << this->matriz[i][j].getValor() << " ";
        }
        cout << "\n";
    }
}

void Matriz::createPortals(){
    int colunaAux = 0;
    while(true){
        for(int linhaAux=0; linhaAux <= this->tamanhoColuna-1; linhaAux++){
            if(colunaAux == 0 && this->matriz[linhaAux][colunaAux].getValor() == -2){ //      BORDA ESQUERDA
                this->matriz[linhaAux][colunaAux].setValor(-3);
            }
            else if(colunaAux == this->tamanhoColuna-1 && this->matriz[linhaAux][colunaAux].getValor() == -2){ //        BORDA DIREITA
                this->matriz[linhaAux][colunaAux].setValor(-4);
            }
        }
        if(colunaAux == this->tamanhoColuna-1){
            break;
        }
        colunaAux = this->tamanhoColuna-1;
    }
}

bool Matriz::randomStreet(int *keyRow, int *keyColumn){
    srand(time(0));
    int currentRow = *keyRow, currentColumn = *keyColumn;
    makeDecision(keyRow, keyColumn, currentRow, currentColumn);
    while(true){
    	currentRow = *keyRow;
		currentColumn = *keyColumn;
		this->lastVisit = &this->matriz[*keyRow][*keyColumn];
		this->lastVisit->setVisit(true);
    	do{
    		*keyRow += (-1+rand()%3);
	    	*keyColumn += (-1+rand()%3);	
		}while((*keyRow  == currentRow && *keyColumn == currentColumn) || (&this->matriz[*keyRow][*keyColumn] == this->lastVisit));
	    if(*keyColumn < 0  && (*keyRow >=0 && *keyRow <= this->tamanhoLinha-1)){     // -----> MATRIZ ANTERIOR
	        *keyColumn = this->tamanhoColuna-1;
	        return false;
	    }
	    else if(*keyColumn == this->tamanhoColuna  && (*keyRow >=0 && *keyRow <= this->tamanhoLinha-1)){     // -----> MATRIZ POSTERIOR
	        *keyColumn = 0;
	        return true;
	    }
	    makeDecision(keyRow, keyColumn, currentRow, currentColumn);
	}
    return NULL;
}

bool Matriz::isFirstElement(Numero *adreess){
	if(adreess == &matriz[0][0]){
		return true;
	}
    return false;
}

void Matriz::makeDecision(int *keyRow, int *keyColumn, int currentRow, int currentColumn){
	if(*keyRow < 0){
		*keyRow = currentRow;
		*keyColumn = currentColumn;
		randomStreet(keyRow, keyColumn);
	}
	else if (*keyRow == this->tamanhoLinha){       // -----> CAIU FORA PELAS BORDAS HORIZONTAIS
	    *keyRow = currentRow;
		*keyColumn = currentColumn;
		randomStreet(keyRow, keyColumn);
	}
	else if(&this->matriz[*keyRow][*keyColumn] == this->lastVisit){
		// NÃO FAZ NADA
	}
	else{
		this->matriz[*keyRow][*keyColumn] = 0;
		print();	
	}
}
/******************************************************************************************** FINAL METODOS */
