#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    char telefone[12];
} Contato;

void exibirMenu() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("---------- MENU PRINCIPAL ----------\n");
    printf("1. Opcao 1: Mostrar lista de Contatos\n");
    printf("2. Opcao 2: Adicionar Contatos\n");
    printf("3. Opcao 3: Apagar Contato\n");
    printf("0. Sair\n");
    printf("----------------------------------\n");
}

int main() {
    int opcao;

    do {
        exibirMenu();

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nExecutando a Opcao 1...\n\n");
                break;

            case 2:
                printf("\nExecutando a Opcao 2...\n\n");
                break;

            case 3:
                printf("\nExecutando a Opcao 3...\n\n");
                break;

            case 0:
                printf("\nSaindo do programa. Ate mais!\n\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n\n");
                break;
        }

        if (opcao != 0) {
            printf("Pressione Enter para continuar...");
            getchar();
            getchar();
        }

    } while (opcao != 0);

    return 0;
}
