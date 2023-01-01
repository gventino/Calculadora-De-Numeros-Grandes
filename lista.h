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