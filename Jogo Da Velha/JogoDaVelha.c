#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
void limparTela() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void imprimirTabuleiro(char tabuleiro[3][3]) {
    printf("\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
    printf("     |     |     \n");
    printf("\n");
}

bool Ganhou(char tabuleiro[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        if((tabuleiro[i][0] == 'X' || tabuleiro[i][0] == 'O') && (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]))
        {
            return true;
        }
        if((tabuleiro[0][i] == 'X' || tabuleiro[0][i] == 'O') && (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i]))
        {
            return true;
        }
    }
    if((tabuleiro[1][1] == 'X' || tabuleiro[1][1] == 'O') && (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]))
    {
        return true;
    }
    if((tabuleiro[1][1] == 'X' || tabuleiro[1][1] == 'O') && (tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[0][2]))
    {
        return true;
    }
    return false;
}

bool isJogadaValida(char tabuleiro[3][3], char jogada)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(tabuleiro[i][j] == jogada)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    char tabuleiro[3][3];
    int turno = 0;
    char jogadorAtual = 'X';
    int jogadaInt;
    char jogadaChar;

    int casa = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = casa + '0';
            casa++;
        }
    }

    while (true) {
        limparTela();
        imprimirTabuleiro(tabuleiro);
        printf("É a vez do Jogador '%c'.\n", jogadorAtual);
        
        while (true) {
            printf("Escolha uma casa (1-9): ");
            scanf("%d", &jogadaInt);
            jogadaChar = jogadaInt + '0';

            if (jogadaInt >= 1 && jogadaInt <= 9 && isJogadaValida(tabuleiro, jogadaChar)) {
                break;
            } else {
                printf("Jogada inválida ou casa ocupada. Tente novamente.\n");
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tabuleiro[i][j] == jogadaChar) {
                    tabuleiro[i][j] = jogadorAtual;
                }
            }
        }

        if (Ganhou(tabuleiro)) {
            imprimirTabuleiro(tabuleiro);
            printf("\n*** PARABÉNS! O Jogador '%c' venceu! ***\n", jogadorAtual);
            break;
        }
        
        turno++;

        if (turno == 9) {
            imprimirTabuleiro(tabuleiro);
            printf("\n*** DEU VELHA! O jogo empatou! ***\n");
            break;
        }

        if (jogadorAtual == 'X') {
            jogadorAtual = 'O';
        } else {
            jogadorAtual = 'X';
        }
    }

    printf("\n--- Fim de Jogo ---\n");
    return 0;
}
