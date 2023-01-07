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
    int y=5;
    if (l != NULL)
    {
        NoNumero *noLista = l->inicio;
        if(l->sinal=='-')
        printf("%c",l->sinal);
        while (noLista != NULL)
        {
            if(noLista->ant!=NULL)
            {
                for(int i=10;i<=100000;i=i*10)
                {
                    if((noLista->valor)<i)
                    {
                        for(int i=0;i<y;i++)
                        {
                            printf("0");
                        }
                        break;
                    }
                    y--;
                }
            }
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
    if (historicoVazia(l) == 0)
    {
        l->inicio->a=n1;
        l->inicio->b=n2;
        l->inicio->c=n3;
        l->inicio->operacao=op;
        l->inicio->prox=NULL;
        return 0;
    }

    NoOperacao *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;

    NoOperacao *no = (NoOperacao*)malloc(sizeof(NoOperacao));

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
    if (historicoVazia(l) == 0) return 1;

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
    while (historicoVazia(l) != 0)
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
       Numero *noNumA=noLista->a;
       Numero *noNumB=noLista->b;
       Numero *noNumC=noLista->c;
       while (noLista != NULL)
       {
          noNumA=noLista->a;
          noNumB=noLista->b;
          noNumC=noLista->c;

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

    int r;
    int userInputA;
    char teste;
    char lixo;
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
    if(a->sinal!='-')
        a->sinal='+';
    printf("\nA=");
    corrige(a);
    mostrar(a);

    printf("\nInsira a operacao:");
    scanf("%c",&operacao);
    fflush(stdin);

    lixo = getc(stdin);
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
    if(b->sinal!='-')
        b->sinal='+';
    printf("\nB=");
    corrige(b);
    mostrar(b);

    switch (operacao)
    {

        case '+':
            r = soma(h,a,b,c);
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

int corrige(Numero *l)
{
    if(l==NULL) return 2;
    if(listaVazia(l)==0) return 1;
    int i,j;
    NoNumero *nonum = l->inicio;
    while(nonum->prox != NULL)
        nonum = nonum->prox;
    
    //printf("\nno antes: %d",nonum->valor);
    NoNumero *aux = nonum->ant;
    while(aux != NULL)//aux é o anterior de nonum, se aux é NULL, é pq o nonum é o primeiro no da lista
    {
        for(i=10;i<=100000;i=i*10)//i é fator de correçao de algarismo, que tb verifica o limite do valor de nonum(se for menor que 10^6, precisa de correçao)
        {
            if(nonum->valor==(nonum->valor)%i)
            {
                j=(aux->valor)%10;//pega o ultimo algarismo do no anterior
                aux->valor=(aux->valor)/10;//corrige questões de classe numerica
                nonum->valor=(nonum->valor) + j*i;//insere o algarismo do no anterior no no atual, multiplicando ele pelo fator de correçao de classe do algarismo
            }
        }
        nonum = nonum->ant;
        aux = aux->ant;
    }

    //while(nonum->prox != NULL)
    //    nonum = nonum->prox;
    
    //printf("\nno depois: %d",nonum->valor);
    //printf("\n\n\n");
    return 0;
}

int tamanho(Numero *l)
{
    if(l==NULL) return -1;
    if(listaVazia(l)==0) return 0;
    int i=1;
    NoNumero *nolista = l->inicio;
    while(nolista->prox!=NULL)
    {
        i++;
        nolista=nolista->prox;
    }
    return i;
}
//funcoes operacoes diversas
//processo q eu pensei pras operacoes:a gnt recebe da main o historico criado la, os numeros(ja criado e formado) e a operacao que o usuario digita, e assim é gerado uma lista do tipo Numero que é o resultado da operacao.
//no fim tudo seria inserido no historico
//B)

int soma(Historico *l, Numero *n1, Numero *n2, Numero *n3)
{
    if(l==NULL) return 2;
    if (listaVazia(n1) == 0) return 1;
    if (listaVazia(n2) == 0) return 1;
    if((n1->sinal=='-')&&(n2->sinal=='+')) return subtracao(l,n2,n1,n3);
    if((n1->sinal=='+')&&(n2->sinal=='-')) return subtracao(l,n1,n2,n3);
    if((n1->sinal=='-')&&(n2->sinal=='-')) n3->sinal='-';
    else n3->sinal='+';
    int y;
    NoNumero *a = n1->inicio;
    NoNumero *b = n2->inicio;

    while(a->prox != NULL)
        a = a->prox;
    
    while(b->prox != NULL)
        b = b->prox;

    while((a!=NULL)&&(b!=NULL))
    {
        y = a->valor + b->valor;
        inserirInicio(n3,y);
        a = a->ant;
        b = b->ant;
    }

    if(a==NULL)
    {
        while(b!=NULL)
        {
            inserirInicio(n3,b->valor);
            b = b->ant;
        }
    }

    if(b==NULL)
    {
        while(a!=NULL)
        {
            inserirInicio(n3,a->valor);
            a = a->ant;
        }
    }

    NoNumero *c = n3->inicio;
    while(c->prox != NULL)
        c = c->prox;

    while(c!=NULL)
    {
        if(c->valor>1000000)
        {
            c->valor = (c->valor)%1000000;
            if(c->ant!=NULL)
                c->ant = c->ant + 1;
            else
                inserirInicio(n3,1);
        }
        c = c->ant;
    }
    printf("\nRESULTADO: ");
    mostrar(n3);
    //inserirFimHistorico(l,n1,n2,n3,'+');
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
