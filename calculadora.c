#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "headersCalculadora.h"

FILE *erro;
FILE *hist;

//construcao de um numero:----------------------------------------------------------------------------------------
typedef struct no
{
    int valor;
    struct no *prox;
    struct no *ant;
} NoNumero;

typedef struct listaNumero
{
    char sinal;
    NoNumero *inicio;
} Numero;

//construcao do historico:----------------------------------------------------------------------------------------
typedef struct nooperacao
{
    Numero *a;
    Numero *b;
    Numero *c;
    Numero *res;
    char operacao;
    struct nooperacao *prox;
}NoOperacao;

typedef struct filaHistorico
{
    NoOperacao *inicio;
    NoOperacao *fim;
    int qtd;

}Historico;

void criarLogs()
{
    hist = fopen("historico.txt", "w+");
    erro = fopen("log.txt", "w+");
    fclose(erro);
    fclose(hist);
}
// funcoes Numero:----------------------------------------------------------------------------------------
Numero *criar()
{
    Numero *l = (Numero *)malloc(sizeof(Numero));
    if (l == NULL)
    {
        logErro(0);
        return NULL;
    }

    l->inicio = NULL;
    return l;
}

int listaVazia(Numero *l)
{
    if (l == NULL)
    {
        logErro(-2);
        return -2;
    }
    if (l->inicio == NULL)
        return 0;
    return 1;

}

int inserirInicio(Numero *l, int it)
{
    if (l == NULL)
    {
        logErro(-2);
        return -2;
    }
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
    if (l == NULL)
    {
        logErro(-2);
        return -2;
    }
    if (listaVazia(l) == 0)
        return inserirInicio(l, it);
    NoNumero *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;
    NoNumero *no = (NoNumero *)malloc(sizeof(NoNumero));
    no->valor = it;
    no->prox = NULL;
    no->ant = noLista;
    noLista->prox = no;

    return 0;
}

void limpar(Numero *l)
{
    if(l!=NULL)
    {
        l->sinal = ' ';
        while (listaVazia(l) != 0)
            removerInicio(l);
    }
}

void mostrar(Numero *l)
{
    int i, j;
    if (l != NULL)
    {
        NoNumero *noLista = l->inicio;
        if (l->sinal == '-')
            printf("%c", l->sinal);
        while (noLista != NULL)
        {
            printf("%d", noLista->valor);
            noLista = noLista->prox;
        }
    }
}

int removerFim(Numero *l)
{
    if (l == NULL)
    {
        logErro(-2);
        return -2;
    }
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

int removerInicio(Numero *l)
{
    if (l == NULL)
    {
        logErro(-2);
        return -2;
    }
    if (listaVazia(l) == 0)
        return 1;
    NoNumero *noLista = l->inicio;
    l->inicio = noLista->prox;
    if (l->inicio != NULL)
        l->inicio->ant = NULL;

    free(noLista);
    return 0;
}

//funcoes historico:----------------------------------------------------------------------------------------
Historico *criarHistorico()
{
    Historico *h=(Historico*)malloc(sizeof(Historico));
    h->inicio=NULL;
    h->qtd=0;
    h->fim=NULL;
    return h;
}
void limparHistorico(Historico *h)
{
    if(h==NULL)
    {
        logErro(-1);
        return;
    }
    while(historicoVazio(h)!=0)
        removerHistorico(h);
}

int inserirHistorico(Historico *h, Numero *n1, Numero *n2, Numero *n3, Numero *resto,char op)
{
    if(h==NULL)
    {
        logErro(-1);
        return -1;
    }
    NoOperacao *no=(NoOperacao*)malloc(sizeof(NoOperacao));
    no->a=criar();
    copia(n1,no->a);
    no->b=criar();
    copia(n2,no->b);
    no->c=criar();
    copia(n3,no->c);
    if(resto!=NULL)
    {
        no->res=criar();
        copia(resto,no->res);
    }
    no->operacao=op;
    no->prox=NULL;

    if(historicoVazio(h)==0)
        h->inicio=no;

    else
        h->fim->prox=no;

    h->fim=no;
    h->qtd++;
    return 0;
}

int removerHistorico(Historico *h)
{
    if(h==NULL)
    {
        logErro(-1);
        return -1;
    }
    NoOperacao *temp = h->inicio;
    h->inicio=temp->prox;
    free(temp);
    if(h->inicio==NULL)
        h->fim=NULL;

    h->qtd--;
    return 0;
}

int tamanhoHistorico(Historico *h)
{
    if(h==NULL)
    {
        logErro(-1);
        return -1;
    }
    return h->qtd;
}

int historicoVazio(Historico *h)
{
    if(h==NULL)
    {
        logErro(-1);
        return -1;
    }
    if(h->qtd==0)
        return 0;

    else
        return 1;
}

void mostrarHistorico(Historico *h)
{
    if(h!=NULL)
    {
        int q,i,tamA,tamB,tamC;
        printf("HISTORICO:\n");
        NoOperacao *no= h->inicio;

        while(no!=NULL)
        {
            tamA=tamanho(no->a);
            tamB=tamanho(no->b);
            tamC=tamanho(no->c);

            printf("\n\n");
            mostrar(no->a);
            printf("\n");
            printf("%c",no->operacao);

            if(no->b->sinal=='-')
            {
                printf("(");
                mostrar(no->b);
                printf(")");
            }
            else mostrar(no->b);

            printf("\n");
            if(tamA>tamB && tamA>tamC)
                q=tamA;
            if(tamB>tamA && tamB>tamC)
                q=tamB;
            if(tamC>=tamA && tamC>=tamB)
                q=tamC;

            for(i=0;i<q+1;i++)
                printf("-");

            printf("\n");
            if(no->operacao!='/')
                mostrar(no->c);
            else
            {
                if((no->b->inicio)->valor!=0)
                {
                    mostrar(no->c);
                    printf("\nRESTO: ");
                    mostrar(no->res);
                }
                else
                {
                    printf("NAO EXISTE");
                    printf("\nRESTO: ");
                    printf("NAO EXISTE");
                }
            }
            printf("\n\n");
            no=no->prox;
        }
            printf("\nFIM DO HISTORICO.");
    }
}

//funcoes calculadora:----------------------------------------------------------------------------------------
int opcaoA(Numero *a, Numero *b, Numero *c, Numero *res, Historico *h)
{
    if (a == NULL || b == NULL || c == NULL)
    {
        logErro(-2);
        return 2;
    }
    //limpar(res);
    int r;
    int userInputA;
    char teste;
    char lixo;
    char operacao;
    printf("\n|->Insira o Primeiro Numero: ");
    teste = getc(stdin);
    while (teste != '\n')
    {
        if (teste == '-')
            a->sinal = '-';
        else if(isdigit(teste)>0)
        {
            ungetc(teste, stdin);
            scanf("%1d", &userInputA);
            inserirFim(a, userInputA);
        }
        userInputA = 0;
        teste = getc(stdin);
    }
    fflush(stdin);
    if (a->sinal != '-')
        a->sinal = '+';
    printf("\n|->A=");
    corrige(a);
    mostrar(a);

    printf("\n\n|->soma : +; \n|->subtracao : -; \n|->multiplicacao : *; \n|->divisao : /;\n|->mostrar o maior dentre os numeros escritos : m;");
    printf("\n\n|->Insira a operacao:");
    scanf("%c", &operacao);
    fflush(stdin);
    lixo = getc(stdin);

    printf("\n|->Insira o Segundo Numero: ");
    teste = getc(stdin);
    while (teste != '\n')
    {
        if (teste == '-')
            b->sinal = '-';
        else if(isdigit(teste)>0)
        {
            ungetc(teste, stdin);
            scanf("%1d", &userInputA);
            inserirFim(b, userInputA);
        }
        userInputA = 0;
        teste = getc(stdin);
    }
    fflush(stdin);
    if (b->sinal != '-')
        b->sinal = '+';
    printf("\n|->B=");
    corrige(b);
    mostrar(b);

    switch (operacao)
    {

        case '+':
        {
            c = soma(a, b);
            printf("\n\nRESULTADO:");
            mostrar(c);
            break;
        }
        case '-':
        {
            c = subtracao(a, b);
            printf("\n\nRESULTADO:");
            mostrar(c);
            break;
        }
        case '*':
        {
            c = multiplicacao(a, b);
            printf("\n\nRESULTADO:");
            mostrar(c);
            break;
        }
        case '/':
        {
            c = divisao(a, b, res);
            if(c!=NULL)
            {
                printf("\n\nRESULTADO:");
                mostrar(c);
                printf("\n\nRESTO:");
                mostrar(res);
            }

            break;
        }
        case 'm':
        {
            int maior=diferenca(a,b);
            if(a->sinal=='+' && b->sinal=='-')
                        maior = -1;
            if(a->sinal=='-' && b->sinal=='+')
                        maior = -2;

            if(a->sinal=='-' && b->sinal=='-')
            {
                int l;
                if(maior==-1)
                    l = -2;
                if(maior==-2)
                    l = -1;
                maior=l;
            }
             switch(maior)
             {
                case 0://seccao == n2
                {
                    printf("\n\nA:");
                    copia(a,c);
                    mostrar(a);
                    printf("\nEh igual a: ");
                    mostrar (b);
                    break;
                }
                case -1:
                {
                    printf("\n\nA:");
                    copia(a,c);
                    mostrar(a);
                    printf("\nEh maior que: ");
                    mostrar (b);
                    break;
                }
                case -2:
                {
                    printf("\n\nB:");
                    copia(b,c);
                    mostrar(b);
                    printf("\nEh maior que: ");
                    mostrar (a);
                    break;
                }
                default:
                {
                    printf("\n\noperacao invalida!ERRO!");
                    return -1;
                    break;
                }
             }
            break;
        }
        default:
            printf("\n\noperacao invalida!ERRO!");
            return -1;
            break;
    }
    if(operacao=='/')
    {
        inserirHistorico(h,a,b,c,res,operacao);
        mostrarOperacao(a,b,c,res,operacao);
    }
    else
    {
        inserirHistorico(h,a,b,c,NULL,operacao);
        mostrarOperacao(a,b,c,NULL,operacao);
    }

    return 0;
}

int corrige(Numero *l)
{
    if (l == NULL)
    {
        logErro(-2);
        return 2;
    }
    if (listaVazia(l) == 0)
        return 1;
    int i=2;
    if(tamanho(l)>1)
    {
        while ((l->inicio->valor == 0)&&(i>1))
        {
            removerInicio(l);
            i = tamanho(l);
        }
    }

    return 0;
}

int tamanho(Numero *l)
{

    if (l == NULL)
    {
        logErro(-2);
        return -1;
    }

    if (listaVazia(l) == 0)
        return 0;

    int i = 1;

    NoNumero *nolista = l->inicio;

    while (nolista->prox != NULL)
    {
        i++;
        nolista = nolista->prox;
    }

    return i;
}

int copia(Numero *l, Numero *r)
{
    if (l == NULL || r == NULL)
    {
        logErro(-2);
        return -1;
    }
    limpar(r);
    NoNumero *no = l->inicio;
    while (no != NULL)
    {
        inserirFim(r, no->valor);
        no = no->prox;
    }
    r->sinal = l->sinal;

    return 0;
}

//operacoes da calculadora:----------------------------------------------------------------------------------------
Numero *soma(Numero *n1, Numero *n2)
{
    if (n1 == NULL || n2 == NULL)
    {
        logErro(-2);
        logErro(0);
        return NULL;
    }
    if (listaVazia(n1) == 0)
    {
        logErro(0);
        return NULL;
    }

    if (listaVazia(n2) == 0)
    {
        logErro(0);
        return NULL;
    }

    Numero *n3 = criar();

    if (tamanho(n1) == 1)
    {
        if (n1->inicio->valor == 0)
        {
            copia(n2, n3);
            // inserirFimHistorico(l,n1,n2,n3,'+');
            return n3;
        }
    }

    if (tamanho(n2) == 1)
    {
        if (n2->inicio->valor == 0)
        {
            copia(n1, n3);
            // inserirFimHistorico(l,n1,n2,n3,'+');
            return n3;
        }
    }

    if ((n1->sinal == '-') && (n2->sinal == '+'))
    {
        n1->sinal = '+';
        n3 = subtracao( n1, n2);
        n3->sinal = '-';
        n1->sinal = '-';
        return n3;
    }

    if ((n1->sinal == '+') && (n2->sinal == '-'))
    {
        n2->sinal = '+';
        n3 = subtracao( n1, n2);
        n2->sinal = '-';
        return n3;
    }

    if ((n1->sinal == '-') && (n2->sinal == '-'))
        n3->sinal = '-';
    else
        n3->sinal = '+';
    int y;

    NoNumero *a = n1->inicio;
    NoNumero *b = n2->inicio;

    while (a->prox != NULL)
        a = a->prox;

    while (b->prox != NULL)
        b = b->prox;

    while ((a != NULL) && (b != NULL))
    {
        y = a->valor + b->valor;
        inserirInicio(n3, y);
        a = a->ant;
        b = b->ant;
    }

    if (a == NULL)
    {
        while (b != NULL)
        {
            inserirInicio(n3, b->valor);
            b = b->ant;
        }
    }

    if (b == NULL)
    {
        while (a != NULL)
        {
            inserirInicio(n3, a->valor);
            a = a->ant;
        }
    }

    NoNumero *c = n3->inicio;
    while (c->prox != NULL)
        c = c->prox;

    while (c != NULL)
    {
        if (c->valor >= 10)
        {
            c->valor = (c->valor) % 10;
            if (c->ant != NULL)
                (c->ant)->valor = (c->ant)->valor + 1;
            else
                inserirInicio(n3, 1);
        }
        c = c->ant;
    }

    return n3;
}

Numero *subtracao( Numero *n1, Numero *n2)
{
    if (n1 == NULL || n2 == NULL)
    {
        logErro(-2);
        logErro(0);
        return NULL;
    }
    if (listaVazia(n1) == 0)
    {
        logErro(0);
        return NULL;
    }

    if (listaVazia(n2) == 0)
    {
        logErro(0);
        return NULL;
    }

    Numero *n3 = criar();
    int j = 0;
    if((n1->inicio->valor==0)&&(n2->inicio->valor==0))
    {
        inserirFim(n3,0);
        n3->sinal = '+';
        return n3;
    }
    if ((n1->sinal == '-') && (n2->sinal == '+'))
    {
        n2->sinal = '-';
        n3 = soma(n1, n2);
        n2->sinal = '+';
        return n3;
    }
    if ((n1->sinal == '+') && (n2->sinal == '-'))
    {
        n2->sinal = '+';
        n3 = soma(n1, n2);
        n2->sinal = '-';
        return n3;
    }

    if ((n1->sinal == '+') && (n2->sinal == '+'))
    {
        int n = tamanho(n1);
        int m = tamanho(n2);
        if (n > m)
        {
            n3->sinal = '+';
        }
        else if (n < m)
        {
            n3 = subtracao(n2, n1);
            n3->sinal = '-';
            return n3;
        }
        else
        {
            NoNumero *no1 = n1->inicio;
            NoNumero *no2 = n2->inicio;

            while (no1 != NULL)
            {
                if (no1->valor > no2->valor)
                {
                    n3->sinal = '+';
                    break;
                }
                else if (no1->valor < no2->valor)
                {
                    n3 = subtracao(n2, n1);
                    n3->sinal = '-';
                    return n3;
                }
                else
                {
                    n3->sinal = '+';
                    j++;
                }
                no1 = no1->prox;
                no2 = no2->prox;
            }
            if ((j == m) && (j == n))
            {
                inserirInicio(n3, 0);
                return n3;
            }
        }
    }

    if ((n1->sinal == '-') && (n2->sinal == '-'))
    {
        int n = tamanho(n1);
        int m = tamanho(n2);
        if (n > m)
        {
            n3->sinal ='-';
        }
        else if (n < m)
        {
            n3 = subtracao(n2, n1);
            n3->sinal = '+';
            return n3;
        }
        else
        {
            NoNumero *no1 = n1->inicio;
            NoNumero *no2 = n2->inicio;

            while (no1 != NULL)
            {
                if (no1->valor > no2->valor)
                {
                    n3->sinal = '-';
                    break;
                }
                else if (no1->valor < no2->valor)
                {
                    n3 = subtracao( n2, n1);
                    n3->sinal = '+';
                    return n3;
                }
                else
                {
                    n3->sinal = '+';
                    j++;
                }
                no1 = no1->prox;
                no2 = no2->prox;
            }
            if ((j == m) && (j == n))
            {
                inserirInicio(n3, 0);
                return n3;
            }
        }
    }
    char sin;
    if (tamanho(n1) == 1)
    {
        if (n1->inicio->valor == 0)
        {
            sin = n3->sinal;
            copia(n2, n3);
            n3->sinal = sin;
            return n3;
        }
    }

    if (tamanho(n2) == 1)
    {
        if (n2->inicio->valor == 0)
        {
            copia(n1, n3);
            return n3;
        }
    }

    Numero *naux1 = criar();
    copia(n1,naux1);

    NoNumero *no1 = n1->inicio;
    NoNumero *no2 = n2->inicio;

    while (no1->prox != NULL)
        no1 = no1->prox;

    while (no2->prox != NULL)
        no2 = no2->prox;

    NoNumero *aux1 = no1->ant;
    NoNumero *cteant = no1->ant;

    int i = 1, y;
    while (no1 != NULL && no2 != NULL)
    {
        if ((no2->valor) > (no1->valor))
        {
            while ((aux1 != NULL) && (aux1->valor == 0))
            {
                i++;
                aux1 = aux1->ant;
            }
            for (int y = 0; y < i; y++)
            {
                aux1->valor = aux1->valor - 1;
                (aux1->prox)->valor = (aux1->prox)->valor + 10;
                aux1 = aux1->prox;
            }
        }
        aux1 = cteant;
        y = no1->valor - no2->valor;
        inserirInicio(n3, y);
        no1 = no1->ant;
        if (no1 != NULL)
        {
            aux1 = aux1->ant;
            cteant = aux1;
        }
        no2 = no2->ant;
    }

    if (no1 == NULL)
    {
        while (no2 != NULL)
        {
            inserirInicio(n3, no2->valor);
            no2 = no2->ant;
        }
    }

    if (no2 == NULL)
    {
        while (no1 != NULL)
        {
            inserirInicio(n3, no1->valor);
            no1 = no1->ant;
        }
    }

    while ((n3->inicio)->valor == 0)
    {
        if (n3->inicio->prox == NULL)
            break;
        removerInicio(n3);
    }
    copia(naux1,n1);
    limpar(naux1);
    return n3;
}

Numero *multiplicacao( Numero *n1, Numero *n2)
{
    Numero *n3 = criar();
    if (n1 == NULL || n2 == NULL)
    {
        logErro(-2);
        logErro(0);
        return NULL;
    }
    if (listaVazia(n1) == 0)
    {
        logErro(0);
        return NULL;
    }

    if (listaVazia(n2) == 0)
    {
        logErro(0);
        return NULL;
    }

    int y, z, i = 0, j = 0;
    NoNumero *a = n1->inicio;
    NoNumero *b = n2->inicio;
    NoNumero *c = (NoNumero *)malloc(sizeof(NoNumero));
    NoNumero *a1 = (NoNumero *)malloc(sizeof(NoNumero));
    Numero *res1 = criar();
    Numero *res0 = criar();
    Numero *help1 = criar();
    Numero *help = criar();
    Numero *aux = criar();

    inserirInicio(res0, 0);
    inserirInicio(help, 0);

    if (tamanho(n1) == 1)
    {
        if (n1->inicio->valor == 0)
        {
            inserirFim(n3,0);
            return n3;
        }
        else if (n1->inicio->valor == 1)
        {
            copia(n2,n3);
            if ((n1->sinal == '+') && (n2->sinal == '+'))
                n3->sinal = '+';
            if ((n1->sinal == '-') && (n2->sinal == '+'))
                n3->sinal = '-';
            if ((n1->sinal == '+') && (n2->sinal == '-'))
                n3->sinal = '-';
            if ((n1->sinal == '-') && (n2->sinal == '-'))
                n3->sinal = '+';

            return n3;
        }
    }

    if (tamanho(n2) == 1)
    {
        if (n2->inicio->valor == 0)
        {
            inserirFim(n3,0);
            return n3;
        }
        else if (n2->inicio->valor == 1)
        {
            copia(n1,n3);
            if ((n1->sinal == '+') && (n2->sinal == '+'))
                n3->sinal = '+';
            if ((n1->sinal == '-') && (n2->sinal == '+'))
                n3->sinal = '-';
            if ((n1->sinal == '+') && (n2->sinal == '-'))
                n3->sinal = '-';
            if ((n1->sinal == '-') && (n2->sinal == '-'))
                n3->sinal = '+';

            return n3;
        }
    }

    while (b->prox != NULL)
        b = b->prox;

    while (a->prox != NULL)
        a = a->prox;
    a1 = a;

    while (b != NULL)
    {
        a = a1;
        while (a != NULL)
        {
            // gerar uma linha da multiplicação
            y = (b->valor) * (a->valor);
            inserirInicio(aux, y);
            if ((j > 0) && (aux->inicio->valor != 0))
            {
                for (int y = 0; y < j; y++)
                {
                    inserirFim(aux, 0);
                }
            }
            c = aux->inicio; // nao precisa de loop pq so o inicio de aux tem valor relevante

            if (c->valor >= 10)
            {
                z = (c->valor) / 10;
                c->valor = (c->valor) % 10;
                inserirInicio(aux, z);
            }
            res1 = soma(aux, help);
            copia(res1, help);
            limpar(res1);
            limpar(aux);
            j++;
            a = a->ant;
        }
        // gerar a soma das linhas da multiplicação
        j = 0;
        if ((i > 0) && (help->inicio->valor != 0))
        {
            for (int y = 0; y < i; y++)
                inserirFim(help, 0);
        }
        help1 = soma(help, res0);
        copia(help1, res0);
        limpar(help1);
        limpar(help);
        inserirInicio(help, 0);
        i++;
        b = b->ant;
    }
    copia(res0, n3);
    limpar(res0);
    if ((n1->sinal == '+') && (n2->sinal == '+'))
        n3->sinal = '+';
    if ((n1->sinal == '-') && (n2->sinal == '+'))
        n3->sinal = '-';
    if ((n1->sinal == '+') && (n2->sinal == '-'))
        n3->sinal = '-';
    if ((n1->sinal == '-') && (n2->sinal == '-'))
        n3->sinal = '+';

    return n3;
}

Numero *divisao( Numero *n1, Numero *n2, Numero *resto)
{
    if (n1 == NULL || n2 == NULL)
    {
        logErro(-2);
        logErro(0);
        return NULL;
    }
    Numero *n3 = criar();
    if(n2->inicio->valor == 0)
    {
        printf("\nNAO DIVIDA POR ZERO.");
        logErro(0);
        return NULL;
    }
    if(n1->inicio->valor == 0)
    {
        inserirFim(n3,0);
        inserirFim(resto,0);
        return n3;
    }
    int i;
    NoNumero *a = n1->inicio;
    Numero *seccao = criar();
    Numero *aux = criar();
    Numero *aux1 = criar();
    Numero *D = criar();
    inserirFim(D,1);
    int y = 1,j=0;
    i = diferenca(n1,n2);
    if(i==-1)
    {
        int n = tamanho(n2), m = tamanho(n1);
        if(m==n) 
        {
            copia(n1,seccao);//quando o tamanho dos dois é igual, a seccao se torna literalmente o numero A
            a = NULL;
        }
        else
        {
            seccao = cortaNumero(n1,n);
            for(int i=0; i<n; i++)
            {
                a = a->prox;
            }
        }
        while(a!=NULL)
        {
            i = diferenca(seccao,n2);
            switch(i)
            {
                case 0://seccao == n2
                {
                    inserirFim(n3,1);
                    limpar(seccao);
                    inserirFim(seccao,a->valor);
                    corrige(seccao);
                    break;
                }
                case -2://seccao < n2
                {
                    inserirFim(n3,0);
                    inserirFim(seccao,a->valor);
                    corrige(seccao);
                    break;
                }
                case -1://seccao > n2
                {
                    while(i!=-2)
                    {
                        limpar(aux);
                        aux1 = multiplicacao(n2,D);
                        aux = subtracao(seccao,aux1);
                        i = diferenca(aux,n2);
                        limpar(aux1);
                        y++;
                        limpar(D);
                        inserirFim(D,y);
                    }
                    limpar(seccao);
                    copia(aux,seccao);
                    limpar(aux);
                    inserirFim(seccao,a->valor);
                    corrige(seccao);
                    inserirFim(n3,y-1);
                    y=1;
                    limpar(D);
                    inserirFim(D,y);
                    break;
                }
            }
            a = a->prox;
        }
        i = diferenca(seccao,n2);
        switch(i)
        {
            case 0://seccao == n2
            {
                inserirFim(n3,1);
                limpar(seccao);
                inserirFim(seccao,0);
                corrige(seccao);
                break;
            }
            case -2://seccao < n2
            {
                inserirFim(n3,0);
                break;
            }
            case -1://seccao > n2
            {
                while(i!=-2)
                {
                    limpar(aux);
                    aux1 = multiplicacao(n2,D);
                    aux = subtracao(seccao,aux1);
                    i = diferenca(aux,n2);
                    limpar(aux1);
                    y++;
                    limpar(D);
                    inserirFim(D,y);
                }
                limpar(seccao);
                copia(aux,seccao);
                limpar(aux);
                corrige(seccao);
                inserirFim(n3,y-1);
                y=1;
                limpar(D);
                inserirFim(D,y);
                break;
            }
        }
        i=-1;
    }
    if(i==-2)
    {
        inserirFim(n3,0);
        n3->sinal = '+';
        copia(n1,resto);
        return n3;
    }
    if(i==0)
    {
        inserirFim(n3,1);
        if ((n1->sinal == '+') && (n2->sinal == '+'))
            n3->sinal = '+';
        if ((n1->sinal == '-') && (n2->sinal == '+'))
            n3->sinal = '-';
        if ((n1->sinal == '+') && (n2->sinal == '-'))
            n3->sinal = '-';
        if ((n1->sinal == '-') && (n2->sinal == '-'))
            n3->sinal = '+';
        inserirFim(resto,0);
        return n3;
    }
    if(i==-3)
    {
        logErro(0);
        return NULL;
    }
    //jogo de sinal:
    corrige(n3);
    copia(seccao,resto);
    limpar(seccao);
    if ((n1->sinal == '+') && (n2->sinal == '+'))
        n3->sinal = '+';
    if ((n1->sinal == '-') && (n2->sinal == '+'))
        n3->sinal = '-';
    if ((n1->sinal == '+') && (n2->sinal == '-'))
        n3->sinal = '-';
    if ((n1->sinal == '-') && (n2->sinal == '-'))
        n3->sinal = '+';
    return n3;
}

int diferenca(Numero *a, Numero *b)
{
    if (listaVazia(a) == 0)
        return 1;
    if (listaVazia(b) == 0)
        return 1;
    Numero *aux = criar();
    Numero *aux1 = criar();
    copia(a,aux);
    copia(b,aux1);
    NoNumero *no1 = a->inicio;
    NoNumero *no2 = b->inicio;
    int j = 0;
    int n = tamanho(a),m = tamanho(b);
    if(n>m)
        return -1;
    if(m>n)
        return -2;
    while (no1 != NULL)
    {
        if (no1->valor > no2->valor)
        {
            copia(aux,a);
            copia(aux1,b);
            return -1;
        }
        else if (no1->valor < no2->valor)
        {
            copia(aux,a);
            copia(aux1,b);
            return -2;
        }
        else
        {
            j++;
        }
        if((j==tamanho(a))&&(j==tamanho(b)))
        {
            copia(aux,a);
            copia(aux1,b);
            return 0;
        }
        no1 = no1->prox;
        no2 = no2->prox;
    }
    return -3;
    //0 = iguais; -1 = a maior; -2 = b maior; -3 = erro.
}

//printa historico no historico.txt:
int mostrarOperacao(Numero *a, Numero *b, Numero *c, Numero *res, char op)
{
    int tamA=tamanho(a);
    int tamB=tamanho(b);
    int tamC=tamanho(c);
    int i;
    int q;

    hist=fopen("historico.txt","a");
    if(a==NULL || b==NULL || c==NULL)
    {
        logErro(-2);
        return -1;
    }

    //mostrando A
    NoNumero *no = a->inicio;
    if(a->sinal=='-')
        fprintf(hist,"%c",a->sinal);
    while(no!=NULL)
    {
        fprintf(hist,"%d",no->valor);
        no=no->prox;
    }

    //mostrando operacao
    fprintf(hist,"\n%c", op);

    //mostrando b
    no = b->inicio;
    if(b->sinal=='-')
    {
        fprintf(hist,"(");
        fprintf(hist,"%c",b->sinal);
        while(no!=NULL)
        {
            fprintf(hist,"%d",no->valor);
            no=no->prox;
        }
        fprintf(hist,")");
    }
    else
    {
        while(no!=NULL)
        {
            fprintf(hist,"%d",no->valor);
            no=no->prox;
        }
    }

    fprintf(hist,"\n");
    if(tamA>=tamB && tamA>tamC)
        q=tamA;
    if(tamB>tamA && tamB>tamC)
        q=tamB;
    if(tamC>=tamA && tamC>=tamB)
        q=tamC;

    for(i=0;i<q+1;i++)
        fprintf(hist,"-");


    fprintf(hist,"\n");
    no = c->inicio;
    if(op!='/')
    {
        while(no!=NULL)
        {
            fprintf(hist,"%d",no->valor);
            no=no->prox;
        }
    }

    else
    {
        if((b->inicio)->valor!=0)
        {
            while(no!=NULL)
            {
                fprintf(hist,"%d",no->valor);
                no=no->prox;
            }

            fprintf(hist,"\nRESTO: ");
            no=res->inicio;
            while(no!=NULL)
            {
                fprintf(hist,"%d",no->valor);
                no=no->prox;
            }
        }
        else
        {
            fprintf(hist,"NAO EXISTE");
            fprintf(hist,"\nRESTO: ");
            fprintf(hist,"NAO EXISTE");
        }
    }
    fprintf(hist,"\n\n\n");
    fclose(hist);
    return 0;
}

/*
    cortaNumero:
    supondo cortar 1234567, tirando os 3 primeiros elementos.
    essa função retornaria o Numero 123, e um ponteiro prx que apontaria pro nó do elemento de valor 4
*/
Numero *cortaNumero(Numero *a, int tam)
{
    Numero *ret = criar();
    NoNumero *A = a->inicio;
    for(int i=0; i<tam; i++)
    {
        inserirFim(ret,A->valor);
        A = A->prox;
    }
    return ret;
}

//printa no log de erro .txt os erros.
void logErro(int x)
{
    erro=fopen("log.txt","a+");
    if(x==-2)
        fprintf(erro,"\nNumero Nulo;");
    if(x==-1)
        fprintf(erro,"\nHistorico Nulo;");
    if(x==0)
        fprintf(erro,"Retornando Nulo;");
    fclose(erro);
}