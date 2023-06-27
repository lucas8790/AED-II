#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
	//declara a árvore
	arvore a;
	int opcao, aux;
	
	//incializa a árvore como vazia
	a = NULL;
	int *cresceu = malloc(sizeof(int));
	int *diminuiu = malloc(sizeof(int));
	
	while(1){
		scanf("%d", &opcao);
		switch(opcao) {
			case 1:
				scanf("%d", &aux);
				a = inserir_avl(a, aux, cresceu);
				break;
    			case 2:
    				scanf("%d", &aux);
    				a = remover_avl(aux, a, diminuiu);
    				break;
    			case 3:
    				pre_order_avl(a);
    				printf("\n");
    				break;
    			case 99:
    				exit(0);
		}
	}
}