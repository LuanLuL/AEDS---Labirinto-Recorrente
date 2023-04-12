#include "Person.hpp"

//******************************************************************************************** INICIO CONSTRUTORES */
Person::Person(){
    this->health = 10;
    this->map = Inventario();
    this->bag = Bag();
    this->moveTotal = 0;
}

Person::Person(short int pntsVidas, Inventario labirinto, Bag bag, int nbrDanoTomado, int nbrMovimentoFeito){
    this->health = pntsVidas;
    this->map = labirinto;
    this->bag = bag;
    this->damageTotal = nbrDanoTomado;
    this->moveTotal = nbrMovimentoFeito;
}
//******************************************************************************************** FINAL CONSTRUTORES */

//******************************************************************************************** INICIO GETTERS AND SETTERS */
short int Person::getHealth(){
    return this->health;
}

void Person::setHealth(short int newHealth){
    this->health = newHealth;
}

Inventario Person::getMap(){
    return this->map;
}

void Person::setMap(Inventario newMap){
    this->map = newMap;
}

Bag Person::getBag(){
    return this->bag;
}

void Person::setBag(Bag newBag){
    this->bag = newBag;
}

int Person::getDamageTotal(){
    return this->damageTotal;
}

void Person::setDamageTotal(int newDamageTotal){
    this->damageTotal = newDamageTotal;
}

int Person::getMoveTotal(){
    return this->moveTotal;
}

void Person::setMoveTotal(int newMoveTotal){
    this->moveTotal = newMoveTotal;
}

//******************************************************************************************** FINAL GETTERS AND SETTERS */

//******************************************************************************************** INICIO METODOS */
void Person::regenerateHealth(){
    if(health < 10){
        this->health = this->health + 1;
    }
}

void Person::takesADamage(string data, Matriz matrix){
    this->damageTotal = this->damageTotal + 1;
    this->health = this->health - 1;
    if(health == 0){ //    O PERSONAGEM MORREU
        this->map.create("dataset/" + data, matrix);
        printResults(true);
        exit(0);
    }
}

void Person::solveMaze(){
    No *no = this->map.getLista().getInicio();
    Matriz matriz = this->map.retrive("dataset/" + no->getValor());
    int row = 0, column = 0;
    int currentRow = row, currentColumn = column;
    matriz.randomStart(&row, &column, &currentRow, &currentColumn);
    int rowStart = row, columnStart = column;
    move(&row, &column, &currentRow, &currentColumn, &matriz, &no);
    while(finishSolveMaze(no, row, column, rowStart, columnStart)){
        switch(matriz.randomStreet(&row, &column, &currentRow, &currentColumn)){
        	case 1:
            case 4:
            { //    TELETRANSPORTA PARA A MATRIZ ANTERIOR
                this->map.create("dataset/" + no->getValor(), matriz);
                no->setVisit(true);
                no = no->getAnterior();
                matriz = this->map.retrive("dataset/" + no->getValor());
                matriz.randomStart(&row, &column, &currentRow, &currentColumn);
        		break;
			}
			case 2:
            case 3:
            { //    TELETRANSPORTA PARA A MATRIZ POSTERIOR
                this->map.create("dataset/" + no->getValor(), matriz);
                no->setVisit(true);
                no = no->getProximo();
                matriz = this->map.retrive("dataset/" + no->getValor());
				matriz.randomStart(&row, &column, &currentRow, &currentColumn);
        		break;
			}
			case 5:{
        		break;
			}
			default:{
				cerr << "ERRO...ERRO... Person.cpp::SolveMaze ...ERRO...ERRO\n\n"; 
				exit(0);
				break;
			}
		}
		move(&row, &column, &currentRow, &currentColumn, &matriz, &no);
    }
    printResults(false);
}

void Person::move(int *keyRow, int *keyColumn, int *currentRow, int *currentColumn, Matriz *matrix, No **no){
    matrix->getMatriz()[*currentRow][*currentColumn].setVisit(true);
    if(matrix->getMatriz()[*keyRow][*keyColumn].getValor() == -2){ //   É UMA PAREDE
        *keyRow = *currentRow;
        *keyColumn = *currentColumn;
    }
    else if(matrix->getMatriz()[*keyRow][*keyColumn].getValor() == -3){ //  É UM PORTAL PARA MATRIZ ANTERIOR
        this->moveTotal = this->moveTotal + 1;
        matrix->getMatriz()[*keyRow][*keyColumn].setVisit(true);
        matrix->setVisit(true);
        this->map.create("dataset/" + (*no)->getValor(), *matrix);
        (*no)->setVisit(true);
        (*no) = (*no)->getAnterior();
        *matrix = this->map.retrive("dataset/" + (*no)->getValor());
        matrix->randomStart(keyRow, keyColumn, currentRow, currentColumn);
    }
    else if(matrix->getMatriz()[*keyRow][*keyColumn].getValor() == -4){ //  É UM PORTAL PARA MATRIZ POSTERIOR
        this->moveTotal = this->moveTotal + 1;
        matrix->getMatriz()[*keyRow][*keyColumn].setVisit(true);
        matrix->setVisit(true);
        this->map.create("dataset/" + (*no)->getValor(), *matrix);
        (*no)->setVisit(true);
        (*no) = (*no)->getProximo();
        *matrix = this->map.retrive("dataset/" + (*no)->getValor());
        matrix->randomStart(keyRow, keyColumn, currentRow, currentColumn);
    }
    else if(matrix->getMatriz()[*keyRow][*keyColumn].getValor() == -1){ //  É UM PERIGO
        this->moveTotal = this->moveTotal + 1;
        //this->bag.setForget(true);
        takesADamage((*no)->getValor(), *matrix);
    }
    else if(matrix->getMatriz()[*keyRow][*keyColumn].getValor() == 0){ //   É UM CAMINHO FINALIZADO
        // CONTINUA O CAMINHO SEM FAZER NADA
        this->moveTotal = this->moveTotal + 1;
    }
    else{ //   É UM CAMINHO NÃO FINALIZADO
        this->bag.setForget(false);
        this->moveTotal = this->moveTotal + 1;
        if(this->bag.addItem()){
            regenerateHealth();
        }
        matrix->setVisit(true);
        matrix->allowedEntry(*keyRow, *keyColumn);
    }
}

bool Person::finishSolveMaze(No *curretNo, int keyRow, int keyColumn, int rowStart, int columnStart){
    if(this->map.getLista().allVisit() && (keyRow == rowStart && keyColumn == columnStart) && (curretNo == this->map.getLista().getInicio()) && this->bag.isForget()){
        return false;
    }
    if((curretNo == this->map.getLista().getInicio()) && (keyRow == rowStart && keyColumn == columnStart)){ //   RESETA A CONTAGEM DO CAMINHO SEMPRE QUE VOLTAR NO INICIO
        this->bag.setForget(true);
    }
    return true;
}
void Person::printResults(bool isDead){
    cout << "\nFIM DE JOGO\n\n";
    if(isDead){
        cout << "O personagem morreu!\n\nResultados:\n\n";
    }
    else{
        cout << "O último caminho percorrido possue apenas zeros.\n\nResultados:\n\n";
    }
    cout << "a) Quantidade de casas percorridas ao todo: " << this->moveTotal << endl;
    cout << "\nb) Soma de itens consumidos pelo caminho: " << this->bag.getItensTotal() << endl;
    cout << "\nc) Quantidade de casas que ficaram sem serem exploradas:\n";
    No *noAux = this->map.getLista().getInicio();
    int i = 1;
    do{
        cout << "\n\tMatriz " << i << ": " << this->map.selectNumbersNotAccess(noAux->getValor());
        noAux = noAux->getProximo();
        i++;
    }while(noAux != this->map.getLista().getInicio());
    cout << "\n\nd) Quantidade de perigos enfrentados ao decorrer do percurso: " << this->damageTotal << endl;
    cout << "\n************* FIM *************\n\n";
}
//******************************************************************************************** FINAL METODOS */