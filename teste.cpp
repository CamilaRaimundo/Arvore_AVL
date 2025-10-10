#include <stdio.h>  // entrada e saída de dados
#include <stdlib.h> // funções de alocação dinâmica
#include <locale.h> // suporte ao idioma

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
    No *n = (No*)malloc(sizeof(No)); // aloca espaço na memória
    n->valor = valor;
    n->esq = NULL;
    n->dir = NULL;
    n->altura = 1; // todo novo nó começa com altura 1
    return n;
}

// Retorna a altura de um nó
int altura(No* n) {
    if (n == NULL)
        return 0;
    return n->altura;
}

// Retorna o maior entre dois valores
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calcula o fator de balanceamento
// Se FB = 0, 1 ou -1 -> está balanceado.
// Se FB = +2 ou -2 -> precisa de rotação para corrigir.
int fatorBalanceamento(No *n) {
    if (n == NULL)
        return 0;
    return altura(n->esq) - altura(n->dir);
}

// Encontra o menor valor (usado na exclusão)
No* menorNo(No* node) {
    No* atual = node;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

// ------------------------- ROTAÇÕES -------------------------

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

// ------------------------- INSERÇÃO -------------------------

No* inserir(No* node, int valor) {
    // 1. Inserção normal de BST
    if (node == NULL) return novoNo(valor);

    if (valor < node->valor)
        node->esq = inserir(node->esq, valor);
    else if (valor > node->valor)
        node->dir = inserir(node->dir, valor);
    else
        return node; // valores duplicados não são inseridos

    // 2. Atualiza altura
    node->altura = 1 + max(altura(node->esq), altura(node->dir));

    // 3. Calcula fator de balanceamento
    int fb = fatorBalanceamento(node);

    // 4. Corrige desbalanceamentos
    if (fb > 1 && valor < node->esq->valor) // Esquerda-Esquerda
        return rotacaoDireita(node);

    if (fb < -1 && valor > node->dir->valor) // Direita-Direita
        return rotacaoEsquerda(node);

    if (fb > 1 && valor > node->esq->valor) { // Esquerda-Direita
        node->esq = rotacaoEsquerda(node->esq);
        return rotacaoDireita(node);
    }

    if (fb < -1 && valor < node->dir->valor) { // Direita-Esquerda
        node->dir = rotacaoDireita(node->dir);
        return rotacaoEsquerda(node);
    }

    return node; // nó sem alteração
}

void inserirElemento(int num) {
    printf("\nDigite o valor a ser inserido: ");
    scanf("%d", &num);
    raiz = inserir(raiz, num);
    printf("Elemento %d inserido com sucesso!\n", num);
}

// ------------------------- EXCLUSÃO -------------------------

No* remover(No* node, int valor) {
    if (node == NULL)
        return node;

    // Busca o nó a ser removido
    if (valor < node->valor)
        node->esq = remover(node->esq, valor);
    else if (valor > node->valor)
        node->dir = remover(node->dir, valor);
    else {
        // Nó encontrado
        if ((node->esq == NULL) || (node->dir == NULL)) {
            No *temp = node->esq ? node->esq : node->dir;

            if (temp == NULL) { // sem filhos
                temp = node;
                node = NULL;
            } else {
                *node = *temp; // copia o conteúdo
            }
            free(temp);
        } else {
            No *temp = menorNo(node->dir);
            node->valor = temp->valor;
            node->dir = remover(node->dir, temp->valor);
        }
    }

    if (node == NULL)
        return node;

    // Atualiza altura
    node->altura = 1 + max(altura(node->esq), altura(node->dir));

    // Corrige desbalanceamento
    int fb = fatorBalanceamento(node);

    if (fb > 1 && fatorBalanceamento(node->esq) >= 0)
        return rotacaoDireita(node);

    if (fb > 1 && fatorBalanceamento(node->esq) < 0) {
        node->esq = rotacaoEsquerda(node->esq);
        return rotacaoDireita(node);
    }

    if (fb < -1 && fatorBalanceamento(node->dir) <= 0)
        return rotacaoEsquerda(node);

    if (fb < -1 && fatorBalanceamento(node->dir) > 0) {
        node->dir = rotacaoDireita(node->dir);
        return rotacaoEsquerda(node);
    }

    return node;
}

void excluirElemento(int num) {
    printf("\nDigite o valor a ser removido: ");
    scanf("%d", &num);
    raiz = remover(raiz, num);
    printf("Elemento %d removido (se existia)!\n", num);
}

// ------------------------- BUSCA -------------------------

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
        printf("Elemento %d encontrado!\n", num);
    else
        printf("Elemento %d não encontrado.\n", num);
}

// ------------------------- EDIÇÃO -------------------------

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

// ------------------------- PERCURSOS -------------------------

void exibirPreOrdem(No* no) {
	if (raiz == NULL){
		printf("\aNão há árvore");
	}
    else if (no != NULL) {
        printf("%d ", no->valor);
        exibirPreOrdem(no->esq);
        exibirPreOrdem(no->dir);
    }
}

void exibirPosOrdem(No* no) {
	if (raiz == NULL){
		printf("\aNão há árvore");
	}
    else if (no != NULL) {
        exibirPosOrdem(no->esq);
        exibirPosOrdem(no->dir);
        printf("%d ", no->valor);
    }
}

void exibirSimetrica(No* no) {
	if (raiz == NULL){
		printf("\aNão há árvore");
	}
    else if (no != NULL) {
        exibirSimetrica(no->esq);
        printf("%d ", no->valor);
        exibirSimetrica(no->dir);
    }
}

void exibirGrafos() {
    printf("\nExibição gráfica ainda não implementada.\n");
}

// ------------------------- MENU PRINCIPAL -------------------------

void criarArvore() {
    raiz = NULL;
    printf("\nÁrvore criada com sucesso!\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int op;

    do {
        printf("\n----- ÁRVORE AVL -----\n");
        printf("0 - Sair\n"
               "1 - Criar Árvore Vazia\n"
               "2 - Inserir Elemento\n"
               "3 - Excluir Elemento\n"
               "4 - Editar Elemento\n"
               "5 - Buscar Elemento\n"
               "6 - Exibir Pré-Ordem\n"
               "7 - Exibir Pós-Ordem\n"
               "8 - Exibir Ordem Simétrica\n"
               "9 - Exibir Grafos\n");

        printf("\nDigite a opção desejada (0 a 9): ");
        scanf("%d", &op);

        switch (op) {
            case 1: criarArvore(); break;
            case 2: inserirElemento(0); break;
            case 3: excluirElemento(0); break;
            case 4: editarElemento(0); break;
            case 5: buscarElemento(0); break;
            case 6: printf("\nPré-Ordem: "); exibirPreOrdem(raiz); printf("\n"); break;
            case 7: printf("\nPós-Ordem: "); exibirPosOrdem(raiz); printf("\n"); break;
            case 8: printf("\nOrdem Simétrica: "); exibirSimetrica(raiz); printf("\n"); break;
            case 9: exibirGrafos(); break;
            case 0: printf("\nEncerrando programa...\n"); break;
            default: printf("\nOpção inválida!\n");
        }

    } while (op != 0);

    return 0;
}        

