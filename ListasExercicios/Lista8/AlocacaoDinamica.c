#include <stdio.h>
#include <stdlib.h>

typedef struct Elemento {
    int valor;
    struct Elemento* prox;
} Elemento;

typedef struct {
    Elemento* inicio;
    Elemento* fim;
} Fila;

Fila* criarFila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void enfileirar(Fila* f, int v) {
    Elemento* novo = (Elemento*)malloc(sizeof(Elemento));
    novo->valor = v;
    novo->prox = NULL;

    if (f->fim != NULL) {
        f->fim->prox = novo;
    } else {
        f->inicio = novo;
    }
    f->fim = novo;
}

int desenfileirar(Fila* f) {
    if (f->inicio == NULL) return -1;

    Elemento* temp = f->inicio;
    int v = temp->valor;
    f->inicio = temp->prox;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(temp);
    return v;
}

void imprimirFila(Fila* f) {
    Elemento* atual = f->inicio;
    printf("Fila: ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("\n");
}

void liberarFila(Fila* f) {
    while (f->inicio != NULL) {
        desenfileirar(f);
    }
    free(f);
}

int main() {
    Fila* minhaFila = criarFila();

    enfileirar(minhaFila, 10);
    enfileirar(minhaFila, 20);
    enfileirar(minhaFila, 30);
    imprimirFila(minhaFila);

    printf("Removido: %d\n", desenfileirar(minhaFila));
    imprimirFila(minhaFila);

    enfileirar(minhaFila, 40);
    imprimirFila(minhaFila);

    liberarFila(minhaFila);

    return 0;
}