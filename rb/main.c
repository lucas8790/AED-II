#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
	//declara a árvore
	arvore a;
	int opcao, aux;
	
	//incializa a árvore como vazia
	a = NULL;
	
	while(1){
		scanf("%d", &opcao);
		switch(opcao) {
			case 1:
				scanf("%d", &aux);
				inserir_rb(aux, &a);
				break;
    			case 2:
    				scanf("%d", &aux);
    				remover_rb(aux, &a);
    				break;
    			case 3:
    				pre_order_rb(a);
    				printf("\n");
    				break;
    			case 99:
    				exit(0);
		}
	}
}