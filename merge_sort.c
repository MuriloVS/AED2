#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mostraVetor(int v[], int tamanho);
void mergeSort(int v[], int inicio, int fim);
void merge(int v[], int inicio, int meio, int fim);

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

    if(vetor != NULL)
    {
        for(int i = 0; i < testes; i++)
        {
            // novos elementos desordenados a cada loop de teste
            for(int i = 0; i < tamanho; i++)
                vetor[i] = rand() % (tamanho + 1);
            
            //mostraVetor(vetor, tamanho);       

            // INICIO DA TOMADA DE TEMPO NA LINHA ABAIXO
            start = clock();

            // -1 porque queremos o índice do último elemento
            mergeSort(vetor, 0, tamanho-1);            

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

void mergeSort(int v[], int inicio, int fim)
{
    if(inicio < fim)
    {
        int meio = (fim + inicio) / 2;

        // chamada recursiva para cada metade do vetor
        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, fim);

        // chamada da função que ordena e une os elementos
        merge(v, inicio, meio, fim);
    }
}

void merge(int v[], int inicio, int meio, int fim)
{
    // criação do vetor temporário
    // +1 porque queremos tamanho, não o índice do último elemento
    int tamanho = fim - inicio + 1;
    int *v_temp = (int *)malloc(tamanho * sizeof(int));

    // variáveis para controlar o índice de ínicio de cada metade
    int p1 = inicio, p2 = meio + 1;

    int i = 0;

    if(v_temp != NULL)
    {
        // preenchimento inicial do vetor com os menores elementos de cada metade
        while(p1 <= meio && p2 <= fim)
        {
            if(v[p1] < v[p2])
                v_temp[i++] = v[p1++];
            else
                v_temp[i++] = v[p2++];
        }

        // nestes dois whiles garantimos que nenhum elemento tenha sido 'esquecido'
        while(p1 <= meio)
            v_temp[i++] = v[p1++];
        while(p2 <= fim)
            v_temp[i++] = v[p2++];

        // aqui substituímos os elementos do vetor original por elementos ordenados
        for(int j = inicio; j <= fim; ++j)
            v[j] = v_temp[j - inicio];
    }

    if(v_temp != NULL)
        free(v_temp);
}