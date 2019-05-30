#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mostraVetor(int v[], int tamanho);

int main() {
    // seed para os números randômicos
    srand(time(NULL));

    int tamanho;
    printf("Tamanho do vetor: ");
    scanf(" %d", &tamanho);

    // variáveis para fazer a métrica
    int testes = 20;
    clock_t start;
    double tempo, soma = 0, menor, maior;

    // criação do vetor
    int *vetor = (int *)malloc(tamanho * sizeof(int));

    // variável utilizada para auxiliar na troca das posições
    int aux;

    if(vetor != NULL)
    {
        for(int i = 0; i < testes; i++)
        {
            // novos elementos desordenados a cada loop de teste
            for(int j = 0; j < tamanho; j++)
                vetor[j] = rand() % (tamanho + 1);           
            
            //mostraVetor(vetor, tamanho);       

            // INICIO DA TOMADA DE TEMPO NA LINHA ABAIXO
            start = clock();

            // iníciamos em 1 porque usamos o j para evitar estouro de índice no loop interno
            for(int j = 1; j < tamanho; j++)     
            {
                for(int g = 0; g < tamanho - j; g++)
                {                   
                    if(vetor[g] > vetor[g+1])
                    {                        
                        aux = vetor[g+1];
                        vetor[g+1] = vetor[g];
                        vetor[g] = aux;
                    }
                }
            }

            tempo = (double)(clock() - start)/CLOCKS_PER_SEC;
            // FINAL DA TOMADA DE TEMPO NA LINHA ACIMA
            
            //mostraVetor(vetor, tamanho);       

            if(i == 0)
            {
                menor = tempo;
                maior = tempo;
            }

            if(tempo < menor)
                menor = tempo;
            if(tempo > maior)
                maior = tempo;
            
            soma += tempo;
            //printf("tempo = %f\n", tempo);
        }

        printf("Menor....: %f\n", menor);
        printf("Maior....: %f\n", maior);
        printf("Média....: %f\n", soma/testes);

        free(vetor);
    }
    else
        printf("Erro na criação do vetor!\n");
    
    return 0;
}


void mostraVetor(int v[], int tamanho)
{
    for(int i = 0; i < tamanho; i++)
        printf("%d ", v[i]);
    
    printf("\n");
}