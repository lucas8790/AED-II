#ifndef BST_H
#define BST_H

typedef struct no{
	int valor;
	struct no *esq, *dir;
} no;

typedef no* arvore;

arvore inserir_bst(int valor, arvore raiz);
void pre_order_bst(arvore raiz);
void in_order_bst(arvore raiz);
void pos_order_bst(arvore raiz);
void reverso_bst(arvore raiz);
int primo(int valor);
int qtd_primo_bst(arvore raiz);
void sucessor_bst(int n, arvore raiz);
void caminho_bst(int n, arvore raiz);
arvore remover_bst(arvore raiz, int valor);
int somatorio_bst(arvore raiz);
arvore podar_bst(int n, arvore raiz);
void reajusta_bst(arvore raiz, float percentual);
int existe_bst(arvore raiz, int elemento);
void descendentes_bst(int n, arvore raiz);
int altura_bst(arvore raiz);
arvore maior(arvore raiz);

#endif
