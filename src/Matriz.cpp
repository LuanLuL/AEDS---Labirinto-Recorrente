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

bool Matriz::randomStreet(int *keyRow, int* keyColumn, bool *caminho){
    srand(time(0));
    short int nextStreet;
    while(true){
    	*caminho = false;
    	//cout << "\n\nPrint de antes = [" << *keyRow << "][" << *keyColumn << "]\n\n";
        matriz[*keyRow][*keyColumn] = 0;
        matriz[*keyRow][*keyColumn].setVisit(true);
        print();
        if(*keyRow == 0 && *keyColumn == 0){ //      CANTO SUPERIOR ESQUERDO
        	//cout << "\n\nCANTO SUPERIOR ESQUERDOO  [" << *keyRow << "][" << *keyColumn << "]\n\n";
            nextStreet = rand() % 5;
            if(nextStreet == 0){ //      PARA DIREITA
            	if(!(&matriz[*keyRow][*keyColumn + 1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn + 1;
                	//cout << "\n\nPARA DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 1){ //      PARA DIAGONAL INFERIOR DIREITA
            	if(!(&matriz[*keyRow+1][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
	                *keyRow = *keyRow + 1;
	                *keyColumn = *keyColumn + 1;
					//cout << "\n\nPARA DIAGONAL INFERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 2){ //      PARA BAIXO
            	if(!(&matriz[*keyRow+1][*keyColumn] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;	
                	//cout << "\n\nPARA BAIXO  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 3){ //      PARA DIAGONAL INFERIOR ESQUERDA
            	if(!(&this->anterior->matriz[*keyRow+1][this->tamanhoColuna-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;
                	*keyColumn = this->tamanhoColuna-1;
                	//cout << "\n\nPARA DIAGONAL INFERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		        	    *caminho = true;
		        	}
                	return false;	
				}
            }
            else if(nextStreet == 4){ //      PARA ESQUERDA
            	if(!(&this->anterior->matriz[*keyRow][this->tamanhoColuna-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
            		*keyRow = 0;
                	*keyColumn = this->tamanhoColuna-1;
                	//cout << "\n\nPARA ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		        	    *caminho = true;
		        	}
                	return false;	
				}
            }
        }
        else if(*keyRow == 0 && *keyColumn == this->tamanhoColuna-1){ //       CANTO SUPERIOR DIREITO
            //cout << "\n\nCANTO SUPERIOR DIREITO  [" << *keyRow << "][" << *keyColumn << "]\n\n";
			nextStreet = rand() % 5;
            if(nextStreet == 0){ //      PARA DIREITA
            	if(!(&this->proximo->matriz[*keyRow][0] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
            		*keyRow = 0;
                	*keyColumn = 0;
                	//cout << "\n\nPARA DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		        	    *caminho = true;
		        	}
                	return true;	
				}
            }
            else if(nextStreet == 1){ //      PARA DIAGONAL INFERIOR DIREITA
            	if(!(&this->proximo->matriz[*keyRow+1][0] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;
                	*keyColumn = 0;
                	//cout << "\n\nPARA DIAGONAL INFERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		        	    *caminho = true;
		        	}
                	return true;
				}
            }
            else if(nextStreet == 2){ //      PARA BAIXO
            	if(!(&matriz[*keyRow+1][*keyColumn] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;	
                	//cout << "\n\nPARA BAIXO  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 3){ //      PARA DIAGONAL INFERIOR ESQUERDA
            	if(!(&matriz[*keyRow+1][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;
                	*keyColumn = *keyColumn - 1;
					//cout << "\n\nPARA DIAGONAL INFERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 4){ //      PARA ESQUERDA
            	if(!(&matriz[*keyRow][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn - 1;
					//cout << "\n\nPARA ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
        }
        else if(*keyRow == this->tamanhoLinha-1 && *keyColumn == 0){ //     CANTO INFERIOR ESQUERDO    
            //cout << "\n\nCANTO INFERIOR ESQUERDO  [" << *keyRow << "][" << *keyColumn << "]\n\n";
			nextStreet = rand() % 5;
            if(nextStreet == 0){ //      PARA ESQUERDA
            	if(!(&this->anterior->matriz[*keyRow][this->tamanhoColuna-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
            		*keyRow = 6; 
                	*keyColumn = this->tamanhoColuna-1;
                	//cout << "\n\nPARA ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		        	    *caminho = true;
		        	} 
                	return false;	
				}
            }
            else if(nextStreet == 1){ //      PARA DIAGONAL SUPERIOR ESQUERDA
            	if(!(&this->anterior->matriz[*keyRow-1][this->tamanhoColuna-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	*keyColumn = this->tamanhoColuna-1;
                	//cout << "\n\nPARA DIAGONAL SUPERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		            	*caminho = true;
		        	}
                	return false;	
				}
            }
            else if(nextStreet == 2){ //      PARA CIMA
            	if(!(&matriz[*keyRow-1][*keyColumn] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;	
                	//cout << "\n\nPARA CIMA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 3){ //      PARA DIAGONAL SUPERIOR DIREITA
            	if(!(&matriz[*keyRow-1][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	*keyColumn = *keyColumn + 1;
					//cout << "\n\nPARA DIAGONAL SUPERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 4){ //      PARA DIREITA
            	if(!(&matriz[*keyRow][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn + 1;
					//cout << "\n\nPARA DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
        }
        else if(*keyRow == this->tamanhoLinha-1 && *keyColumn == this->tamanhoColuna-1){ //      CANTO INFERIOR DIREITO
            //cout << "\n\nCANTO INFERIOR DIREITO [" << *keyRow << "][" << *keyColumn << "]\n\n";
            nextStreet = rand() % 5;
            if(nextStreet == 0){ //      PARA ESQUERDA
            	if(!(&matriz[*keyRow][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn - 1;
                	//cout << "\n\nPARA ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 1){ //      PARA DIAGONAL SUPERIOR ESQUERDA
            	if(!(&matriz[*keyRow-1][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	*keyColumn = *keyColumn - 1;
					//cout << "\n\nPARA DIAGONAL SUPERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 2){ //      PARA CIMA
            	if(!(&matriz[*keyRow-1][*keyColumn] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	//cout << "\n\nPARA CIMA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 3){ //      PARA DIAGONAL SUPERIOR DIREITA
            	if(!(&this->proximo->matriz[*keyRow-1][0] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	*keyColumn = 0;
                	//cout << "\n\nPARA DIAGONAL SUPERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		        	    *caminho = true;
		        	}
                	return true;	
				}
            }
            else if(nextStreet == 4){ //      PARA DIREITA
            	if(!(&this->proximo->matriz[*keyRow][0] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
            		*keyRow = 6;
                	*keyColumn = 0;
                	//cout << "\n\nPARA DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		        	    *caminho = true;
		        	}
                return true;	
				}
            }
        }
        else if(*keyRow == 0){ //      BORDA SUPERIOR
        	//cout << "\n\nBORDA SUPERIOR  [" << *keyRow << "][" << *keyColumn << "]\n\n";
            nextStreet = rand() % 5;
            if(nextStreet == 0){ //      PARA DIREITA
            	if(!(&matriz[*keyRow][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn + 1;
					//cout << "\n\nPARA DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 1){ //     CANTO INFERIOR DIREITA
            	if(!(&matriz[*keyRow+1][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;
                	*keyColumn = *keyColumn + 1;
					//cout << "\n\nPARA DIAGONAL INFERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 2){ //      PARA BAIXO
            	if(!(&matriz[*keyRow+1][*keyColumn] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
            		*keyRow = *keyRow + 1;
            		//cout << "\n\nPARA BAIXO  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 3){ //     CANTO INFERIOR ESQUERDA
            	if(!(&matriz[*keyRow+1][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;
                	*keyColumn = *keyColumn - 1;
					//cout << "\n\nDIAGONAL INFERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 4){//      PARA ESQUERDA
            	if(!(&matriz[*keyRow][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn - 1;
                	//cout << "\n\nPARA ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
        }
        else if(*keyColumn == this->tamanhoColuna-1){ //        BORDA DIREITA
        	//cout << "\n\nBORDA DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
            nextStreet = rand() % 8;
            if(nextStreet == 0){ //      PARA DIAGONAL SUPERIOR ESQUERDA
            	if(!(&matriz[*keyRow-1][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	*keyColumn = *keyColumn - 1;
					//cout << "\n\nPARA DIAGONAL SUPERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 1){ //      PARA CIMA
            	if(!(&matriz[*keyRow-1][*keyColumn] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	//cout << "\n\nPARA CIMA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 2){ //      PARA DIAGONAL SUPERIOR DIREITA
            	if(!(&this->proximo->matriz[*keyRow-1][0] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	*keyColumn = 0;
                	//cout << "\n\nPARA DIAGONAL SUPERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		        	    *caminho = true;
		        	}
                	return true;	
				}
            }
            else if(nextStreet == 3){ //      PARA DIREITA
            	if(!(&this->proximo->matriz[*keyRow][0] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = 0;
                	//cout << "\n\nPARA DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
               		if(*keyRow == 0 && *keyColumn == 0){
		        	    *caminho = true;
		        	}
                	return true;
				}
            }
            else if(nextStreet == 4){ //     DIAGONAL INFERIOR DIREITA
            	if(!(&this->proximo->matriz[*keyRow+1][0] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;
                	*keyColumn = 0;
                	//cout << "\n\nPARA DIAGONAL INFERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		        	    *caminho = true;
		        	}
                	return true;	
				}
            }
            else if(nextStreet == 5){ //      PARA BAIXO
            	if(!(&matriz[*keyRow+1][*keyColumn] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;	
                	//cout << "\n\nPARA BAIXO  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 6){ //     DIAGONAL INFERIOR ESQUERDA
            	if(!(&matriz[*keyRow+1][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;
                	*keyColumn = *keyColumn - 1;
					//cout << "\n\nDIAGONAL INFERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 7){ //      PARA ESQUERDA
            	if(!(&matriz[*keyRow][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn - 1;
                	//cout << "\n\nPARA ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
        }
        else if(*keyRow == this->tamanhoLinha-1){ //        BORDA INFERIOR
            //cout << "\n\nBORDA INFERIOR  [" << *keyRow << "][" << *keyColumn << "]\n\n";
			nextStreet = rand() % 5;
            if(nextStreet == 0){ //      PARA ESQUERDA
            	if(!(&matriz[*keyRow][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn - 1;
                	//cout << "\n\nPARA ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 1){ //      PARA DIAGONAL SUPERIOR ESQUERDA
            	if(!(&matriz[*keyRow-1][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	*keyColumn = *keyColumn - 1;
                	//cout << "\n\nPARA DIAGONAL SUPERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 2){ //      PARA CIMA
            	if(!(&matriz[*keyRow-1][*keyColumn] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
               		*keyRow = *keyRow - 1;
					//cout << "\n\nPARA CIMA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 3){ //      PARA DIAGONAL SUPERIOR DIREITA
            	if(!(&matriz[*keyRow-1][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	*keyColumn = *keyColumn + 1;
                	//cout << "\n\nPARA DIAGONAL SUPERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 4){ //      PARA DIREITA
            	if(!(&matriz[*keyRow][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn + 1;
					//cout << "\n\nPARA DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
        }
        else if(*keyColumn == 0){ //      BORDA ESQUERDA
        	//cout << "\n\nBORDA ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
            nextStreet = rand() % 8;
            if(nextStreet == 0){ //      PARA DIAGONAL SUPERIOR ESQUERDA
            	if(!(&this->anterior->matriz[*keyRow-1][this->tamanhoColuna-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	*keyColumn = this->tamanhoColuna-1; 
                	//cout << "\n\nPARA DIAGONAL SUPERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		         	   *caminho = true;
		       		}
                	return false;	
				}
            }
            else if(nextStreet == 1){ //      PARA CIMA
            	if(!(&matriz[*keyRow-1][*keyColumn] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
					//cout << "\n\nPARA CIMA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 2){ //      PARA DIAGONAL SUPERIOR DIREITA
            	if(!(&matriz[*keyRow-1][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	*keyColumn = *keyColumn + 1; 	
                	//cout << "\n\nPARA DIAGONAL SUPERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 3){ //      PARA DIREITA
            	if(!(&matriz[*keyRow][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn + 1;
					//cout << "\n\nPARA DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 4){ //     DIAGONAL INFERIOR DIREITA
            	if(!(&matriz[*keyRow+1][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;
                	*keyColumn = *keyColumn + 1;
					//cout << "\n\nPARA DIAGONAL INFERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 5){ //      PARA BAIXO
            	if(!(&matriz[*keyRow+1][*keyColumn] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;	
                	//cout << "\n\nPARA BAIXO  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 6){ //     DIAGONAL INFERIOR ESQUERDA
            	if(!(&this->anterior->matriz[*keyRow+1][this->tamanhoColuna-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;
                	*keyColumn = this->tamanhoColuna-1;
                	////cout << "\n\nDIAGONAL INFERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
               		if(*keyRow == 0 && *keyColumn == 0){
		            *caminho = true;
		        	}
                	return false;	
				}
            }
            else if(nextStreet == 7){ //      PARA ESQUERDA
            	if(!(&this->anterior->matriz[*keyRow][this->tamanhoColuna-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = this->tamanhoColuna-1;
                	//cout << "\n\nPARA ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
                	if(*keyRow == 0 && *keyColumn == 0){
		        	    *caminho = true;
		        	}
                	return false;	
				}
            }
        }
        else{ //        MEIO DA MATRIZ 
        	//cout << "\n\nMEIO DA MATRIZ  [" << *keyRow << "][" << *keyColumn << "]\n\n";
        	nextStreet = rand() % 8;
            if(nextStreet == 0){ //      PARA DIAGONAL SUPERIOR ESQUERDA
            	if(!(&matriz[*keyRow-1][*keyColumn-1] == this->lastVisit)){
	            	this->lastVisit = &matriz[*keyRow][*keyColumn];
	                *keyRow = *keyRow - 1;
	                *keyColumn = *keyColumn - 1;
					//cout << "\n\nPARA DIAGONAL SUPERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 1){ //      PARA CIMA
            	if(!(&matriz[*keyRow-1][*keyColumn] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
					//cout << "\n\nPARA CIMA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				}
            }
            else if(nextStreet == 2){ //      PARA DIAGONAL SUPERIOR DIREITA
            	if(!(&matriz[*keyRow-1][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow - 1;
                	*keyColumn = *keyColumn + 1;
                	//cout << "\n\nPARA DIAGONAL SUPERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 3){ //      PARA DIREITA
            	if(!(&matriz[*keyRow][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn + 1;
					//cout << "\n\nPARA DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n"; 	
				}
            }
            else if(nextStreet == 4){ //     DIAGONAL INFERIOR DIREITA
            	if(!(&matriz[*keyRow+1][*keyColumn+1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyRow = *keyRow + 1;
                	*keyColumn = *keyColumn + 1;
					//cout << "\n\nPARA DIAGONAL INFERIOR DIREITA  [" << *keyRow << "][" << *keyColumn << "]\n\n";	
				} 
            }
            else if(nextStreet == 5){ //      PARA BAIXO
            	if(!(&matriz[*keyRow+1][*keyColumn] == this->lastVisit)){
					this->lastVisit = &matriz[*keyRow][*keyColumn];
	                *keyRow = *keyRow + 1;
	                //cout << "\n\nPARA BAIXO  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 6){ //     DIAGONAL INFERIOR ESQUERDA
            	if(!(&matriz[*keyRow+1][*keyColumn-1] == this->lastVisit)){
	         		this->lastVisit = &matriz[*keyRow][*keyColumn];
	                *keyRow = *keyRow + 1;
	                *keyColumn = *keyColumn - 1;
					//cout << "\n\nDIAGONAL INFERIOR ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
            else if(nextStreet == 7){ //      PARA ESQUERDA
            	if(!(&matriz[*keyRow][*keyColumn-1] == this->lastVisit)){
            		this->lastVisit = &matriz[*keyRow][*keyColumn];
                	*keyColumn = *keyColumn - 1;
                	//cout << "\n\nPARA ESQUERDA  [" << *keyRow << "][" << *keyColumn << "]\n\n";
				}
            }
        }
    }
    return NULL;
}
/******************************************************************************************** FINAL METODOS */