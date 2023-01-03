#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

//construcao de um numero:
typedef struct noNumero 
{
    int valor;
    struct noNumero *prox;
}NoNumero;

typedef struct listaNumero
{
    char sinal;
    NoNumero *inicio;
}Numero;

//construcao do historico
typedef struct noOperacao
{
    //a e b sao entradas, c eh saida
    Numero a;
    Numero b;
    Numero c;
    char operacao;
    struct noOperacao *prox;

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

int inserirInicio(Numero *l, int it)
{
    if(l == NULL) return 2;
    if(listaVazia(l)==0) return inserirFim(l,it);
    NoNumero *noLista = l->inicio;
    NoNumero *novo = (NoNumero *)malloc(sizeof(NoNumero));
    novo->valor=it;
    novo->prox=noLista;
    l->inicio=novo;
    return 0;
}

int inserirFim(Numero *l, int it) 
{
    if (l == NULL) return 2;
    if (listaVazia(l) == 0)
    {
        l->inicio->valor=it;
        l->inicio->prox=NULL;
        return 0;
    }
    
    NoNumero *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;
    
    NoNumero *no = (NoNumero*)malloc(sizeof(NoNumero));
    
    no->valor = it;
    no->prox = noLista->prox;
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
       printf("\n");
       NoNumero *noLista = l->inicio;
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
    if (listaVazia(l) == 0) return 1;
    
    NoNumero *noAuxiliar = NULL;
    NoNumero *noLista = l->inicio;
    
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

int removerInicio(Numero *l)
{
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    NoNumero *noLista = l->inicio;
    l->inicio=l->inicio->prox;
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

int inserirFimHistorico(Historico *l, Numero n1, Numero n2, Numero n3, char op)
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
       NoNumero *noNumA=noLista->a.inicio;
       NoNumero *noNumB=noLista->b.inicio;
       NoNumero *noNumC=noLista->c.inicio;
       while (noLista != NULL) 
       {
          noNumA=noLista->a.inicio;
          noNumB=noLista->b.inicio;
          noNumC=noLista->c.inicio;

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

//funcoes operacoes diversas
//processo q eu pensei pras operacoes:a gnt recebe da main o historico criado la, os numeros(ja criado e formado) e a operacao que o usuario digita, e assim é gerado uma lista do tipo Numero que é o resultado da operacao.
//no fim tudo seria inserido no historico
//B)

int soma(Historico *l, Numero n1, Numero n2, char op)
{
    if(l==NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    Numero n3;//lista do numero resultante da operacao
    //coisinhas da operacao
    inserirFimHistorico(l,n1,n2,n3,op);
    return 0;
}

int subtracao(Historico *l, Numero n1, Numero n2, char op)
{
    if(l==NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    //coisinhas da operacao
    Numero n3;//lista do numero resultante da operacao
    inserirFimHistorico(l,n1,n2,n3,op);
    return 0;
}

int multiplicacao(Historico *l, Numero n1, Numero n2, char op)
{
    if(l==NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    //coisinhas da operacao
    Numero n3;//lista do numero resultante da operacao
    inserirFimHistorico(l,n1,n2,n3,op);
    return 0;
}

int divisao(Historico *l, Numero n1, Numero n2, char op)
{
    if(l==NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    //coisinhas da operacao
    Numero n3;//lista do numero resultante da operacao
    inserirFimHistorico(l,n1,n2,n3,op);
    return 0;
}