#ifndef RB_H
#define RB_H

enum cor { VERMELHO, PRETO, DUPLO_PRETO };
typedef int tipo_dado;

typedef struct no_bst{
	tipo_dado valor;
	enum cor cor;
	struct no_bst *esq, *dir, *pai;
} no_bst;

typedef no_bst* arvore;

void rotacaoSimplesDireita(arvore *raiz, arvore pivot);
void rotacaoSimplesEsquerda(arvore *raiz, arvore pivot);
void rotacaoDuplaDireita(arvore *raiz, arvore pivot);
void rotacaoDuplaEsquerda(arvore *raiz, arvore pivot);

enum cor cor(arvore elemento);

int eh_raiz(arvore elemento);
int eh_filho_esquerdo(arvore elemento);
int eh_filho_direito(arvore elemento);
arvore tio(arvore elemento);
arvore irmao(arvore elemento);

int maior(int a, int b);
int maior_elemento(arvore raiz);
int menor_elemento(arvore raiz);
void imprimir_elemento(arvore raiz);

void pre_order_rb(arvore raiz);
void RetiraDuploPreto(arvore *raiz, arvore elemento);
void reajustar(arvore *raiz, arvore elemento);
void ajustar(arvore *raiz, arvore elemento);
void inserir_rb(int valor, arvore *raiz);
void remover_rb(int valor, arvore *raiz);

#endif