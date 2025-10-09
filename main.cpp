#include <stdio.h> //entrada e sa�da de dados
#include <stdlib.h> //cont�m as fun��es de aloca��o din�mica
#include <locale.h> //altera o idioma do programa 


// Estrutura do n� da �rvore
struct No {
    int valor;             // valor guardado no n�
    struct No *esq;        // ponteiro para filho da esquerda
    struct No *dir;        // ponteiro para filho da direita
    int altura;            // altura do n� (necess�rio para balancear)
};

// Cria um novo n�
No *novoNo(int valor) {
    No *n = (No*)malloc(sizeof(No)); //abrir um espa�o na mem�ria
    n->valor = valor;
    n->esq = NULL;
    n->dir = NULL;
    n->altura = 1; //contador para o fb
    return n;
}

// Fun��o auxiliar para pegar altura
int altura(No* n) {
    if (n == NULL) 
		return 0; //o n� n�o existe
		
    return n->altura; //retorna a altura
}

// Calcula fator de balanceamento
	//Se FB = 0, 1 ou -1 -> est� balanceado.
	//Se FB = +2 ou -2 -> precisa de rota��o para corrigir.
int fatorBalanceamento(No *n) {
    if (n == NULL) 
		return 0;
    return altura(n->esq) - altura(n->dir);
}

// Retorna o maior entre dois valores 
int max(int a, int b) {
    if (a > b) {
        return a;   // se a for maior, retorna a
    } else {
        return b;   // caso contr�rio, retorna b
    }
}

// Declara��o das fun��es -------
void criarArvore();
void inserirElemento(int num);
void excluirElemento(int num);
void editarElemento(int num);
void buscarElemento(int num);
void exibirPreOrdem();
void exibirPosOrdem();
void exibirSimetrica();
void exibirGrafos();


int main(){
	setlocale(LC_ALL, "Portuguese");
	int op;
	
	printf("\a----- �RVORE AVL -----\n\n");
	
	printf("\t\tMENU\n");
	printf("0 - Sair\n"
	       "1 - Criar �rvore Vazia\n"
		   "2 - Inserir Elemento da �rvore\n"
		   "3 - Excluir Elemento da �rvore\n"
		   "4 - Editar Elemento da �rvore\n"
		   "5 - Buscar Elemento da �rvora\n"
		   "6 - Exibir em Pr�-ordem\n"
		   "7 - Exibir em P�s-ordem\n"
		   "8 - Exibir em Ordem Sim�trica\n"
		   "9 - Exibir em Grafos");

	do{	
		printf("\nDigite a op��o desejada (0 a 9): ");
		scanf("%d", &op);	
		while(op < 0 || op > 9){
			printf("\n\n\aValor inv�lido, digite novamente!\n");
			printf("Digite a op��o desejada (0 a 9): ");
			scanf("%d", &op);
		}
		
		switch (op) {
			case 0: {
				break;
			}
			case 1: { //Thais
				criarArvore();
				break;
			}
			case 2: { //Thais
				//se n�o existir �rvore chamar a fun��o 1
				int num = 0;
				inserirElemento(num);
				break;
			}
			case 3: { //Thais
				int num = 0;
				buscarElemento(num);
				excluirElemento(num);
				break;
			}
			case 4: { //Fabricio
				int num = 0;
				buscarElemento(num);
				editarElemento(num);
				break;
			}
			case 5: { //Fabricio
				int num = 0;
 				buscarElemento(num);
 				//Retorna se o elemento existe ou n�o 
 				break;
 			}
 			case 6: { //Camila
 				exibirPreOrdem();
 				break;
 			}
 			case 7: { //Camila
 				exibirPosOrdem();
 				break;
 			}
 			case 8: { //Camila
 				exibirSimetrica();
 				break;
 			}
 			case 9: { //Fabricio
 				exibirGrafos();
 				break;
 			}
		}	
	}while(op != 0);
	
}

// Fun��es -----


void criarArvore(){
	printf("b");
}

void inserirElemento(int num){
	printf("c");
}

void excluirElemento(int num){
	printf("d");
}

void editarElemento(int num){
	printf("e");
}

void buscarElemento(int num){
	printf("f");
}

void exibirPreOrdem(){
	printf("g");
}

void exibirPosOrdem(){
	printf("h");
}

void exibirSimetrica(){
	printf("i");
}

void exibirGrafos(){
	printf("j");
}


