#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char caracter;
    struct No* prox;
} No;

typedef struct {
    No* topo;
} Pilha;

Pilha* criarPilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void push(Pilha* p, char c) {
    No* novo = (No*)malloc(sizeof(No));
    novo->caracter = c;
    novo->prox = p->topo;
    p->topo = novo;
}

char pop(Pilha* p) {
    if (p->topo == NULL) return '\0';
    No* temp = p->topo;
    char c = temp->caracter;
    p->topo = temp->prox;
    free(temp);
    return c;
}

int estaVazia(Pilha* p) {
    return (p->topo == NULL);
}

int verificaBalanceamento(char* expressao) {
    Pilha* p = criarPilha();
    int valido = 1;

    for (int i = 0; expressao[i] != '\0'; i++) {
        char c = expressao[i];

        if (c == '(' || c == '[') {
            push(p, c);
        } else if (c == ')' || c == ']') {
            if (estaVazia(p)) {
                valido = 0;
                break;
            }
            char topo = pop(p);
            if ((c == ')' && topo != '(') || (c == ']' && topo != '[')) {
                valido = 0;
                break;
            }
        }
    }

    if (!estaVazia(p)) valido = 0;

    while (!estaVazia(p)) pop(p);
    free(p);

    return valido;
}

int main() {
    char exp1[] = "[( )]";
    char exp2[] = "([ )]";

    printf("Expressao: %s -> %s\n", exp1, verificaBalanceamento(exp1) ? "Correto" : "Incorreto");
    printf("Expressao: %s -> %s\n", exp2, verificaBalanceamento(exp2) ? "Correto" : "Incorreto");

    return 0;
}