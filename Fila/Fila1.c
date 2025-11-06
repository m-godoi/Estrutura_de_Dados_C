#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// --- Estruturas da Pilha de Alunos ---
typedef struct AlunoNode {
    int numero;
    char nome[100];
    struct AlunoNode* prox;
} AlunoNode;

// --- Estruturas da Fila de Notas ---
typedef struct NotaNode {
    int numero_aluno;
    float nota;
    struct NotaNode* prox;
} NotaNode;

typedef struct FilaNotas {
    NotaNode* inicio;
    NotaNode* fim;
} FilaNotas;

// --- Funções da Pilha de Alunos ---

int pilha_isEmpty(AlunoNode* topo) {
    return topo == NULL;
}

void pilha_push(AlunoNode** topo, int numero, const char* nome) {
    AlunoNode* novoAluno = (AlunoNode*)malloc(sizeof(AlunoNode));
    if (novoAluno == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    novoAluno->numero = numero;
    strcpy(novoAluno->nome, nome);
    novoAluno->prox = *topo;
    *topo = novoAluno;
    printf("Aluno %s (No %d) cadastrado.\n", nome, numero);
}

AlunoNode* pilha_pop(AlunoNode** topo) {
    if (pilha_isEmpty(*topo)) {
        return NULL;
    }
    AlunoNode* temp = *topo;
    *topo = (*topo)->prox;
    temp->prox = NULL;
    return temp;
}

AlunoNode* pilha_peek(AlunoNode* topo) {
    return topo;
}

AlunoNode* buscar_aluno_por_numero(AlunoNode* topo, int numero) {
    AlunoNode* atual = topo;
    while (atual != NULL) {
        if (atual->numero == numero) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

// --- Funções da Fila de Notas ---

void fila_init(FilaNotas* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

int fila_isEmpty(FilaNotas* fila) {
    return fila->inicio == NULL;
}

void fila_enqueue(FilaNotas* fila, int numero_aluno, float nota) {
    NotaNode* novaNota = (NotaNode*)malloc(sizeof(NotaNode));
    if (novaNota == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    novaNota->numero_aluno = numero_aluno;
    novaNota->nota = nota;
    novaNota->prox = NULL;

    if (fila_isEmpty(fila)) {
        fila->inicio = novaNota;
        fila->fim = novaNota;
    } else {
        fila->fim->prox = novaNota;
        fila->fim = novaNota;
    }
    printf("Nota %.2f cadastrada para o aluno No %d.\n", nota, numero_aluno);
}

NotaNode* fila_dequeue(FilaNotas* fila) {
    if (fila_isEmpty(fila)) {
        return NULL;
    }
    NotaNode* temp = fila->inicio;
    fila->inicio = fila->inicio->prox;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    temp->prox = NULL;
    return temp;
}

int buscar_notas_aluno(FilaNotas* fila, int numero_aluno) {
    NotaNode* atual = fila->inicio;
    int contador = 0;
    while (atual != NULL) {
        if (atual->numero_aluno == numero_aluno) {
            contador++;
        }
        atual = atual->prox;
    }
    return contador;
}

void calcular_media(FilaNotas* fila, AlunoNode* aluno) {
    if (aluno == NULL) return;

    NotaNode* atual = fila->inicio;
    float soma = 0;
    int contador = 0;

    while (atual != NULL) {
        if (atual->numero_aluno == aluno->numero) {
            soma += atual->nota;
            contador++;
        }
        atual = atual->prox;
    }

    printf("\n--- Media do Aluno ---\n");
    printf("Numero: %d\n", aluno->numero);
    printf("Nome: %s\n", aluno->nome);
    if (contador > 0) {
        printf("Media: %.2f (%d notas)\n", (soma / contador), contador);
    } else {
        printf("Media: 0.00 (Nenhuma nota cadastrada)\n");
    }
}

void listar_alunos_sem_notas(AlunoNode* topo, FilaNotas* fila) {
    AlunoNode* atual = topo;
    int encontrou = 0;
    
    printf("\n--- Alunos Sem Notas ---\n");
    if (pilha_isEmpty(topo)) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    while (atual != NULL) {
        if (buscar_notas_aluno(fila, atual->numero) == 0) {
            printf("- %s (No %d)\n", atual->nome, atual->numero);
            encontrou = 1;
        }
        atual = atual->prox;
    }

    if (!encontrou) {
        printf("Todos os alunos possuem notas cadastradas.\n");
    }
}

// --- Função Principal ---
int main() {
    AlunoNode* pilha_alunos = NULL;
    FilaNotas fila_notas;
    fila_init(&fila_notas);
    
    int opcao, num_aluno;
    char nome_aluno[100];
    float nota_aluno;

    while(1) {
        printf("\n========= MENU DE ALUNOS E NOTAS =========\n");
        printf(" 1 - Cadastrar aluno\n");
        printf(" 2 - Cadastrar nota\n");
        printf(" 3 - Calcular media de um aluno\n");
        printf(" 4 - Listar os nomes dos alunos sem notas\n");
        printf(" 5 - Excluir aluno\n");
        printf(" 6 - Excluir nota\n");
        printf(" 7 - Sair\n");
        printf("==========================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n');
            printf("Opcao invalida. Digite um numero.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                printf("Digite o numero do aluno: ");
                scanf("%d", &num_aluno);
                printf("Digite o nome do aluno: ");
                scanf(" %[^\n]", nome_aluno); // Lê até o \n
                
                if (buscar_aluno_por_numero(pilha_alunos, num_aluno) != NULL) {
                    printf("Erro: Numero de aluno ja cadastrado!\n");
                } else {
                    pilha_push(&pilha_alunos, num_aluno, nome_aluno);
                }
                break;
            
            case 2:
                printf("Digite o numero do aluno: ");
                scanf("%d", &num_aluno);
                if (buscar_aluno_por_numero(pilha_alunos, num_aluno) == NULL) {
                    printf("Erro: Aluno nao cadastrado na pilha!\n");
                } else {
                    printf("Digite a nota: ");
                    scanf("%f", &nota_aluno);
                    fila_enqueue(&fila_notas, num_aluno, nota_aluno);
                }
                break;

            case 3:
                printf("Digite o numero do aluno para calcular a media: ");
                scanf("%d", &num_aluno);
                AlunoNode* aluno = buscar_aluno_por_numero(pilha_alunos, num_aluno);
                if (aluno == NULL) {
                    printf("Erro: Aluno nao encontrado!\n");
                } else {
                    calcular_media(&fila_notas, aluno);
                }
                break;
            
            case 4:
                listar_alunos_sem_notas(pilha_alunos, &fila_notas);
                break;

            case 5:
                if (pilha_isEmpty(pilha_alunos)) {
                    printf("Pilha de alunos esta vazia.\n");
                } else {
                    AlunoNode* aluno_topo = pilha_peek(pilha_alunos);
                    if (buscar_notas_aluno(&fila_notas, aluno_topo->numero) > 0) {
                        printf("Erro: O aluno no topo (%s) possui notas e nao pode ser excluido.\n", aluno_topo->nome);
                    } else {
                        AlunoNode* excluido = pilha_pop(&pilha_alunos);
                        printf("Aluno %s (No %d) excluido do topo da pilha.\n", excluido->nome, excluido->numero);
                        free(excluido);
                    }
                }
                break;

            case 6:
                if (fila_isEmpty(&fila_notas)) {
                    printf("Fila de notas esta vazia.\n");
                } else {
                    NotaNode* nota_excluida = fila_dequeue(&fila_notas);
                    printf("Nota %.2f (Aluno No %d) excluida do inicio da fila.\n", nota_excluida->nota, nota_excluida->numero_aluno);
                    free(nota_excluida);
                }
                break;
            
            case 7:
                printf("Saindo do programa...\n");
                // Limpar memória restante (opcional mas boa prática)
                while (!pilha_isEmpty(pilha_alunos)) {
                    AlunoNode* temp = pilha_pop(&pilha_alunos);
                    free(temp);
                }
                while (!fila_isEmpty(&fila_notas)) {
                    NotaNode* temp = fila_dequeue(&fila_notas);
                    free(temp);
                }
                exit(0);

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}