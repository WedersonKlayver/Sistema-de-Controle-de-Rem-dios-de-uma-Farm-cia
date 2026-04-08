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
    if (*quantidade == 0 ){
        (*vetor) = (Remedio *) malloc(sizeof(Remedio));
    }   else {
            (*vetor) = (Remedio *) realloc((*vetor), ((*quantidade) + 1) * sizeof(Remedio));
        }  
     printf("Digite o codigo do remedio: ");
    scanf("%d", &novoRemedio.codigo);
    printf("Digite o nome do remedio: ");
    fgets(novoRemedio.nome, 100, stdin);
    novoRemedio.nome[strcspn(novoRemedio.nome, "\n")] = '\0';

    printf("Digite o laboratorio do remedio: ");
    fgets(novoRemedio.laboratorio, 100, stdin);
    novoRemedio.laboratorio[strcspn(novoRemedio.laboratorio, "\n")] = '\0';

    printf("Digite o preco do remedio: ");
    scanf("%f", &novoRemedio.preco);
    printf("Digite a quantidade em estoque do remedio: ");
    scanf("%d", &novoRemedio.quantidadeEstoque);
    (*vetor)[*quantidade] = novoRemedio;
    (*quantidade)++;
}
/*case 2*/
void listarRemedios(Remedio *vetor, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Codigo: %d\n", vetor[i].codigo);
        printf("Nome: %s\n", vetor[i].nome);
        printf("Laboratorio: %s\n", vetor[i].laboratorio);
        printf("Preco: %.2f\n", vetor[i].preco);
        printf("Quantidade em estoque: %d\n", vetor[i].quantidadeEstoque);
        printf("--------------------\n");
    }
}
/*case 3*/
int buscarRemedioPorNome(Remedio *vetor, int quantidade, char *nome){
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            printf("Codigo: %d\n", vetor[i].codigo);
            printf("Nome: %s\n", vetor[i].nome);
            printf("Laboratorio: %s\n", vetor[i].laboratorio);
            printf("Preco: %.2f\n", vetor[i].preco);
            printf("Quantidade em estoque: %d\n", vetor[i].quantidadeEstoque);
            printf("--------------------\n");
            return i;
        } 
    }
    printf("Remedio nao encontrado\n");
    return -1;
}
/*case 4*/
int buscarRemedioPorCodigo(Remedio *vetor, int quantidade, int codigo) {
    for (int i = 0; i < quantidade; i++){
        if(vetor[i].codigo == codigo) {
            printf("Codigo: %d\n", vetor[i].codigo);
            printf("Nome: %s\n", vetor[i].nome);
            printf("Laboratorio: %s\n", vetor[i].laboratorio);
            printf("Preco: %.2f\n", vetor[i].preco);
            printf("Quantidade em estoque: %d\n", vetor[i].quantidadeEstoque);
            printf("--------------------\n");   
            return i;
        }
    }
    printf("Remedio nao encontrado\n");
    return -1;
}
/*case 5*/
void venderRemedio(Remedio *vetor, int quantidade, char *nome, int quantidadeVendida) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            if (vetor[i].quantidadeEstoque >= quantidadeVendida) {
                vetor[i].quantidadeEstoque -= quantidadeVendida;
                printf("Venda realizada com sucesso\n");
            } else {
                printf("Quantidade em estoque insuficiente\n");
            }
            return;
        }
    }
    printf("Remedio nao encontrado\n");
}
/*case 6*/
void removerRemedio(Remedio **vetor, int *quantidade, char *nome) {
    int indice = buscarRemedioPorNome(*vetor, *quantidade, nome);
    if (indice != -1) {
        for (int i = indice; i < (*quantidade) - 1; i++) {
            (*vetor)[i] = (*vetor)[i + 1];
        }
        (*quantidade)--;
        if (*quantidade == 0) {
            free(*vetor);
            *vetor = NULL;
        } else {
            *vetor = (Remedio *) realloc(*vetor, (*quantidade) * sizeof(Remedio));
        }
        printf("Remedio removido com sucesso\n");
    } else {
        printf("Remedio nao encontrado\n");
    }
}
/*case 7*/
void liberarMemoria(Remedio *vetor){
    if (vetor != NULL){
    free(vetor);
    }
}

int main (){
    int opcao;
    Remedio *vetor = NULL;
    int quantidade = 0;
    do{
        printf("----- Sistema de Gerenciamento de Remedios -----\n");
        printf("1- Cadastrar remedio\n");
        printf("2- Listar remedios\n");
        printf("3- Buscar remedio pelo nome\n");
        printf("4- Buscar remedio pelo codigo\n");
        printf("5- Vender remedio\n");
        printf("6- Remover remedio pelo nome\n");
        printf("7- Sair\n");
        printf("---------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Cadastrar remedio\n");
                cadastrarRemedio(&vetor, &quantidade);
                break;
            case 2:
                printf("Listar remedios\n");
                listarRemedios(vetor, quantidade);
                break;
            case 3: {
                char nome[100];
                printf("Buscar remedio pelo nome\n");
                printf("Digite o nome do remedio: ");
                getchar();
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                buscarRemedioPorNome(vetor, quantidade, nome);
                break;
            }
            case 4: {
                int codigo;
                printf("Buscar remedio pelo codigo\n");
                printf("Digite o codigo do remedio: ");
                scanf("%d", &codigo);
                buscarRemedioPorCodigo(vetor, quantidade, codigo);
                break;
            }
            case 5: {
                char nomeVenda[100];
                int quantidadeVendida;
                printf("Vender remedio\n");
                printf("Digite o nome do remedio: ");
                while (getchar() != '\n');
                fgets(nomeVenda, 100, stdin);
                nomeVenda[strcspn(nomeVenda, "\n")] = '\0';
                printf("Digite a quantidade vendida: ");
                scanf("%d", &quantidadeVendida);
                venderRemedio(vetor, quantidade, nomeVenda, quantidadeVendida);
                break;
            }
            case 6: {
                char nomeRemover[100];
                printf("Remover remedio pelo nome\n");
                printf("Digite o nome do remedio: ");
                while (getchar() != '\n');
                fgets(nomeRemover, 100, stdin);
                nomeRemover[strcspn(nomeRemover, "\n")] = '\0';
                removerRemedio(&vetor, &quantidade, nomeRemover);
                break;
            }
            case 7:
                printf("Saindo...\n");
                liberarMemoria(vetor);
                break;
            default:
                printf("Opcao invalida\n");
        }

    } while (opcao != 7);

    return 0;
}