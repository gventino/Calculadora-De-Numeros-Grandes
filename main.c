#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "lista.h"

int main()
{
    char op;
    char l; //lixo
    char *n1, *n2;
    Historico *historico=criar();
    printf("\nEscolha uma das opcoes a baixo:\n");
    printf("A- Comecar operacao nova\n");
    printf("B- Limpar historico\n");
    printf("C- Exibir Historico de operacoes\n");
    printf("X- Encerrar o programa\n\n");

	scanf("%c", &op);
    scanf("%c", &l);
	op = toupper(op);
	fflush(stdin);

    while(op != 'X')
	{
		printf("\n");

	    switch(op)
	    {
            case 'A':
                //funcao de comecar nova operacao aqui
                char string[50];
                int v1[30];
                int v2[30];
                int i;
                int j = 0;
                printf("\nDigite o valor 1");
                scanf("%s", string);
                for (i=0; i<10; i+=3)
                {
                    v1[j] += (string[i+2] - '0');
                    v1[j] += 10*(string[i+1] - '0');
                    v1[j] += 100*(string[i] - '0');
                    j++;
                }

                printf("\nDigite o valor 2");
                scanf("%s", string);
                for (i=0; i<10; i+=3)
                {
                    v2[j] += (string[i+2] - '0');
                    v2[j] += 10*(string[i+1] - '0');
                    v2[j] += 100*(string[i] - '0');
                    j++;
                }

                operacaoA(*n1,*n2,l);
                printf("\nOperacao Realizada!");
                break;

            case 'B':
                //funcao de limpar queue das operacoes aqui
                printf("\nClear Realizado!");
                break;

            case 'C':
                //funcao de mostrar historico
                printf("\nHistorico Exibido");
                break;

            default:
                fprintf(stderr, "INPUT INVALIDO\n");
		}

        printf("\nEscolha uma das opcoes a baixo:\n");
        printf("A- Comecar operacao nova\n");
        printf("B- Limpar historico\n");
        printf("C- Exibir Historico de operacoes\n");
        printf("X- Encerrar\n\n");

		scanf("%c", &op);
        scanf("%c", &l);
		op = toupper(op);
		fflush(stdin);
	}
	return 0; 
    
    printf("\nPressione qualquer tecla para encerrar o programa\n");
    scanf("%c", &l); 
}