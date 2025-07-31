#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char telefone[12];
} Contato;

void salvarContatosNoArquivo(const Contato contatos[], int numContatos);
int carregarContatos(Contato contatos[]);
int compararContatos(const void *a, const void *b);
void mostrarContatos(const Contato contatos[], int numContatos);
void apagarContato(Contato contatos[], int *numContatos);
void exibirMenu();


int main() {
    int opcao;
    Contato contatos[100];
    int numContatos;

    do {
        exibirMenu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcao) {
            case 1:
                numContatos = carregarContatos(contatos);
                qsort(contatos, numContatos, sizeof(Contato), compararContatos);
                mostrarContatos(contatos, numContatos);
                break;

            case 2:
                numContatos = carregarContatos(contatos);
                if (numContatos >= 100) {
                    printf("A agenda esta cheia! Nao e possivel adicionar mais contatos.\n");
                    break;
                }
                
                Contato novoContato;
                printf("\n--- Adicionar Novo Contato ---\n");
                printf("Digite o nome do contato: ");
                fgets(novoContato.nome, sizeof(novoContato.nome), stdin);
                novoContato.nome[strcspn(novoContato.nome, "\n")] = '\0';

                printf("Digite o telefone do contato: ");
                fgets(novoContato.telefone, sizeof(novoContato.telefone), stdin);
                novoContato.telefone[strcspn(novoContato.telefone, "\n")] = '\0';

                contatos[numContatos] = novoContato;
                numContatos++;

                qsort(contatos, numContatos, sizeof(Contato), compararContatos);
                salvarContatosNoArquivo(contatos, numContatos);

                printf("\n[OK] Contato '%s' adicionado e agenda reordenada com sucesso!\n", novoContato.nome);
                break;

            case 3:
                numContatos = carregarContatos(contatos);
                apagarContato(contatos, &numContatos);
                break;

            case 0:
                printf("\nSaindo do programa. Ate mais!\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
    } while (opcao != 0);

    return 0;
}


void salvarContatosNoArquivo(const Contato contatos[], int numContatos) {
    FILE *arquivo = fopen("Agenda.txt", "w");
    if (arquivo == NULL) {
        perror("Nao foi possivel salvar as alteracoes no arquivo");
        return;
    }
    for (int i = 0; i < numContatos; i++) {
        fprintf(arquivo, "Nome: %s\nTelefone: %s\n--------------------\n",
                contatos[i].nome, contatos[i].telefone);
    }
    fclose(arquivo);
}

void apagarContato(Contato contatos[], int *numContatos) {
    if (*numContatos == 0) {
        printf("\nA agenda esta vazia. Nao ha contatos para apagar.\n");
        return;
    }
    printf("\n--- Qual contato voce deseja apagar? ---\n");
    for (int i = 0; i < *numContatos; i++) {
        printf("%d. %s\n", i + 1, contatos[i].nome);
    }
    printf("----------------------------------------\n");

    int escolha;
    printf("Digite o numero do contato (ou 0 para cancelar): ");
    scanf("%d", &escolha);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (escolha == 0) { printf("Operacao cancelada.\n"); return; }
    if (escolha < 1 || escolha > *numContatos) { printf("Opcao invalida.\n"); return; }

    int indiceParaApagar = escolha - 1;
    printf("\nApagando o contato: %s\n", contatos[indiceParaApagar].nome);

    for (int i = indiceParaApagar; i < *numContatos - 1; i++) {
        contatos[i] = contatos[i + 1];
    }
    (*numContatos)--;
    salvarContatosNoArquivo(contatos, *numContatos);
    printf("[OK] Contato apagado com sucesso!\n");
}

int compararContatos(const void *a, const void *b) {
    return strcmp(((Contato *)a)->nome, ((Contato *)b)->nome);
}

void mostrarContatos(const Contato contatos[], int numContatos) {
    if (numContatos == 0) {
        printf("Nenhum contato na agenda.\n");
        return;
    }
    printf("\n--- Lista de Contatos (Ordem Alfabética) ---\n");
    for (int i = 0; i < numContatos; i++) {
        printf("Nome: %s\nTelefone: %s\n----------------------------------------\n",
               contatos[i].nome, contatos[i].telefone);
    }
}

int carregarContatos(Contato contatos[]) {
    FILE *arquivo = fopen("Agenda.txt", "r");
    if (arquivo == NULL) return 0;
    int numContatos = 0;
    while (numContatos < 100 && fscanf(arquivo, "Nome: %[^\n]\nTelefone: %[^\n]\n--------------------\n",
           contatos[numContatos].nome, contatos[numContatos].telefone) == 2) {
        numContatos++;
    }
    fclose(arquivo);
    return numContatos;
}

void exibirMenu() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("---------- AGENDA DE CONTATOS ----------\n");
    printf("1. Mostrar lista de Contatos\n");
    printf("2. Adicionar Contato\n");
    printf("3. Apagar Contato\n");
    printf("0. Sair\n");
    printf("----------------------------------------\n");
}
