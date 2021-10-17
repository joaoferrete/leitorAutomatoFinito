/*
	---SIMULADOR UNIVERSAL DE AUTOMATOS FINITOS DETERMINISTICOS---
	
	TRABALHO DE LINGUAGENS FORMAIS E AUTOMATOS
	ALUNO: JOÃO PAULO SOUZA FERRETE
	MATRICULA: 2018205041

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    true = 1,
    false = 0
}boolean;

boolean estadoFinal(char estado, int numEstados, char estadosFinais[]){
    //Função que verifica se um estado é um estado final
    for(int i = 0; i < numEstados; i++){
        if(estado == estadosFinais[i]){
            return true;
        }
    }   
    return false;
}

boolean taNoDicionario(char elemento, char simbolosFinais[], int numSimbolosFinais){
    //Função que verifica se um elemento está no dicionário
    for(int i = 0; i < numSimbolosFinais; i++){
        if(elemento == simbolosFinais[i]){
            return true;
        }
    }
    return false;
}


boolean pertence(char estadosFinais[],int numEstados, char transicoes[][3], 
int numTransicoes, char simbolosFinais[], int numSimbolos){
    //Função que verifica se uma cadeia é lida pelo automato finito
    char cadeia[51];
    char estadoAtual;


    estadoAtual = '0';
    scanf("%s", cadeia);
    boolean entrou = false;
    for(int i = 0; i < strlen(cadeia); i++){    //Percorre a cadeia
        for(int j = 0; j < numTransicoes; j++){ //Percorre as transições
            if (cadeia[i] == '-' && estadoFinal(estadoAtual, numEstados, estadosFinais)) return true;   //Se a cadeia for um lambda e estiver em um  estado final, retorna true
            if(!taNoDicionario(cadeia[i], simbolosFinais, numSimbolos)) return false;   //Se o elemento não estiver no dicionário, retorna false
            if(cadeia[i] == transicoes[j][1] && estadoAtual == transicoes[j][0]){   //Se o elemento for igual ao estado e o estado atual for igual ao estado de transição, entra na condição seguinte
                estadoAtual = transicoes[j][2]; //O estado atual é o estado de transição
                entrou = true;
                break;
            }
            else entrou = false;

        }
        if(!entrou) return false;   //Se não entrou na condição anterior, retorna false
        if (i == strlen(cadeia)-1 && !estadoFinal(estadoAtual, numEstados, estadosFinais)) return false;    //Se for o ultimo elemento da cadeia, e não estiver em um estado final, retorna false
    }
    return true;    //Se chegar ao final, então a cadeia é lida pelo automato

}

int main(){
    int estados, numSimbolosTerminais, numEstadosFinal, numeroTransicoes, numCadeias, a;
    char b;

    scanf("%d", &estados);  //Le o numero de estados

    scanf("%d", &numSimbolosTerminais); //Le o numero de simbolos terminais
    
    char simbolos[numSimbolosTerminais];    
    
    for (int i = 0; i < numSimbolosTerminais; i++) {    //Le os simbolos terminais
        getchar();
        scanf("%c", &simbolos[i]);
    }


    scanf("%d", &a);    

    scanf("%d", &numEstadosFinal);  //Le o numero de estados finais

    char estadosFinais[numEstadosFinal];
    for (int i = 0; i < numEstadosFinal; i++) { //Le os estados finais
        getchar();
        scanf("%c", &estadosFinais[i]);
    }

    scanf("%d", &numeroTransicoes); //Le o numero de transicoes

    char transicoes[numeroTransicoes][3];
    for (int i = 0; i < numeroTransicoes; i++) {    //Le as transicoes
        getchar();
        scanf("%c",&transicoes[i][0]);
        getchar();
        scanf("%c",&transicoes[i][1]);
        getchar();
        scanf("%c",&transicoes[i][2]);
    }
    getchar();

    scanf("%d", &numCadeias);   //Le o numero de cadeias

    while(numCadeias--){    //Percorre as cadeias
        boolean verifica;
        verifica = pertence(estadosFinais, numEstadosFinal, transicoes, numeroTransicoes, simbolos, numSimbolosTerminais);  //Verifica se a cadeia é lida pelo automato
        if(verifica)    //Se a cadeia for lida pelo automato, imprime aceita
            printf("aceita\n");
        else    //Se a cadeia não for lida pelo automato, imprime rejeita
            printf("rejeita\n");
    } 

}
