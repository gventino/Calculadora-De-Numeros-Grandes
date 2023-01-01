#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

//Numeros:
typedef struct listaNumero Numero;
Numero *criar();
int listaVazia(Numero *l);
int inserirFim(Numero *l, int it);
void limpar(Numero *l);
void mostrar(Numero *l);
int removerFim(Numero *l);

//Historico:
typedef struct listaHistorico Historico;
Historico *criarHistorico();
int historicoVazia(Historico *l);
int inserirFimHistorico(Historico *l, Numero n1, Numero n2, Numero n3, char op);
int removerFimHistorico(Historico *l);
void limparHistorico(Historico *l);
void mostrarHistorico(Historico *l);

//Operações diversas:
int soma(Historico *l, Numero n1, Numero n2, char op);
int subtracao(Historico *l, Numero n1, Numero n2, char op);
int multiplicacao(Historico *l, Numero n1, Numero n2, char op);
int divisao(Historico *l, Numero n1, Numero n2, char op);

#endif