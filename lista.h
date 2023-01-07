#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

//Numeros:
typedef struct listaNumero Numero;
Numero *criar();
int listaVazia(Numero *l);
int inserirInicio(Numero *l, int it);//necessário para adição e multiplicação
int inserirFim(Numero *l, int it);
void limpar(Numero *l);
void mostrar(Numero *l);
int removerFim(Numero *l);
int removerInicio(Numero *l);//necessário para subtração e divisão
int corrige(Numero *l);//corrigir os erros de ordem q o scanf gerou nos numeros
int tamanho(Numero *l);

//Historico:
typedef struct listaHistorico Historico;
Historico *criarHistorico();
int historicoVazia(Historico *l);
int inserirFimHistorico(Historico *l, Numero *n1, Numero *n2, Numero *n3, char op);
int removerFimHistorico(Historico *l);
void limparHistorico(Historico *l);
void mostrarHistorico(Historico *l);

//opcoes:
int opcaoA(Numero *a, Numero *b, Numero *c, Historico *h);

//Operações diversas:
int soma(Historico *l, Numero *n1, Numero *n2, Numero *n3);
int subtracao(Historico *l, Numero *n1, Numero *n2, Numero *n3);
int multiplicacao(Historico *l, Numero *n1, Numero *n2, Numero *n3);
int divisao(Historico *l, Numero *n1, Numero *n2, Numero *n3);

#endif
