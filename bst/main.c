#include "bst.h"
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
				a = inserir_bst(aux, a);
				break;
			case 2:
				pre_order_bst(a);
				printf("\n");
				break;
			case 3:
				in_order_bst(a);
				printf("\n");
				break;
			case 4:
				pos_order_bst(a);
				printf("\n");
				break;
			case 5:
				reverso_bst(a);
				printf("\n");
				break;
			case 6:
				printf("%d", qtd_primo_bst(a));
				printf("\n");
				break;
			case 7:
				scanf("%d", &aux);
				sucessor_bst(aux, a);
				printf("\n");
				break;
			case 8:
				scanf("%d", &aux);
				caminho_bst(aux, a);
				printf("\n");
				break;
			case 9:
				scanf("%d", &aux);
				remover_bst(a, aux);
				break;
			case 10:
				printf("%d", somatorio_bst(a));
				printf("\n");
				break;
			case 11:
				scanf("%d", &aux);
				a = podar_bst(aux, a);
				break;
			case 12:
				scanf("%d", &aux);
				reajusta_bst(a, aux);
				in_order_bst(a);
				printf("\n");
				break;
			case 13:
				scanf("%d", &aux);
				printf("%d", existe_bst(a, aux));
				printf("\n");
				break;
			case 14:
				scanf("%d", &aux);
				descendentes_bst(aux, a);
				printf("\n");
				break;
    			case 15:
    				printf("%d", altura_bst(a));
    				printf("\n");
    				break;
    			case 99:
    				exit(0);
		}
	}
}