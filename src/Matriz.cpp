#include "Matriz.hpp"

/******************************************************************************************** INICIO CONSTRUTORES */
Matriz::Matriz(){
    this->tamanhoLinha = 0;
    this->tamanhoColuna = 0;
    this->linha = 0;
    this->coluna = 0;
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

Numero *Matriz::getLastVisit(){
    return this->lastVisit;
}

void Matriz::setLastVisit(Numero *newLastVisit){
    this->lastVisit = newLastVisit;
}

bool Matriz::getVisit(){
	for(int i=0;i<this->tamanhoLinha;i++){
        for(int j=0;j<this->tamanhoColuna;j++){
            if(this->matriz[i][j].getVisit() == true){
				return true;            	
			}
        }
    }
    return false;
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

short int Matriz::randomStreet(int *keyRow, int *keyColumn){
    srand(time(0));
    this->matriz[*keyRow][*keyColumn].setVisit(true);
    int currentRow = *keyRow, currentColumn = *keyColumn;
    *keyRow += (-1+rand()%3);
	*keyColumn += (-1+rand()%3);
	if((currentRow == *keyRow) && (currentColumn == *keyColumn)){ //	CAIU ONDE JA ESTAVA
		return randomStreet(keyRow, keyColumn);
	}
	else if(*keyRow == -1 && (*keyColumn >= 0 && *keyColumn <= this->tamanhoColuna-1)){ //	SAIU DA MATRIZ PELA BORDA SUPERIOR
		return 1;
	}
	else if((*keyRow >=0 && *keyRow <= this->tamanhoLinha-1) && *keyColumn == this->tamanhoColuna){ //	SAIU DA MATRIZ PELA BORDA DIREITA
		return 2;
	}
	else if(*keyRow == this->tamanhoLinha && (*keyColumn >= 0 && *keyColumn <= this->tamanhoColuna-1)){ //	SAIU DA MATRIZ PELA BORDA INFERIOR
		return 3;
	}
	else if((*keyRow >=0 && *keyRow <= this->tamanhoLinha-1) && *keyColumn == -1){ //	SAIU DA MATRIZ PELA BORDA ESQUERDA
		return 4;
	}
	else if((*keyRow >= 0 && *keyRow <= this->tamanhoLinha-1) && (*keyColumn >= 0 && *keyColumn <= this->tamanhoColuna-1)){ //	ESTA NA MATRIZ
		return 5;
	}
	else if((*keyRow == -1 && *keyColumn == -1) || (*keyRow == this->tamanhoLinha && *keyColumn == this->tamanhoColuna) || (*keyRow == -1 && *keyColumn == this->tamanhoColuna) || (*keyRow == this->tamanhoLinha && *keyColumn == -1)){ //	SAIU PARA ALGUMA QUINA
		*keyRow = currentRow;
		*keyColumn = currentColumn;
		return randomStreet(keyRow, keyColumn);
	}
	return 0;
}

bool Matriz::isFirstElement(Numero *adreess){
	if(adreess == &matriz[0][0]){
		return true;
	}
    return false;
}

void Matriz::makeDecision(int keyRow, int keyColumn){
	this->matriz[keyRow][keyColumn].setValor(0);
	print();
}
/******************************************************************************************** FINAL METODOS */
