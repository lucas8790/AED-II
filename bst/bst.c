#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

arvore inserir_bst(int valor, arvore raiz){
	//caso base = inserir em uma arvore vazia
	if(raiz == NULL){
		arvore novo = (arvore)malloc(sizeof(struct no));
		novo->esq = NULL;
		novo->dir = NULL;
		novo->valor = valor;
		//o retorno é a raiz da sub-árvore que foi uniciada
		return novo;
	}
	//caso recursivo
	else{
		if(valor > raiz->valor){
			raiz->dir = inserir_bst(valor, raiz->dir);
		}else{
			raiz->esq = inserir_bst(valor, raiz->esq);
		}
		return raiz;
	}
}

void pre_order_bst(arvore raiz){
	if(raiz != NULL){
		//processar a raiz relativa
		printf("[%d]", raiz->valor);
		
		//encadeamentos recursivos esq, dir
		pre_order_bst(raiz->esq);
		pre_order_bst(raiz->dir);
	} //else caso base implicito não faz nada
}

void in_order_bst(arvore raiz){
	if(raiz != NULL){
		in_order_bst(raiz->esq);
		
		printf("[%d]", raiz->valor);
		in_order_bst(raiz->dir);
	}
}

void pos_order_bst(arvore raiz){
	if(raiz != NULL){
		pos_order_bst(raiz->esq);
		
		pos_order_bst(raiz->dir);
		printf("[%d]", raiz->valor);
	}
}

void reverso_bst(arvore raiz){
	if(raiz != NULL){
		reverso_bst(raiz->dir);
		printf("[%d]", raiz->valor);
		reverso_bst(raiz->esq);
	}
}

//Função aux para verificar se é primo:
int primo(int valor){
	int divisores = 0;
	
	for(int i = 2; i <= valor; i++){
		if(valor % i == 0){
			divisores++;
		}
	}
	return divisores == 1;
}

int qtd_primo_bst(arvore raiz) {
   	while(raiz != NULL){
   		if(primo(raiz->valor)){
   			return 1 + qtd_primo_bst(raiz->esq) + qtd_primo_bst(raiz->dir);
   		}
   		return 0 + qtd_primo_bst(raiz->esq) + qtd_primo_bst(raiz->dir);
   	}
    }

void sucessor_bst(int n, arvore raiz) {
    arvore sucessor = NULL;		//Criar as variaveis sucessor e atual para percorrer a arvore
    arvore atual = raiz;

    while (atual != NULL) {
        if (atual->valor > n) {
            if (sucessor == NULL || atual->valor < sucessor->valor) {
                sucessor = atual;
            }
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if (sucessor != NULL) {
        printf("%d\n", sucessor->valor);
    } else {
        printf("-1\n");
    }
}

void caminho_bst(int n, arvore raiz){
	arvore atual = raiz;		//Variavel para percorrer a arvore
	
	while(atual != NULL){
		printf("[%d]", atual->valor);
		if(atual->valor == n){
			break;
		}
		if(n < atual->valor){
			atual = atual->esq;
		}else{
			atual = atual->dir;
		}
	}
	printf("\n");
}

int somatorio_bst(arvore raiz){
	if(raiz != NULL){
		return raiz->valor + somatorio_bst(raiz->esq) + somatorio_bst(raiz->dir);
	}
}

int altura_bst(arvore raiz){
	while(raiz != NULL){
		int altura_esquerda = altura_bst(raiz->esq);
		int altura_direita = altura_bst(raiz->dir);
		
		if(altura_esquerda > altura_direita){
			return 1 + altura_esquerda;
		}else{
			return 1 + altura_direita;
		}
	}
}

int existe_bst(arvore raiz, int elemento){
	while(raiz != NULL){
		if(raiz->valor == elemento){
			return 1;
		}
		if(elemento < raiz->valor){
			return existe_bst(raiz->esq, elemento);
		}else{
			return existe_bst(raiz->dir, elemento);
		}
	}
}

arvore podar_bst(int n, arvore raiz){
	while(raiz != NULL){
		if(n < raiz->valor){
			raiz->esq = podar_bst(n, raiz->esq);
		}else if(n > raiz->valor){
			raiz->dir = podar_bst(n, raiz->dir);
		}else{
			if(raiz->esq != NULL){
				raiz->esq = podar_bst(raiz->esq->valor, raiz->esq);
			}
			if(raiz->dir != NULL){
				raiz->dir = podar_bst(raiz->dir->valor, raiz->dir);
			}
			
			free(raiz);
			return NULL;
		}
	}
	return raiz;
}

void reajusta_bst(arvore raiz, float percentual){
	while(raiz != NULL && raiz->valor >= 1){
		raiz->valor = (int)(raiz->valor * (1 + percentual));
		reajusta_bst(raiz->esq, percentual);
		reajusta_bst(raiz->dir, percentual);
	}
}

void descendentes_bst(int n, arvore raiz) {
    if (raiz == NULL) {
        return; 
    }

    if (raiz->valor == n) {
        if (raiz->esq != NULL) {
            in_order_bst(raiz->esq);
        }
        printf("[%d]", raiz->valor);
        if (raiz->dir != NULL) {
            in_order_bst(raiz->dir);
        }
        printf("\n"); 
    } else if (n < raiz->valor) {
        descendentes_bst(n, raiz->esq); 
    } else {
        descendentes_bst(n, raiz->dir); 
    }
}

//Função aux maior para a remover_bst
arvore maior(arvore raiz){
	if(raiz == NULL){
		return NULL;
	}
	if(raiz->dir == NULL){
		return raiz;
	}
	return maior(raiz->dir);
}



arvore remover_bst(arvore raiz, int valor){
	if(raiz == NULL){
		return NULL;
	}
	if(raiz->valor == valor){
		//Primeiro caso = 0 filhos
		if(raiz->esq == NULL && raiz->dir == NULL){
			free(raiz);
			return NULL;
		}
		//Segundo caso (a) = 1 filho na esquerda
		if(raiz->esq != NULL && raiz->dir == NULL){
			arvore aux = raiz->esq;
			free(raiz);
			return aux;
		}
		//Segundo caso (b) = 1 filho na direita
		if(raiz->esq == NULL && raiz->dir != NULL){
			arvore aux = raiz->dir;
			free(raiz);
			return aux;
		}
		//Terceiro caso = 2 filhos
		//Função aux
		int maiorValorSubarvoreEsquerda = maior(raiz->esq)->valor;
		raiz->valor = maiorValorSubarvoreEsquerda;
		raiz->esq = remover_bst(raiz->esq, maiorValorSubarvoreEsquerda);
		return raiz;
	}
	if(valor > raiz->valor){
		raiz->dir = remover_bst(raiz->dir, valor);
	}else{
		raiz->esq = remover_bst(raiz->esq, valor);
	}
	return raiz;
}