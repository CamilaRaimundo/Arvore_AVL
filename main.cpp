#include <stdio.h> //entrada e saída de dados
#include <stdlib.h> //contém as funções de alocação dinâmica
#include <locale.h> //altera o idioma do programa 

// Estrutura do nó da árvore
struct No {
    int valor;             // valor guardado no nó
    struct No *esq;        // ponteiro para filho da esquerda
    struct No *dir;        // ponteiro para filho da direita
    int altura;            // altura do nó (necessário para balancear)
};

typedef struct No No;      // simplifica a declaração
No *raiz = NULL;           // ponteiro global para o início da árvore

// Cria um novo nó
No *novoNo(int valor) {
    No *n = (No*)malloc(sizeof(No)); //aloca espaço na memória
    n->valor = valor; // define o valor armazenado
    n->esq = NULL;  // sem filho à esquerda
    n->dir = NULL; // sem filho à direita
    n->altura = 1; //contador para o fb
    return n;
}

// Função auxiliar para pegar altura
int altura(No* n) {
    if (n == NULL) 
		return 0; //o nó não existe
    return n->altura; //retorna a altura
}

// Calcula fator de balanceamento
	//Se FB = 0, 1 ou -1 -> está balanceado.
	//Se FB = +2 ou -2 -> precisa de rotação para corrigir.
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
        return b;   // caso contrário, retorna b
    }
}

// Encontra o menor valor (usado na exclusão)
No* menorNo(No* node) {
    No* atual = node;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

// Rotações
// Rotação simples à direita
No* rotacaoDireita(No *y) {
    No *x = y->esq;
    No *T2 = x->dir;

    // Realiza rotação
    x->dir = y;
    y->esq = T2;

    // Atualiza alturas
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    // Novo nó raiz
    return x;
}

// Rotação simples à esquerda
No* rotacaoEsquerda(No *x) {
    No *y = x->dir;
    No *T2 = y->esq;

    // Realiza rotação
    y->esq = x;
    x->dir = T2;

    // Atualiza alturas
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    // Novo nó raiz
    return y;
}


// Declaração das funções -------
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
 				//Retorna se o elemento existe ou não 
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

// Funções -----


void criarArvore(){
	raiz = NULL;
    printf("\nÁrvore criada com sucesso!\n");
}


// -------- Inserção --------

No* inserir(No* node, int valor) {
    // 1. Inserção normal de BST
    if (node == NULL) return novoNo(valor);

    if (valor < node->valor)
        node->esq = inserir(node->esq, valor);
    else if (valor > node->valor)
        node->dir = inserir(node->dir, valor);
    else
        return node; // valores duplicados não são inseridos

    // 2. Atualiza altura do nó atual
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

    return node; // retorna o nó (possivelmente ajustado)
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
        // Nó encontrado
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
        printf("Elemento %d encontrado na árvore!\n", num);
    else
        printf("Elemento %d não encontrado.\n", num);
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
        printf("Elemento não encontrado!\n");
    }
}

// Percursos

// Função que exibe a árvore em pré-ordem (raiz -> esquerda -> direita)
void exibirPreOrdem(struct No* no){
    if (no != NULL) { // verifica se o ponteiro passado não é NULL (ou seja, existe nó)
        printf("%d ", no->chave); // visita (imprime) o valor do nó atual (a "raiz" do subárvore)
        exibirPreOrdem(no->esq); // chama a função que percorre recursivamente a subárvore esquerda
        exibirPreOrdem(no->dir); // chama a função que percorre recursivamente a subárvore direita
    }
    printf("\n");
}

// Função que exibe a árvore em pós-ordem (esquerda -> direita -> raiz)
void exibirPosOrdem(struct No* no){
    if (no != NULL) { // verifica se o nó existe
        exibirPosOrdem(no->esq); // percorre recursivamente a subárvore esquerda primeiro
        exibirPosOrdem(no->dir); // depois percorre recursivamente a subárvore direita
        printf("%d ", no->chave); // por último visita (imprime) o nó atual (raiz do subárvore)
    }
    printf("\n");
}

// Função que exibe a árvore em ordem simétrica / in-order (esquerda -> raiz -> direita)
void exibirSimetrica(struct No* no){
    if (no != NULL) {  // verifica se o ponteiro passado aponta para um nó válido
        exibirSimetrica(no->esq); // percorre recursivamente a subárvore esquerda
        printf("%d ", no->chave); // visita (imprime) o nó atual depois da esquerda (in-order)
        exibirSimetrica(no->dir); // percorre recursivamente a subárvore direita
    }
    printf("\n");
}

void exibirGrafos(){
	printf("j");
}
