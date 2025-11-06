#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100
#define MAX_FAT_STACK_SIZE 100

int isEmpty(int topo) {
    return topo == -1;
}

int isFull(int topo) {
    return topo == MAX_SIZE - 1;
}

void push(int pilha[], int *topo, int valor) {
    if (isFull(*topo)) {
        printf("Erro: Pilha cheia! Nao foi possivel cadastrar.\n");
    } else {
        *topo = *topo + 1;
        pilha[*topo] = valor;
        printf("Numero %d empilhado com sucesso.\n", valor);
    }
}

int pop(int pilha[], int *topo) {
    if (isEmpty(*topo)) {
        return INT_MIN; 
    } else {
        int valor = pilha[*topo];
        *topo = *topo - 1;
        return valor;
    }
}

int peekTopo(int pilha[], int topo) {
    return pilha[topo];
}

int peekBase(int pilha[]) {
    return pilha[0];
}

long long fatorial_com_pilha(int n) {
    if (n < 0) {
        printf("Fatorial nao definido para negativos.\n");
        return -1; 
    }
    if (n == 0) {
        return 1;
    }

    int pilha_fat[MAX_FAT_STACK_SIZE];
    int topo_fat = -1;

    for (int i = 1; i <= n; i++) {
        if (topo_fat < MAX_FAT_STACK_SIZE - 1) {
            pilha_fat[++topo_fat] = i;
        } else {
            printf("Erro: Estouro de pilha no fatorial!\n");
            return -1;
        }
    }
    
    long long resultado = 1;
    while (topo_fat != -1) { 
        resultado *= pilha_fat[topo_fat--]; 
    }

    return resultado;
}

void executar_exercicio2() {
    int entrada;
    printf("\n--- Exercicio 2: Fatorial com Pilha ---\n");
    printf("Digite um numero para calcular o fatorial: ");
    
    if (scanf("%d", &entrada) != 1) {
         while(getchar() != '\n');
         printf("Entrada invalida.\n");
         return;
    }
    
    long long saida = fatorial_com_pilha(entrada);
    if (saida != -1) {
        printf("Fatorial de %d -> %lld\n", entrada, saida);
    }
}

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

int lista_isEmpty(Stack* s) {
    return s->top == NULL;
}

void lista_push(Stack* s, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
}

int lista_pop(Stack* s) {
    if (lista_isEmpty(s)) {
        return INT_MIN;
    }
    Node* temp = s->top;
    int data = temp->data;
    s->top = s->top->next;
    free(temp);
    return data;
}

int lista_peek(Stack* s) {
    if (lista_isEmpty(s)) {
        return INT_MIN;
    }
    return s->top->data;
}

typedef struct MinStack {
    Stack* pilha_principal;
    Stack* pilha_minimos;
} MinStack;

MinStack* minStack_create() {
    MinStack* ms = (MinStack*)malloc(sizeof(MinStack));
    ms->pilha_principal = createStack();
    ms->pilha_minimos = createStack();
    return ms;
}

void minStack_empilha(MinStack* ms, int x) {
    lista_push(ms->pilha_principal, x);
    if (lista_isEmpty(ms->pilha_minimos) || x <= lista_peek(ms->pilha_minimos)) {
        lista_push(ms->pilha_minimos, x);
    }
    printf("Empilha(%d)\n", x);
}

int minStack_desempilha(MinStack* ms) {
    if (lista_isEmpty(ms->pilha_principal)) {
         printf("Desempilha (Vazio)\n");
         return INT_MIN;
    }
    int valor_removido = lista_pop(ms->pilha_principal);
    if (valor_removido == lista_peek(ms->pilha_minimos)) {
        lista_pop(ms->pilha_minimos);
    }
    printf("Desempilha() -> %d\n", valor_removido);
    return valor_removido;
}

int minStack_pegaMin(MinStack* ms) {
    if(lista_isEmpty(ms->pilha_minimos)) {
        return INT_MIN;
    }
    return lista_peek(ms->pilha_minimos);
}

void minStack_free(MinStack* ms) {
    while (!lista_isEmpty(ms->pilha_principal)) lista_pop(ms->pilha_principal);
    while (!lista_isEmpty(ms->pilha_minimos)) lista_pop(ms->pilha_minimos);
    free(ms->pilha_principal);
    free(ms->pilha_minimos);
    free(ms);
}

void executar_exercicio3() {
    printf("\n--- Exercicio 3: Teste da MinStack ---\n");
    MinStack* stack = minStack_create();
    
    minStack_empilha(stack, 5);
    minStack_empilha(stack, 3);
    minStack_empilha(stack, 7);

    int minimo = minStack_pegaMin(stack);
    printf("** pegaMin() -> %d ** (Esperado: 3)\n\n", minimo);

    minStack_desempilha(stack);

    minimo = minStack_pegaMin(stack);
    printf("** pegaMin() -> %d ** (Esperado: 3)\n\n", minimo);

    minStack_desempilha(stack);

    minimo = minStack_pegaMin(stack);
    printf("** pegaMin() -> %d ** (Esperado: 5)\n\n", minimo);
    
    minStack_free(stack);
    printf("--- Teste da MinStack Concluido ---\n");
}

void executar_exercicio4() {
    printf("\n--- Exercicio 4: Analise de Fragmento de Codigo ---\n\n");
    printf("O fragmento de programa faz o seguinte:\n");
    printf("Ele substitui uma sequencia de um ou mais caracteres 'A' (que estejam no topo da pilha) por um unico caractere 'B'.\n\n");
    printf("Detalhadamente:\n");
    printf("1. Se a pilha esta vazia, ele simplesmente empilha 'B'.\n");
    printf("2. Se a pilha nao esta vazia:\n");
    printf("   a. Se o topo NAO e 'A', ele empilha 'B' por cima.\n");
    printf("   b. Se o topo E 'A', ele entra em um loop que desempilha (remove) todos os 'A's consecutivos do topo. Apos remover todos os 'A's, ele empilha um unico 'B'.\n");
    printf("\n");
}

int main() {
    int pilha_ex1[MAX_SIZE];
    int topo_ex1 = -1;
    
    int opcao, numero;

    while (1) {
        printf("\n========= MENU PRINCIPAL =========\n");
        printf(" 1 - Cadastrar numero na pilha\n");
        printf(" 2 - Mostrar pares entre primeiro e ultimo\n");
        printf(" 3 - Excluir numero da pilha\n");
        printf(" 4 - Executar Fatorial com Pilha\n");
        printf(" 5 - Executar Teste da Min-Stack\n");
        printf(" 6 - Ver Analise do Codigo\n");
        printf(" 7 - Sair\n");
        printf("===================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n');
            printf("Opcao invalida! Digite um numero.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                printf("Digite o numero a ser cadastrado: ");
                if (scanf("%d", &numero) != 1) {
                     while(getchar() != '\n');
                     printf("Entrada invalida. Digite um numero inteiro.\n");
                } else {
                    push(pilha_ex1, &topo_ex1, numero);
                }
                break;

            case 2:
                if (isEmpty(topo_ex1)) {
                    printf("A pilha esta vazia.\n");
                } else {
                    int primeiro = peekBase(pilha_ex1);
                    int ultimo = peekTopo(pilha_ex1, topo_ex1);
                    int pares_encontrados = 0;

                    printf("Mostrando pares entre %d e %d:\n", primeiro, ultimo);
                    
                    if (primeiro <= ultimo) {
                        for (int i = primeiro; i <= ultimo; i++) {
                            if (i % 2 == 0) {
                                printf("%d ", i);
                                pares_encontrados = 1;
                            }
                        }
                    } else {
                        for (int i = primeiro; i >= ultimo; i--) {
                            if (i % 2 == 0) {
                                printf("%d ", i);
                                pares_encontrados = 1;
                            }
                        }
                    }
                    if (!pares_encontrados) {
                        printf("Nenhum numero par encontrado.");
                    }
                    printf("\n");
                }
                break;

            case 3:
                numero = pop(pilha_ex1, &topo_ex1);
                if (numero == INT_MIN) {
                    printf("A pilha ja esta vazia.\n");
                } else {
                    printf("Numero %d removido do topo da pilha (desempilhado).\n", numero);
                }
                break;

            case 4:
                executar_exercicio2();
                break;

            case 5:
                executar_exercicio3();
                break;
                
            case 6:
                executar_exercicio4();
                break;

            case 7:
                printf("Saindo do programa...\n");
                exit(0);

            default:
                printf("Opcao invalida! Escolha entre 1 e 7.\n");
        }
    }

    return 0;
}