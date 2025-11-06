#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// --- Estruturas da Pilha ---
typedef struct NumNode {
    int valor;
    struct NumNode* prox;
} NumNode;

// --- Estruturas da Fila ---
typedef struct FilaNumNode {
    int valor;
    struct FilaNumNode* prox;
} FilaNumNode;

typedef struct FilaNumeros {
    FilaNumNode* inicio;
    FilaNumNode* fim;
} FilaNumeros;

// --- Funções da Pilha ---
int pilha_isEmpty(NumNode* topo) {
    return topo == NULL;
}

void pilha_push(NumNode** topo, int valor) {
    NumNode* novoNode = (NumNode*)malloc(sizeof(NumNode));
    if (novoNode == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    novoNode->valor = valor;
    novoNode->prox = *topo;
    *topo = novoNode;
}

int pilha_pop(NumNode** topo) {
    if (pilha_isEmpty(*topo)) {
        return INT_MIN; 
    }
    NumNode* temp = *topo;
    int valor = temp->valor;
    *topo = (*topo)->prox;
    free(temp);
    return valor;
}

void pilha_print(NumNode* topo, const char* titulo) {
    printf("\n--- %s ---\n", titulo);
    if (pilha_isEmpty(topo)) {
        printf("Pilha Vazia.\n");
        return;
    }
    NumNode* atual = topo;
    while (atual != NULL) {
        printf("%d\n", atual->valor);
        atual = atual->prox;
    }
    printf("------------\n");
}

// --- Funções da Fila ---
void fila_init(FilaNumeros* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

int fila_isEmpty(FilaNumeros* fila) {
    return fila->inicio == NULL;
}

void fila_enqueue(FilaNumeros* fila, int valor) {
    FilaNumNode* novoNode = (FilaNumNode*)malloc(sizeof(FilaNumNode));
    if (novoNode == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    novoNode->valor = valor;
    novoNode->prox = NULL;

    if (fila_isEmpty(fila)) {
        fila->inicio = novoNode;
        fila->fim = novoNode;
    } else {
        fila->fim->prox = novoNode;
        fila->fim = novoNode;
    }
}

void fila_print(FilaNumeros* fila, const char* titulo) {
    printf("\n--- %s ---\n", titulo);
    if (fila_isEmpty(fila)) {
        printf("Fila Vazia.\n");
        return;
    }
    FilaNumNode* atual = fila->inicio;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("\n------------\n");
}

// --- Função Principal ---
int main() {
    NumNode* pilha = NULL;
    FilaNumeros fila_pares;
    FilaNumeros fila_impares;
    
    fila_init(&fila_pares);
    fila_init(&fila_impares);
    
    int numero;

    printf("--- Cadastro de Numeros na Pilha ---\n");
    while(1) {
        printf("Digite um numero (<= 0 para parar): ");
        if (scanf("%d", &numero) != 1) {
             while(getchar() != '\n');
             printf("Entrada invalida. Digite um numero.\n");
             continue;
        }
        
        if (numero <= 0) {
            break;
        }
        pilha_push(&pilha, numero);
    }

    pilha_print(pilha, "Pilha Original Digitada");

    while (!pilha_isEmpty(pilha)) {
        int valor = pilha_pop(&pilha);
        
        if (valor % 2 == 0) {
            fila_enqueue(&fila_pares, valor);
        } else {
            fila_enqueue(&fila_impares, valor);
        }
    }

    fila_print(&fila_pares, "Fila de Numeros Pares");
    fila_print(&fila_impares, "Fila de Numeros Impares");

    // Limpar memória restante (opcional)
    FilaNumNode *tempFila;
    while (fila_pares.inicio != NULL) {
        tempFila = fila_pares.inicio;
        fila_pares.inicio = fila_pares.inicio->prox;
        free(tempFila);
    }
    while (fila_impares.inicio != NULL) {
        tempFila = fila_impares.inicio;
        fila_impares.inicio = fila_impares.inicio->prox;
        free(tempFila);
    }

    return 0;
}