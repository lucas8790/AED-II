#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

arvore maiorNo(arvore a){
    if(a != NULL){
        if(a->dir == NULL){
            return a;
        }
        return maiorNo(a->dir);
    }
    return NULL;
}

arvore menorNo(arvore a){
    if(a != NULL){
        if(a->esq == NULL){
            return a;
        }
        return menorNo(a->esq);
    }
    return NULL;
}

arvore rotacaoSimplesEsquerda(arvore pivo){
	arvore u = pivo->dir;
	arvore t2 = u->esq;
	
	u->esq = pivo;
	pivo->dir = t2;
	
	if(u->fb == 1){
		pivo->fb = 0;
		u->fb = 0;
	}else{
		pivo->fb = 1;
		u->fb = -1;
	}
	
	return u;
}

arvore rotacaoSimplesDireita(arvore pivo){
	arvore u = pivo->esq;
	arvore t2 = u->dir;
	
	u->dir = pivo;
	pivo->esq = t2;
	
	if(u->fb == -1){
		pivo->fb = 0;
		u->fb = 0;
	}else{
		pivo->fb = -1;
		u->fb = 1;
	}
	
	return u;
}

arvore rotacaoDuplaEsquerda(arvore pivo){
    arvore u = pivo->dir;
    arvore v = u->esq;
    arvore t1 = u->esq;
    arvore t2 = v->esq;
    arvore t3 = v->dir;
    arvore t4 = pivo->dir;

    pivo->dir = v;
    v->dir = u;
    u->esq = t3;

    pivo->dir = t2;
    v->esq = pivo;

    switch (v->fb) {
        case 0:
            pivo->fb = 0;
            u->fb = 0;
            v->fb = 0;
            break;
        case 1:
            pivo->fb = 0;
            u->fb = 1;
            v->fb = 0;
            break;
        case -1:
            pivo->fb = -1;
            u->fb = 0;
            v->fb = 0;
            break;
    }
    return v;
}

arvore rotacaoDuplaDireita(arvore pivo){
    arvore u = pivo->esq;
    arvore v = u->dir;
    arvore t1 = u->esq;
    arvore t2 = v->esq;
    arvore t3 = v->dir;
    arvore t4 = pivo->dir;

    pivo->esq = v;
    v->esq = u;
    u->dir = t2;

    pivo->esq = t3;
    v->dir = pivo;

    switch (v->fb) {
        case 0:
            pivo->fb = 0;
            u->fb = 0;
            v->fb = 0;
            break;
        case 1:
            pivo->fb = 0;
            u->fb = -1;
            v->fb = 0;
            break;
        case -1:
            pivo->fb = 1;
            u->fb = 0;
            v->fb = 0;
            break;
    }
    return v;
}

arvore rotacao(arvore pivo){
	if(pivo->fb > 0){
		//Ou seja vai inserir na direita, e rotaciona para a esquerda <--
		switch(pivo->dir->fb){
			case 0:
			case 1:
				return rotacaoSimplesEsquerda(pivo);
			case -1:
				return rotacaoDuplaEsquerda(pivo);
		}
	}else{
		switch(pivo->esq->fb){
			case 0:
			case 1:
				return rotacaoSimplesDireita(pivo);
			case -1:
				return rotacaoDuplaDireita(pivo);
		}
	}
}

int maior(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

arvore inserir_avl(arvore raiz, tipo_dado valor, int *cresceu){
	if(raiz == NULL){
		arvore novo = (arvore)malloc(sizeof(struct no));
		novo->esq = NULL;
		novo->dir = NULL;
		novo->valor = valor;
		novo->fb = 0;
		*cresceu = 1;
		return novo;
	}
	
	if(valor < raiz->valor){
		//Inserir na esquerda
		raiz->esq = inserir_avl(raiz->esq, valor, cresceu);
		
		if(*cresceu){
			switch(raiz->fb){
				case 0:
					raiz->fb = -1;
					*cresceu = 1;
					break;
				case -1: 
					*cresceu = 0;
					return rotacao(raiz);
				case 1:
					raiz->fb = 0;
					*cresceu = 0;
					break;
			}
		}	
	}else{
		//Inserir na direita
		raiz->dir = inserir_avl(raiz->dir, valor, cresceu);
		
		if(*cresceu){
			switch(raiz->fb){
				case 0:
					raiz->fb = 1;
					*cresceu = 1;
					break;
				case -1:
					raiz->fb = 0;
					*cresceu = 0;
					break;
				case 1:
					*cresceu = 0;
					return rotacao(raiz);
			}
		}
	}
	
	return raiz;
}

void pre_order_avl(arvore raiz){
	if(raiz != NULL){
		//processar a raiz relativa
		printf("[%d] - %d ", raiz->valor, raiz->fb);
		
		//encadeamentos recursivos esq, dir
		pre_order_avl(raiz->esq);
		pre_order_avl(raiz->dir);
	} //else caso base implicito não faz nada
}

arvore remover_avl(tipo_dado valor, arvore raiz, int *diminuiu){
	if(raiz == NULL){
		*diminuiu = 0;
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
		if(raiz->esq != NULL && raiz->dir != NULL){
            		arvore maiorElemento = maiorNo(raiz->esq);
            		raiz->valor = maiorElemento->valor;

            		raiz->esq = remover_avl(maiorElemento->valor, raiz->esq, diminuiu);

            		if(*diminuiu == 1){
                		switch (raiz->fb) {
                    			case 0:
                        			raiz->fb = 1;
                        			*diminuiu = 0;
                        			break;
                    			case -1:
                        			raiz->fb = 0;
                        			*diminuiu = 1;
                        			break;
                    			case 1:
                        			if(raiz->dir->fb != 0){
                            				*diminuiu = 1;
                        			}else{
                            				*diminuiu = 0;
                        			}
                        			return rotacao(raiz);
                		}
            		}

            		return raiz;
        	}
        }
	if(valor < raiz->valor){
        	raiz->esq = remover_avl(valor, raiz->esq, diminuiu);
        	if(*diminuiu){
            		switch (raiz->fb) {
                		case 0:
                    			raiz->fb = 1;
                    			*diminuiu = 0;
                    			break;
                		case -1:
                    			raiz->fb = 0;
                    			*diminuiu = 1;
                    			break;
                		case 1:
                    			if(raiz->dir->fb != 0){
                        		*diminuiu = 1;
                    		}else{
                        		*diminuiu = 0;
                    		}

                    		return rotacao(raiz);
            		}
       		 }
    	}else{
        	raiz->dir = remover_avl(valor, raiz->dir, diminuiu);

        	if(*diminuiu){
            		switch (raiz->fb) {
                		case 0:
                    			raiz->fb = -1;
                    			*diminuiu = 0;
                    		break;
                		case -1:
                    			if(raiz->esq->fb != 0){
                        			*diminuiu = 1;
                    			}else{
                        			*diminuiu = 0;
                    			}
                    			return rotacao(raiz);
                		case 1:
                    			raiz->fb = 0;
                    			*diminuiu = 1;
                    		break;
            		}
        	}
    	}
	return raiz;
}