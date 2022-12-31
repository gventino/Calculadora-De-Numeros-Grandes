#include <stdio.h>
#include <stdlib.h>

//construcao de um numero:
typedef struct noNumero 
{
    int valor;
    struct noNumero prox;
}NoNumero;

typedef struct listaNumero
{
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
    struct noOperacao prox;

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

int inserirFim(Numero *l, int it) 
{
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return inserirInicio(l,it);
    
    NoNumero *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;
    
    NoNumero *no = (noNumero*)malloc(sizeof(noNumero));
    
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
    
    noNumero *noAuxiliar = NULL;
    noNumero *noLista = l->inicio;
    
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
    if (listaVazia(l) == 0) return inserirInicio(l,it);
    
    noNumero *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;
    
    NoOperacao *no = (noNumero*)malloc(sizeof(noNumero));
    
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
