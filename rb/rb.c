#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

arvore no_null;

void rotacaoSimplesDireita(arvore *raiz, arvore pivot) {
    arvore u, t1;
    u = pivot->esq;
    t1 = u->dir;

    /*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivot p era um filho esquerdo ou direito*/
    int posicao_pivo_esq = eh_filho_esquerdo(pivot);

    //Atualização dos ponteiros
    pivot->esq = t1;
    if (t1 != NULL)
        t1->pai = pivot;

    u->dir = pivot;

    u->pai = pivot->pai;
    pivot->pai = u;



    //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if (eh_raiz(u))
        *raiz = u;
    else {
        //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
        if (posicao_pivo_esq)
            u->pai->esq = u;
        else
            u->pai->dir = u;
    }
}

void rotacaoSimplesEsquerda(arvore *raiz, arvore pivot) {
    arvore u, t1;
    u = pivot->dir;
    t1 = u->esq;

    /*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivot p era um filho esquerdo ou direito*/
    int posicao_pivo_esq = eh_filho_esquerdo(pivot);

    //Atualização dos ponteiros
    pivot->dir = t1;
    if (t1 != NULL)
        t1->pai = pivot;

    u->esq = pivot;

    u->pai = pivot->pai;
    pivot->pai = u;



    //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if (eh_raiz(u))
        *raiz = u;
    else {
        //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
        if (posicao_pivo_esq)
            u->pai->esq = u;
        else
            u->pai->dir = u;
    }
}

void rotacaoDuplaDireita(arvore *raiz, arvore pivot) {
    arvore u = pivot->esq;
    arvore v = u->dir;

    arvore t2 = v->esq;
    arvore t3 = v->dir;
    arvore t4 = pivot->dir;

    int posicao_pivo_esq = eh_filho_esquerdo(pivot);

    pivot->esq = v;
    v->esq = u;
    u->dir = t2;

    pivot->esq = t3;
    v->dir = pivot;

    if (t2 != NULL) {
        t2->pai = u;
    }

    if (t3 != NULL) {
        t3->pai = pivot;
    }

    if (t4 != NULL) {
        t4->pai = pivot;
    }

    v->pai = pivot->pai;
    pivot->pai = v;
    u->pai = v;

    //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if (eh_raiz(v))
        *raiz = v;
    else {
        //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
        if (posicao_pivo_esq)
            v->pai->esq = v;
        else
            v->pai->dir = v;
    }
}

void rotacaoDuplaEsquerda(arvore *raiz, arvore pivot) {
    arvore u = pivot->dir;
    arvore v = u->esq;
    arvore t2 = v->esq;
    arvore t3 = v->dir;
    arvore t4 = u->dir;

    int posicao_pivo_esq = eh_filho_esquerdo(pivot);

    pivot->dir = v;
    v->dir = u;
    u->esq = t3;

    pivot->dir = t2;
    v->esq = pivot;

    if (t2 != NULL) {
        t2->pai = pivot;
    }

    if (t3 != NULL) {
        t3->pai = u;
    }

    if (t4 != NULL) {
        t4->pai = u;
    }
    v->pai = pivot->pai;

    pivot->pai = v;
    u->pai = v;

    //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if (eh_raiz(v))
        *raiz = v;
    else {
        //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
        if (posicao_pivo_esq)
            v->pai->esq = v;
        else
            v->pai->dir = v;
    }
}

enum cor cor(arvore elemento) {
    enum cor c;
    if (elemento == NULL)
        c = PRETO;
    else
        c = elemento->cor;
    return c;
}

//Função eh raiz:
int eh_raiz(arvore elemento) {
    return (elemento->pai == NULL);
}

//Verifica se um nó é filho esquerdo
int eh_filho_esquerdo(arvore elemento) {
    return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

int eh_filho_direito(arvore elemento) {
    return (elemento->pai != NULL && elemento == elemento->pai->dir);
}

//Função Tio
arvore tio(arvore elemento) {
    return irmao(elemento->pai);
}

//Função Irmão
arvore irmao(arvore elemento) {
    if (eh_filho_esquerdo(elemento))
        return elemento->pai->dir;
    else
        return elemento->pai->esq;
}

int maior(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int maior_elemento(arvore raiz) {
    if (raiz == NULL)
        return -1;
    if (raiz->dir == NULL)
        return raiz->valor;
    else
        return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz) {
    if (raiz == NULL)
        return -1;
    if (raiz->esq == NULL)
        return raiz->valor;
    else
        return maior_elemento(raiz->esq);
}

void imprimir_elemento(arvore raiz) {
    switch (raiz->cor) {
        case PRETO:
            printf("\x1b[30m[%d]\x1b[0m", raiz->valor);
            break;
        case VERMELHO:
            printf("\x1b[31m[%d]\x1b[0m", raiz->valor);
            break;
        case DUPLO_PRETO:
            printf("\x1b[32m[%d]\x1b[0m", raiz->valor);
            break;
    }
}

void pre_order_rb(arvore raiz) {
    if (raiz != NULL) {
        imprimir_elemento(raiz);
        pre_order_rb(raiz->esq);
        pre_order_rb(raiz->dir);
    }
}

void RetiraDuploPreto(arvore *raiz, arvore elemento) {
    if (elemento == no_null) {
        if (eh_raiz(elemento)) {
            *raiz = NULL;
        } else {
            if (eh_filho_esquerdo(elemento)) {
                elemento->pai->esq = NULL;
            } else {
                elemento->pai->dir = NULL;
            }
        }
    } else {
        elemento->cor = PRETO;
    }
}

void reajustar(arvore *raiz, arvore elemento) {
    //Caso 1 -  O mais simples:	
    if (eh_raiz(elemento)) {
        RetiraDuploPreto(raiz, elemento);
        return;
    }

    //Caso 2
    if (cor(elemento->pai) == PRETO &&
        cor(irmao(elemento)) == VERMELHO &&
        cor(irmao(elemento)->dir) == PRETO &&
        cor(irmao(elemento)->esq) == PRETO) {
        
        if (eh_filho_esquerdo(elemento))
            rotacaoSimplesEsquerda(raiz, elemento->pai);
        else
            rotacaoSimplesDireita(raiz, elemento->pai);
        elemento->pai->pai->cor = PRETO;
        elemento->pai->cor = VERMELHO;

        reajustar(raiz, elemento);
        return;
    }

    //Caso 3
    if (cor(elemento->pai) == PRETO &&
        cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->dir) == PRETO &&
        cor(irmao(elemento)->esq) == PRETO) {
  
        elemento->pai->cor = DUPLO_PRETO;
        irmao(elemento)->cor = VERMELHO;

        RetiraDuploPreto(raiz, elemento);
        reajustar(raiz, elemento->pai);
        return;
    }

    //Caso 4
    if (cor(elemento->pai) == VERMELHO &&
        cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->dir) == PRETO &&
        cor(irmao(elemento)->esq) == PRETO) {

        elemento->pai->cor = PRETO;
        irmao(elemento)->cor = VERMELHO;

        RetiraDuploPreto(raiz, elemento);
        return;
    }

    //Caso 5A - Direito
    if (cor(elemento->pai->dir) == PRETO &&
        cor(elemento->pai->dir->esq) == VERMELHO &&
        cor(elemento->pai->dir->dir) == PRETO) {

        rotacaoSimplesDireita(raiz, irmao(elemento));
        irmao(elemento)->cor = PRETO;
        irmao(elemento)->dir->cor = VERMELHO;

        reajustar(raiz, elemento);
        return;
    }

    //Caso 5B - Esquerda
    if (cor(elemento->pai->esq) == PRETO &&
        cor(elemento->pai->esq->esq) == PRETO &&
        cor(elemento->pai->esq->dir) == VERMELHO) {

        rotacaoSimplesEsquerda(raiz, irmao(elemento));
        irmao(elemento)->cor = PRETO;
        irmao(elemento)->esq->cor = VERMELHO;

        reajustar(raiz, elemento);
        return;
    }

    //Caso 6A
    if (cor(elemento->pai->dir) == PRETO &&
        cor(elemento->pai->dir->dir) == VERMELHO) {
        enum cor hold_cor = elemento->pai->cor;
        rotacaoSimplesEsquerda(raiz, elemento->pai);

        elemento->pai->pai->cor = hold_cor;
        elemento->pai->cor = PRETO;
        irmao(elemento->pai)->cor = PRETO;

        RetiraDuploPreto(raiz, elemento);
        return;
    }

    //Caso 6B
    if (cor(elemento->pai->esq) == PRETO &&
        cor(elemento->pai->esq->esq) == VERMELHO) {

        enum cor hold_cor = elemento->pai->cor;
        rotacaoSimplesDireita(raiz, elemento->pai);

        elemento->pai->pai->cor = hold_cor;
        elemento->pai->cor = PRETO;
        irmao(elemento->pai)->cor = PRETO;

        RetiraDuploPreto(raiz, elemento);
        return;
    }
}

void ajustar(arvore *raiz, arvore elemento) {
    while (cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {
        //Caso 1: Cor do tio é vermelha então desce o preto do avô.
        if (cor(tio(elemento)) == VERMELHO) {
            tio(elemento)->cor = PRETO;
            elemento->pai->cor = PRETO;
            elemento->pai->pai->cor = VERMELHO;
            //Continua a verificação a partir do avô.
            elemento = elemento->pai->pai;
            continue;
        } else {
            //Caso 2A: R.S.D
            if (eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
                rotacaoSimplesDireita(raiz, elemento->pai->pai);
                elemento->pai->cor = PRETO;
                elemento->pai->dir->cor = VERMELHO;
                continue;
            }
            //Caso 2B: R.S.E
            if (eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)) {
                rotacaoSimplesEsquerda(raiz, elemento->pai->pai);
                elemento->pai->cor = PRETO;
                elemento->pai->esq->cor = VERMELHO;
                continue;
            }
            //Caso 3A: R.D.D
            if (eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai)) {
                rotacaoDuplaDireita(raiz, elemento->pai->pai);
                elemento->cor = PRETO;
                elemento->dir->cor = VERMELHO;
                continue;
            }
            //caso 3B: R.D.E
            if (eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai)) {
                rotacaoDuplaEsquerda(raiz, elemento->pai->pai);
                elemento->cor = PRETO;
                elemento->esq->cor = VERMELHO;
                continue;
            }
        }

    }
    //Se raiz ficou vermelha, muda para preta.
    (*raiz)->cor = PRETO;
}

void inserir_rb(int valor, arvore *raiz) {
    arvore posicao, pai, novo;
    posicao = *raiz;
    pai = NULL;

    while (posicao != NULL) {
        pai = posicao;
        if (valor > posicao->valor)
            posicao = posicao->dir;
        else
            posicao = posicao->esq;
    }

    novo = (arvore) malloc(sizeof(struct no_bst));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = pai;
    novo->cor = VERMELHO;

    if (eh_raiz(novo))
        *raiz = novo;
    else {
        if (valor > pai->valor)
            pai->dir = novo;
        else
            pai->esq = novo;
    }
    ajustar(raiz, novo);
}

void remover_rb(int valor, arvore *raiz) {
    arvore posicao;
    posicao = *raiz;

    while (posicao != NULL) {
        if (valor == posicao->valor) {
            //Dois filhos
            if (posicao->esq != NULL && posicao->dir != NULL) {
                posicao->valor = maior_elemento(posicao->esq);
                remover_rb(posicao->valor, &(posicao->esq));
                break;
            }

            //Um filho direito
            if (posicao->esq == NULL && posicao->dir != NULL) {
                arvore elementoDireita = posicao->dir;
                posicao->valor = elementoDireita->valor;
                posicao->cor = PRETO;
                posicao->dir = NULL;

                free(elementoDireita);
                break;
            }


            //Um filho esquerdo
            if (posicao->dir == NULL && posicao->esq != NULL) {
                arvore elementosEsquerdo = posicao->esq;
                posicao->valor = elementosEsquerdo->valor;
                posicao->cor = PRETO;
                posicao->esq = NULL;

                free(elementosEsquerdo);
                break;
            }

            //Não possui filhos
            if (posicao->esq == NULL && posicao->dir == NULL) {
                if (eh_raiz(posicao)) {
                    *raiz = NULL;
                    free(posicao);
                    break;
                }

                if (posicao->cor == VERMELHO) {
                    if (eh_filho_esquerdo(posicao))
                        posicao->pai->esq = NULL;
                    else
                        posicao->pai->dir = NULL;
                    free(posicao);
                    break;
                } else {
                    no_null->cor = DUPLO_PRETO;
                    no_null->pai = posicao->pai;
                    if (eh_filho_esquerdo(posicao))
                        posicao->pai->esq = no_null;
                    else
                        posicao->pai->dir = no_null;
                    free(posicao);
                    reajustar(raiz, no_null);
                    break;
                }
            }
        }
        if (valor > posicao->valor)
            posicao = posicao->dir;
        else
            posicao = posicao->esq;
    }
}