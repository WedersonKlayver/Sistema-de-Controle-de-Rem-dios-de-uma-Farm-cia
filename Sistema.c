#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   int codigo;
   char nome[100];
   char laboratorio[100];
   float preco;
   int quantidadeEstoque;
} Remedio;

/*case 1*/
void cadastrarRemedio(Remedio **vetor, int *quantidade) {
    Remedio novoRemedio;
    if (*quantidade == 0){
        *vetor = (Remedio *) malloc(sizeof(Remedio));
    } else {
        *vetor = (Remedio *) realloc(*vetor, ((*quantidade) + 1) * sizeof(Remedio));
    }

    printf("Digite o codigo do remedio: ");
    scanf("%d", &novoRemedio.codigo);
    getchar(); // limpar buffer
    printf("Digite o nome do remedio: ");
    fgets(novoRemedio.nome, 100, stdin);
    novoRemedio.nome[strcspn(novoRemedio.nome, "\n")] = '\0';
    printf("Digite o laboratorio do remedio: ");
    fgets(novoRemedio.laboratorio, 100, stdin);
    novoRemedio.laboratorio[strcspn(novoRemedio.laboratorio, "\n")] = '\0';
    printf("Digite o preco do remedio: ");
    scanf("%f", &novoRemedio.preco);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novoRemedio.quantidadeEstoque);
    (*vetor)[*quantidade] = novoRemedio;
    (*quantidade)++;
}

/*case 2*/
void venderRemedio(Remedio *vetor, int quantidade, char *nome, int quantidadeVendida) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            if (vetor[i].quantidadeEstoque >= quantidadeVendida) {
                vetor[i].quantidadeEstoque -= quantidadeVendida;
                printf("Venda realizada com sucesso\n");
            } else {
                printf("Estoque insuficiente\n");
            }
            return;
        }
    }
    printf("Remedio nao encontrado\n");
}

/*case 3*/
void relatorioEstoqueMinimo(Remedio estoque[], int tamanho) {
    int minimo;
    printf("Digite a quantidade minima: ");
    scanf("%d", &minimo);
    for (int i = 0; i < tamanho; i++) {
        if (estoque[i].quantidadeEstoque < minimo) {
            printf("Codigo: %d\nNome: %s\nLab: %s\nPreco: %.2f\nQtd: %d\n\n",
                   estoque[i].codigo,
                   estoque[i].nome,
                   estoque[i].laboratorio,
                   estoque[i].preco,
                   estoque[i].quantidadeEstoque);
        }
    }
}

/*case 4*/
float valorTotalEstoque(Remedio estoque[], int tamanho) {
    float total = 0;
    for (int i = 0; i < tamanho; i++) {
        total += estoque[i].preco * estoque[i].quantidadeEstoque;
    }
    return total;
}

/*case 5*/
void atualizarPreco(Remedio estoque[], int tamanho) {
    int codigo;
    float novoPreco;
    printf("Digite o codigo: ");
    scanf("%d", &codigo);
    for (int i = 0; i < tamanho; i++) {
        if (estoque[i].codigo == codigo) {
            printf("Novo preco: ");
            scanf("%f", &novoPreco);
            estoque[i].preco = novoPreco;
            printf("Preco atualizado!\n");
            return;
        }
    }
    printf("Remedio nao encontrado\n");
}

/*case 6*/
void contarProdutosPorCategoria(Remedio estoque[], int tamanho) {
    char categorias[100][100];
    int contagem[100] = {0};
    int total = 0;
    for (int i = 0; i < tamanho; i++) {
        int achou = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(estoque[i].laboratorio, categorias[j]) == 0) {
                contagem[j]++;
                achou = 1;
                break;
            }
        }
        if (!achou) {
            strcpy(categorias[total], estoque[i].laboratorio);
            contagem[total]++;
            total++;
        }
    }

    for (int i = 0; i < total; i++) {
        printf("Laboratorio: %s - Quantidade: %d\n", categorias[i], contagem[i]);
    }
}

/*case 7*/
Remedio* buscarRemedioPorCodigo(Remedio estoque[], int tamanho, int codigo) {
    for (int i = 0; i < tamanho; i++) {
        if (estoque[i].codigo == codigo) {
            return &estoque[i];
        }
    }
    return NULL;
}

/*case 8*/
void removerRemedio(Remedio **estoque, int *tamanho, char *nome) {
    int indice = -1;
    for (int i = 0; i < *tamanho; i++) {
        if (strcmp((*estoque)[i].nome, nome) == 0) {
            indice = i;
            break;
        }
    }
    if (indice != -1) {
        for (int i = indice; i < (*tamanho) - 1; i++) {
            (*estoque)[i] = (*estoque)[i + 1];
        }
        (*tamanho)--;
        if (*tamanho == 0) {
            free(*estoque);
            *estoque = NULL;
        } else {
            *estoque = realloc(*estoque, (*tamanho) * sizeof(Remedio));
        }
        printf("Removido com sucesso\n");
    } else {
        printf("Nao encontrado\n");
    }
}

/*case 9*/
void atualizarQuantidade(Remedio estoque[], int tamanho) {
    int codigo, qtd;
    printf("Digite o codigo: ");
    scanf("%d", &codigo);
    for (int i = 0; i < tamanho; i++) {
        if (estoque[i].codigo == codigo) {
            printf("Nova quantidade: ");
            scanf("%d", &qtd);
            estoque[i].quantidadeEstoque = qtd;
            printf("Atualizado!\n");
            return;
        }
    }
    printf("Remedio nao encontrado\n");
}

/*case 10*/
void gerarRelatorio(Remedio *vetor, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Codigo: %d\nNome: %s\nLab: %s\nPreco: %.2f\nQtd: %d\n\n",
               vetor[i].codigo,
               vetor[i].nome,
               vetor[i].laboratorio,
               vetor[i].preco,
               vetor[i].quantidadeEstoque);
    }
}

/*case 0*/
void liberarMemoria(Remedio *vetor){
    free(vetor);
}

int main (){
    int opcao;
    Remedio *vetor = NULL;
    int quantidade = 0;

    do {
        printf("\n===== MENU =====\n");
        printf("1- Cadastrar\n");
        printf("2- Vender\n");
        printf("3- Estoque minimo\n");
        printf("4- Valor total\n");
        printf("5- Atualizar preco\n");
        printf("6- Contar por laboratorio\n");
        printf("7- Buscar por codigo\n");
        printf("8- Remover\n");
        printf("9- Atualizar quantidade\n");
        printf("10- Relatorio\n");
        printf("0- Sair\n");
        printf("---------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                cadastrarRemedio(&vetor, &quantidade);
                break;
            case 2: {
                char nome[100];
                int qtd;
                getchar();
                printf("Nome: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Quantidade: ");
                scanf("%d", &qtd);
                venderRemedio(vetor, quantidade, nome, qtd);
                break;
            }
            case 3:
                relatorioEstoqueMinimo(vetor, quantidade);
                break;
            case 4:
                printf("Total: %.2f\n", valorTotalEstoque(vetor, quantidade));
                break;
            case 5:
                atualizarPreco(vetor, quantidade);
                break;
            case 6:
                contarProdutosPorCategoria(vetor, quantidade);
                break;
            case 7: {
                int cod;
                printf("Codigo: ");
                scanf("%d", &cod);
                Remedio *r = buscarRemedioPorCodigo(vetor, quantidade, cod);
                if (r != NULL) {
                    printf("Nome: %s\nPreco: %.2f\nQtd: %d\n",
                           r->nome, r->preco, r->quantidadeEstoque);
                } else {
                    printf("Nao encontrado\n");
                }
                break;
            }
            case 8: {
                char nome[100];
                getchar();
                printf("Nome: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerRemedio(&vetor, &quantidade, nome);
                break;
            }
            case 9:
                atualizarQuantidade(vetor, quantidade);
                break;
            case 10:
                gerarRelatorio(vetor, quantidade);
                break;
            case 0:
                liberarMemoria(vetor);
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (opcao != 0);
    return 0;
}