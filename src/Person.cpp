#include "Person.hpp"

//******************************************************************************************** INICIO CONSTRUTORES */
Person::Person(){
    this->health = 10;
    this->map = Inventario();
    this->bag = Bag();
}

Person::Person(short int pntsVidas, Inventario labirinto, Bag bag){
    this->health = pntsVidas;
    this->map = labirinto;
    this->bag = bag;
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

//******************************************************************************************** FINAL GETTERS AND SETTERS */

//******************************************************************************************** INICIO METODOS */
void Person::regenerateHealth(){
    if(health < 10){
        this->health = this->health + 1;
    }
}

void Person::takesADamage(string data, Matriz matrix){
    if(health > 0){
        this->damageTotal = this->damageTotal + 1;
        this->health = this->health - 1;
    }
    else{ //    O PERSONAGEM MORREU
        this->map.create(data, matrix);
        cout << "\nFIM DE JOGO\n\n";
        cout << "O personagem morreu!\n\nResultados:\n\n";
        cout << "\n************* FIM *************\n\n";
        exit(0);
    }
}

void Person::solveMaze(){
    int row = 0, column = 0;
    int currentRow = row, currentColumn = column;
    No *no = this->map.getLista().getInicio();
    Matriz matriz = this->map.retrive("dataset/" + no->getValor());
    move(&row, &column, &currentRow, &currentColumn, &matriz, no);
    while(finishSolveMaze(no, row, column)){
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
		move(&row, &column, &currentRow, &currentColumn, &matriz, no);
    }
    cout << "\nFIM DE JOGO\n\n";
    cout << "O  último caminho percorrido possue apenas 0's\n\nResultados:\n\n";
}

void Person::move(int *keyRow, int *keyColumn, int *currentRow, int *currentColumn, Matriz *matrix, No *no){
    if(matrix->getMatriz()[*keyRow][*keyColumn].getValor() == -2){ //   É UMA PAREDE
        matrix->getMatriz()[*keyRow][*keyColumn].setVisit(true);
        *keyRow = *currentRow;
        *keyColumn = *currentColumn;
    }
    else if(matrix->getMatriz()[*keyRow][*keyColumn].getValor() == -3){ //  É UM PORTAL PARA MATRIZ ANTERIOR
        matrix->setVisit(true);
        this->map.create("dataset/" + no->getValor(), *matrix);
        no->setVisit(true);
        no = no->getAnterior();
        *matrix = this->map.retrive("dataset/" + no->getValor());
        matrix->randomStart(keyRow, keyColumn, currentRow, currentColumn);
    }
    else if(matrix->getMatriz()[*keyRow][*keyColumn].getValor() == -4){ //  É UM PORTAL PARA MATRIZ POSTERIOR
        matrix->setVisit(true);
        this->map.create("dataset/" + no->getValor(), *matrix);
        no->setVisit(true);
        no = no->getProximo();
        *matrix = this->map.retrive("dataset/" + no->getValor());
        matrix->randomStart(keyRow, keyColumn, currentRow, currentColumn);
    }
    else if(matrix->getMatriz()[*keyRow][*keyColumn].getValor() == -1){ //  É UM PERIGO
        takesADamage(no->getValor(), *matrix);
        this->bag.setForget(true);
    }
    else if(matrix->getMatriz()[*keyRow][*keyColumn].getValor() == 0){ //   É UM CAMINHO FINALIZADO
        // CONTINUA O CAMINHO SEM FAZER NADA
    }
    else{ //   É UM CAMINHO NÃO FINALIZADO
        if(this->bag.addItem()){
            regenerateHealth();
        }
        this->bag.setForget(false);
        matrix->setVisit(true);
        matrix->allowedEntry(*keyRow, *keyColumn);
    }
}

bool Person::finishSolveMaze(No *curretNo, int keyRow, int keyColumn){
    if(this->map.getLista().allVisit() && (keyRow == 0 && keyColumn == 0) && (curretNo == this->map.getLista().getInicio()) && this->bag.isForget()){
        return false;
    }
    if((curretNo == this->map.getLista().getInicio()) && (keyRow == 0 && keyColumn == 0)){ //   RESETA A CONTAGEM DO CAMINHO SEMPRE QUE VOLTAR NO INICIO
        this->bag.setForget(true);
    }
    return true;
}
//******************************************************************************************** FINAL METODOS */