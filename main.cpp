#include <stdio.h>
#include <locale.h>

// Declaração das funções -------
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
	
	printf("\a----- ÁRVORE AVL -----\n\n");
	
	printf("\t\tMENU\n");
	printf("0 - Sair\n"
	       "1 - Criar Árvore Vazia\n"
		   "2 - Inserir Elemento da Árvore\n"
		   "3 - Excluir Elemento da Árvore\n"
		   "4 - Editar Elemento da Árvore\n"
		   "5 - Buscar Elemento da Árvora\n"
		   "6 - Exibir em Pré-ordem\n"
		   "7 - Exibir em Pós-ordem\n"
		   "8 - Exibir em Ordem Simétrica\n"
		   "9 - Exibir em Grafos");

	do{	
		printf("\nDigite a opção desejada (0 a 9): ");
		scanf("%d", &op);	
		while(op < 0 || op > 9){
			printf("\n\n\aValor inválido, digite novamente!\n");
			printf("Digite a opção desejada (0 a 9): ");
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
				//se não existir árvore chamar a função 1
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
 				//Retorna se o elemento existe ou não 
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

// Funções -----
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
