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

typedef struct No No;      // simplifica a declara��o
No *raiz = NULL;           // ponteiro global para o in�cio da �rvore

// Cria um novo n�
No *novoNo(int valor) {
    No *n = (No*)malloc(sizeof(No)); //aloca espa�o na mem�ria
    n->valor = valor; // define o valor armazenado
    n->esq = NULL;  // sem filho � esquerda
    n->dir = NULL; // sem filho � direita
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

// Encontra o menor valor (usado na exclus�o)
No* menorNo(No* node) {
    No* atual = node;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

// Rota��es
// Rota��o simples � direita
No* rotacaoDireita(No *y) {
    No *x = y->esq;
    No *T2 = x->dir;

    // Realiza rota��o
    x->dir = y;
    y->esq = T2;

    // Atualiza alturas
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    // Novo n� raiz
    return x;
}

// Rota��o simples � esquerda
No* rotacaoEsquerda(No *x) {
    No *y = x->dir;
    No *T2 = y->esq;

    // Realiza rota��o
    y->esq = x;
    x->dir = T2;

    // Atualiza alturas
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    // Novo n� raiz
    return y;
}


// Declara��o das fun��es -------
void criarArvore();
void inserirElemento(int num);
void excluirElemento(int num);
void buscarElemento(int num);
void editarElemento(int num);
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
				int num;
				printf("\nDigite o valor a ser inserido: ");
    			scanf("%d", &num);
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
 				exibirPreOrdem(raiz);
 				break;
 			}
 			case 7: { //Camila
 				exibirPosOrdem(raiz);
 				break;
 			}
 			case 8: { //Camila
 				exibirSimetrica(raiz);
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
	raiz = NULL;
    printf("\n�rvore criada com sucesso!\n");
}


// -------- Inser��o --------

No* inserir(No* node, int valor) {
    // 1. Inser��o normal de BST
    if (node == NULL) return novoNo(valor);

    if (valor < node->valor)
        node->esq = inserir(node->esq, valor);
    else if (valor > node->valor)
        node->dir = inserir(node->dir, valor);
    else
        return node; // valores duplicados n�o s�o inseridos

    // 2. Atualiza altura do n� atual
    node->altura = 1 + max(altura(node->esq), altura(node->dir));

    // 3. Calcula fator de balanceamento
    int fb = fatorBalanceamento(node);

    // 4. Corrige desbalanceamentos

    // Caso Esquerda-Esquerda
    if (fb > 1 && valor < node->esq->valor)
        return rotacaoDireita(node);

    // Caso Direita-Direita
    if (fb < -1 && valor > node->dir->valor)
        return rotacaoEsquerda(node);

    // Caso Esquerda-Direita
    if (fb > 1 && valor > node->esq->valor) {
        node->esq = rotacaoEsquerda(node->esq);
        return rotacaoDireita(node);
    }

    // Caso Direita-Esquerda
    if (fb < -1 && valor < node->dir->valor) {
        node->dir = rotacaoDireita(node->dir);
        return rotacaoEsquerda(node);
    }

    return node; // retorna o n� (possivelmente ajustado)
}

void inserirElemento(int num){
    raiz = inserir(raiz, num);
    printf("Elemento %d inserido com sucesso!\n", num);
}

// Exclui elemento
No* remover(No* raiz, int valor) {
    if (raiz == NULL) return raiz;

    if (valor < raiz->valor)
        raiz->esq = remover(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = remover(raiz->dir, valor);
    else {
        // N� encontrado
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            No *temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else
                *raiz = *temp;

            free(temp);
        } else {
            No *temp = menorNo(raiz->dir);
            raiz->valor = temp->valor;
            raiz->dir = remover(raiz->dir, temp->valor);
        }
    }

    if (raiz == NULL)
        return raiz;

    // Atualiza altura
    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    // Verifica balanceamento
    int fb = fatorBalanceamento(raiz);

    // Corrige casos de desbalanceamento
    if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);

    if (fb > 1 && fatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);

    if (fb < -1 && fatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void excluirElemento(int num) {
    printf("\nDigite o valor a ser removido: ");
    scanf("%d", &num);
    raiz = remover(raiz, num);
    printf("Elemento %d removido (se existia)!\n", num);
}

// Busca elemento
No* buscar(No* node, int valor) {
    if (node == NULL || node->valor == valor)
        return node;
    if (valor < node->valor)
        return buscar(node->esq, valor);
    else
        return buscar(node->dir, valor);
}

void buscarElemento(int num) {
    printf("\nDigite o valor a ser buscado: ");
    scanf("%d", &num);
    No* resultado = buscar(raiz, num);
    if (resultado != NULL)
        printf("Elemento %d encontrado na �rvore!\n", num);
    else
        printf("Elemento %d n�o encontrado.\n", num);
}


// Edita elemento (substitui valor existente)
void editarElemento(int num) {
    printf("\nDigite o valor a ser editado: ");
    scanf("%d", &num);
    No* alvo = buscar(raiz, num);
    if (alvo != NULL) {
        int novo;
        printf("Digite o novo valor: ");
        scanf("%d", &novo);
        raiz = remover(raiz, num);
        raiz = inserir(raiz, novo);
        printf("Valor %d alterado para %d!\n", num, novo);
    } else {
        printf("Elemento n�o encontrado!\n");
    }
}

// Percursos

// Fun��o que exibe a �rvore em pr�-ordem (raiz -> esquerda -> direita)
void exibirPreOrdem(struct No* no){
    if (no != NULL) { // verifica se o ponteiro passado n�o � NULL (ou seja, existe n�)
        printf("%d ", no->chave); // visita (imprime) o valor do n� atual (a "raiz" do sub�rvore)
        exibirPreOrdem(no->esq); // chama a fun��o que percorre recursivamente a sub�rvore esquerda
        exibirPreOrdem(no->dir); // chama a fun��o que percorre recursivamente a sub�rvore direita
    }
    printf("\n");
}

// Fun��o que exibe a �rvore em p�s-ordem (esquerda -> direita -> raiz)
void exibirPosOrdem(struct No* no){
    if (no != NULL) { // verifica se o n� existe
        exibirPosOrdem(no->esq); // percorre recursivamente a sub�rvore esquerda primeiro
        exibirPosOrdem(no->dir); // depois percorre recursivamente a sub�rvore direita
        printf("%d ", no->chave); // por �ltimo visita (imprime) o n� atual (raiz do sub�rvore)
    }
    printf("\n");
}

// Fun��o que exibe a �rvore em ordem sim�trica / in-order (esquerda -> raiz -> direita)
void exibirSimetrica(struct No* no){
    if (no != NULL) {  // verifica se o ponteiro passado aponta para um n� v�lido
        exibirSimetrica(no->esq); // percorre recursivamente a sub�rvore esquerda
        printf("%d ", no->chave); // visita (imprime) o n� atual depois da esquerda (in-order)
        exibirSimetrica(no->dir); // percorre recursivamente a sub�rvore direita
    }
    printf("\n");
}

void exibirGrafos(){
	printf("j");
}
