#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

//construcao de um numero:
typedef struct no
{
    int valor;
    struct no *prox;
    struct no *ant;
}NoNumero;

typedef struct listaNumero
{
    char sinal;
    NoNumero *inicio;
}Numero;

//construcao do historico
typedef struct no_operacao
{
    //a e b sao entradas, c eh saida
    Numero *a;
    Numero *b;
    Numero *c;
    char operacao;
    struct no_operacao *prox;

}NoOperacao;

typedef struct listaHistorico
{
    NoOperacao *inicio;
}Historico;

//funcoes Numero:
Numero *criar()
{
    Numero *l = (Numero*)malloc(sizeof(Numero));
    l->inicio = NULL;
    return l;
}

int listaVazia(Numero *l)
{
    if (l == NULL) return 2;
    if (l->inicio == NULL) return 0;
    return 1;
}

int inserirInicio(Numero *l, int it) {
    if (l == NULL) return 2;
    NoNumero *no = (NoNumero *)malloc(sizeof(NoNumero));
    no->valor = it;
    no->prox = l->inicio;
    no->ant = NULL;
    if (l->inicio != NULL)
        l->inicio->ant = no;
    l->inicio = no;
    return 0;
}

int inserirFim(Numero *l, int it)
{
    if (l == NULL) return 2;
    if (listaVazia(l) == 0)
        return inserirInicio(l,it);
    NoNumero *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;
    NoNumero *no = (NoNumero*)malloc(sizeof(NoNumero));
    no->valor = it;
    no->prox = NULL;
    no->ant = noLista;
    noLista->prox = no;
    return 0;
}

void limpar(Numero *l)
{
    while (listaVazia(l) != 0)
        removerFim(l);
}

void mostrar(Numero *l)
{
    if (l != NULL)
    {
       NoNumero *noLista = l->inicio;
       printf("%c",l->sinal);
       while (noLista != NULL)
       {
          printf("%d",noLista->valor);
          noLista = noLista->prox;
       }
       printf("\n");
    }
}

int removerFim(Numero *l)
{
    if (l == NULL) return 2;
    if (listaVazia(l) == 0)
        return 1;
    NoNumero *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;
    if (noLista->ant == NULL)
        l->inicio = NULL;
    else
        noLista->ant->prox = NULL;
    free(noLista);
    return 0;
}

int removerInicio(Numero *l) {
    if (l == NULL) return 2;
    if (listaVazia(l) == 0)
        return 1;
    NoNumero *noLista = l->inicio;
    l->inicio = noLista->prox;
    if (l->inicio != NULL)
        l->inicio->ant = NULL;
    free(noLista);
    return 0;
}

//funcoes historico:
Historico *criarHistorico()
{
    Historico *l = (Historico*)malloc(sizeof(Historico));
    l->inicio = NULL;
    return l;
}

int historicoVazia(Historico *l)
{
    if (l == NULL) return 2;
    if (l->inicio == NULL) return 0;
    return 1;
}

int inserirFimHistorico(Historico *l, Numero *n1, Numero *n2, Numero *n3, char op)
{
    if (l == NULL) return 2;
    if (listaVazia(l) == 0)
    {
        l->inicio->a=n1;
        l->inicio->b=n2;
        l->inicio->c=n3;
        l->inicio->operacao=op;
        l->inicio->prox=NULL;
        return 0;
    }

    NoNumero *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;

    NoOperacao *no = (NoNumero*)malloc(sizeof(NoNumero));

    no->a = n1;
    no->b = n2;
    no->c = n3;
    no->operacao = op;

    no->prox = noLista->prox;
    noLista->prox = no;

    return 0;
}

int removerFimHistorico(Historico *l)
{
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;

    NoOperacao *noAuxiliar = NULL;
    NoOperacao *noLista = l->inicio;

    while (noLista->prox != NULL)
    {
        noAuxiliar = noLista;
        noLista = noLista->prox;
    }

    if (noAuxiliar == NULL) l->inicio = NULL;
    else noAuxiliar->prox = NULL;

    free(noLista);
    return 0;
}

void limparHistorico(Historico *l)
{
    while (listaVazia(l) != 0)
        removerFimHistorico(l);
}

void mostrarHistorico(Historico *l)
{
    //nao testei mas acho que faz sentido
    //mo trampo namoral
    if (l != NULL)
    {
       printf("Historico:\n");
       NoOperacao *noLista = l->inicio;
       NoNumero *noNumA=noLista->a->inicio;
       NoNumero *noNumB=noLista->b->inicio;
       NoNumero *noNumC=noLista->c->inicio;
       while (noLista != NULL)
       {
          noNumA=noLista->a->inicio;
          noNumB=noLista->b->inicio;
          noNumC=noLista->c->inicio;

          mostrar(noNumA);
          printf(" %c ",noLista->operacao);
          mostrar(noNumB);
          printf(" = ");
          mostrar(noNumC);
          printf("\n");

          noLista = noLista->prox;
       }
       printf("\n");
    }
}

//se quiser me chama no zap que eu explico, ta funcionando perfeitamente, so eh meio foda de entender.
int opcaoA(Numero *a, Numero *b, Numero *c, Historico *h)
{
    if(a==NULL || b==NULL || c==NULL || h==NULL)
        return -1;

    int userInputA;
    char teste;
    char operacao;

    printf("\nInsira o Primeiro Numero: ");
    teste=getc(stdin);
    while(teste!='\n')
    {
        if(teste=='-')
            a->sinal='-';

        else
            ungetc(teste,stdin);

        scanf("%6d",&userInputA);
        inserirFim(a,userInputA);
        userInputA=0;
        teste=getc(stdin);
    }
    fflush(stdin);
    printf("\nA=");
    mostrar(a);

    printf("\nInsira a operacao:");
    scanf("%c",&operacao);
    fflush(stdin);

    printf("\nInsira o Segundo Numero: ");
    teste=getc(stdin);
    while(teste!='\n')
    {
        if(teste=='-')
            b->sinal='-';

        else
            ungetc(teste,stdin);

        scanf("%6d",&userInputA);
        inserirFim(b,userInputA);
        userInputA=0;
        teste=getc(stdin);
    }
    fflush(stdin);
    printf("\nB=");
    mostrar(b);


    switch (operacao)
    {

        case '+':
            printf("\nsoma feita!");
            //return soma(h, a, b, c);
            break;

        case '-':
            printf("\nsubtracao feita!");
            //return subtracao(h, a, b, c);
            break;

        case '*':
            printf("\nmultiplicacao feita!");
            //return multiplicacao(h, a, b, c);
            break;

        case '/':
            printf("\ndivisao feita!");
            //return divisao(h, a, b, c);
            break;

        default:
            printf("\noperacao invalida!ERRO!");
            return -1;
            break;
    }
}
//funcoes operacoes diversas
//processo q eu pensei pras operacoes:a gnt recebe da main o historico criado la, os numeros(ja criado e formado) e a operacao que o usuario digita, e assim é gerado uma lista do tipo Numero que é o resultado da operacao.
//no fim tudo seria inserido no historico
//B)

int soma(Historico *l, Numero *n1, Numero *n2, Numero *n3)
{
    if(l==NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    //coisinhas da operacao
    inserirFimHistorico(l,n1,n2,n3,'+');
    return 0;
}

int subtracao(Historico *l, Numero *n1, Numero *n2, Numero *n3)
{
    if(l==NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    //coisinhas da operacao
    inserirFimHistorico(l,n1,n2,n3,'-');
    return 0;
}

int multiplicacao(Historico *l, Numero *n1, Numero *n2, Numero *n3)
{
    if(l==NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    //coisinhas da operacao
    inserirFimHistorico(l,n1,n2,n3,'*');
    return 0;
}

int divisao(Historico *l, Numero *n1, Numero *n2, Numero *n3)
{
    if(l==NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    //coisinhas da operacao
    inserirFimHistorico(l,n1,n2,n3,'/');
    return 0;
}
