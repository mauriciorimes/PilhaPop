#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct no{
    char *string;
    struct no *prox;
};

typedef struct no No;

struct stack{
	No *topo;
};

typedef struct stack Stack;

Stack* createStack(){
	Stack *p = (Stack*) malloc(sizeof(Stack));
	p->topo = NULL;
	return p;
}

char* pop(Stack *s){
    if(s->topo == NULL)
        return NULL;
    else{
        char *carac = (char*)malloc(strlen(s->topo->string) * sizeof(char));
        strcpy(carac, s->topo->string);
        No *aux = s->topo;
        s->topo = aux->prox;
        free(aux);
        return carac;
    }
}

void push(Stack *s, char *c){
    No *novo = (No*)malloc(sizeof(No));
    novo->string = (char*)malloc(strlen(c) * sizeof(char));
    strcpy(novo->string, c);

    novo->prox = s->topo;
    s->topo = novo;
}

float calcular(float operando1, float operando2, char simbolo){
    float result;
    switch (simbolo){
        case 43:
            result = operando1 + operando2;
            return(result);
            break;

        case 45:
            result = operando1 - operando2;
            return(result);
            break;

        case 42:
            result = operando1 * operando2;
            return(result);
            break;
        case 47:
            result = operando1 / operando2;
            return(result);
            break;
        default:
            break;
        }
    return -1;
}

char* analisaExpressao(Stack *s, char *expr){
    int i = 0;
    float valor = 0;
    char simbolo = expr[0];
    float operando1 = 0;
    float operando2 = 0;
    char str[10];

    while(simbolo != '\0'){
        if(isdigit(simbolo)){
            push(s, &simbolo);
        }
        else{
            operando2 = atoi(pop(s));
            operando1 = atoi(pop(s));
            valor = calcular(operando1, operando2, simbolo);
            sprintf(str, "%.2g", valor);
            push(s, str);
        }
        simbolo = expr[++i];
    }
    return pop(s);
}


int main(){
    char expressao[50];
    float resultado;

    Stack *s = createStack();

    scanf("%s", expressao);
    resultado = atoi(analisaExpressao(s, expressao));
    int inteiro = (int)resultado;
    printf("%s = %d", expressao, inteiro);

    return 0;
}
