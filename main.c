#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include "lista.h"

int main()
{
    char op;
    char l; // lixo
    char *n1, *n2;
    criarLogs();
    Historico *H=criarHistorico();
    Numero *A = criar();
    Numero *B = criar();
    Numero *C = criar();
    Numero *R = criar();

    printf("\nEscolha uma das opcoes a baixo:\n");
    printf("A- Comecar operacao nova\n");
    printf("B- Limpar historico\n");
    printf("C- Exibir Historico de operacoes\n");
    printf("D- Limpar Terminal\n");
    printf("X- Encerrar o programa\n\n");

    scanf("%c", &op);
    scanf("%c", &l);
    op = toupper(op);
    fflush(stdin);

    while (op != 'X')
    {
        printf("\n");

        switch (op)
        {
        case 'A':
            // funcao de comecar nova operacao aqui
            opcaoA(A, B, C, R, H);
            limpar(A);
            limpar(B);
            limpar(C);
            limpar(R);
            printf("\n\nOperacao Realizada!");
            break;

        case 'B':
            // funcao de limpar queue das operacoes aqui
            limparHistorico(H);
            printf("\nClear Realizado!");
            break;

        case 'C':
            // funcao de mostrar historico
            mostrarHistorico(H);
            printf("\nHistorico Exibido");
            break;

        case 'D':
            system("cls");
            break;

        case 'X':
            limpar(A);
            limpar(B);
            limpar(C);
            limpar(R);
            limparHistorico(H);
            free(A);
            free(B);
            free(C);
            free(R);
            free(H);
            A=NULL;
            B=NULL;
            C=NULL;
            R=NULL;
            H=NULL;
            return 0;

        default:
            fprintf(stderr, "\nINPUT INVALIDO!");
        }

        printf("\nEscolha uma das opcoes a baixo:\n");
        printf("A- Comecar operacao nova\n");
        printf("B- Limpar historico\n");
        printf("C- Exibir Historico de operacoes\n");
        printf("D- Limpar Terminal\n");
        printf("X- Encerrar o programa\n\n");

        scanf("%c", &op);
        scanf("%c", &l);
        op = toupper(op);
        fflush(stdin);
    }

    return 0;
}
