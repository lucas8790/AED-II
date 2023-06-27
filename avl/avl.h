#ifndef AVL_H
#define AVL_H

typedef int tipo_dado;

typedef struct no{
	tipo_dado valor;
	int fb;
	struct no *esq, *dir;
} no;

typedef no* arvore;

arvore maiorNo(arvore a);
arvore menorNo(arvore a);
arvore rotacaoSimplesEsquerda(arvore pivo);
arvore rotacaoSimplesDireita(arvore pivo);
arvore rotacaoDuplaEsquerda(arvore pivo);
arvore rotacaoDuplaDireita(arvore pivo);
arvore rotacao(arvore pivo);
int maior(int a, int b);
arvore inserir_avl(arvore raiz, tipo_dado valor, int *cresceu);
void pre_order_avl(arvore raiz);
arvore remover_avl(tipo_dado n, arvore a, int *diminuiu);

#endif