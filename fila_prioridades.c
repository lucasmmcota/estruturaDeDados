#include <stdlib.h>
#include <stdio.h>

typedef struct item
{
    char elemento;
    int prioridade;
} TipoItem;

typedef struct celula
{
    TipoItem item;
    struct celula *prox;
} TCelula;

typedef struct fila
{
    TCelula *frente;
    TCelula *tras;
    int tamanho;
} TFila;

typedef struct fila_prioridade
{
    TFila fila_prioridade1;
    TFila fila_prioridade2;
    TFila fila_prioridade3;
} TFilaPrioridade;

void FFVazia(TFila *Fila)
{
    Fila->frente = (TCelula*) malloc(sizeof(TCelula));
    Fila->tras = Fila->frente;
    Fila->frente->prox = NULL;
    Fila->tamanho = 0;
}

int Vazia(TFila Fila)
{
    return (Fila.frente == Fila.tras);
}

void Enfileirar(TipoItem x, TFila *Fila)
{
    Fila->tras->prox = (TCelula*) malloc(sizeof(TCelula));
    Fila->tras = Fila->tras->prox;
    Fila->tras->item = x;
    Fila->tras->prox = NULL;
    Fila->tamanho++;
}

void Desenfileirar(TFila *Fila, TipoItem *Item)
{
    if (!Vazia(*Fila))
    {
        TCelula *aux;
        aux = Fila->frente->prox;
        Fila->frente->prox = aux->prox;
        *Item = aux->item;
        free(aux);
        if (Fila->frente->prox == NULL)
        {
            Fila->tras = Fila->frente;
        }
        Fila->tamanho--;
    }
}

TipoItem Pesquisar(TFila Fila, TipoItem Item)
{
    TipoItem x;

    x.prioridade = -1;

    if(Vazia(Fila) != 1)
    {
        TFila aux;
        FFVazia(&aux);
        TCelula *aux2;
        TipoItem item;
        aux2 = Fila.frente;
        while(aux2->prox != NULL)
        {
            Desenfileirar(&Fila, &item);
            if(Item.prioridade == item.prioridade)
            {
                x.prioridade = item.prioridade;
            }
            Enfileirar(item, &aux);
            aux2 = Fila.frente;
        }

        aux2 = aux.frente;
        while(aux2->prox != NULL)
        {
            Desenfileirar(&aux, &item);
            Enfileirar(item, &Fila);
            aux2 = aux.frente;
        }

        free(aux2);
    }

    return x;
}

void Liberar(TFila *Fila)
{
    while(Vazia(*Fila) != 1)
    {
        TipoItem itemAux;
        Desenfileirar(Fila, &itemAux);
    }

    free(Fila->frente);
}

void Imprimir(TFila *Fila)
{
    TipoItem item;
    int tamanho = Fila->tamanho;

    if(tamanho > 0)
    {
        while(tamanho > 0)
        {
            Desenfileirar(Fila, &item);
            printf("%c - ", item.elemento);
            printf("%d\n", item.prioridade);
            Enfileirar(item, Fila);
            tamanho--;
        }
    }
    else
    {
        printf("\n\nFila de prioridades vazia !\n\n");
    }
}

void EnQueue(TFilaPrioridade *Fila, TipoItem x)
{
    if(x.prioridade == 3)
    {
        Enfileirar(x, &Fila->fila_prioridade3);
    }
    else if(x.prioridade == 2)
    {
        Enfileirar(x, &Fila->fila_prioridade2);
    }
    else
    {
        Enfileirar(x, &Fila->fila_prioridade1);
    }
}

void DeQueue(TFilaPrioridade *Fila, TipoItem x)
{
    if(Vazia(Fila->fila_prioridade3) != 1)
    {
        Desenfileirar(&Fila->fila_prioridade3, &x);
    }
    else if(Vazia(Fila->fila_prioridade2) != 1)
    {
        Desenfileirar(&Fila->fila_prioridade2, &x);
    }
    else if(Vazia(Fila->fila_prioridade1) != 1)
    {
        Desenfileirar(&Fila->fila_prioridade1, &x);
    }
    else
    {
        printf("\nTodas as filas ja estao vazias !\n");
    }

}

int main()
{
    TFilaPrioridade fila;
    TipoItem item1, item2, item3, item4;

    FFVazia(&fila.fila_prioridade1);
    FFVazia(&fila.fila_prioridade2);
    FFVazia(&fila.fila_prioridade3);

    item1.elemento = 'A';
    item2.elemento = 'B';
    item3.elemento = 'C';
    item4.elemento = 'D';

    item1.prioridade = 1;
    item2.prioridade = 3;
    item3.prioridade = 3;
    item4.prioridade = 2;

    EnQueue(&fila, item1);
    EnQueue(&fila, item2);
    EnQueue(&fila, item3);
    EnQueue(&fila, item4);

    printf("\n\nFila de prioridades 1: \n");
    Imprimir(&fila.fila_prioridade1);

    printf("\n\nFila de prioridades 2: \n");
    Imprimir(&fila.fila_prioridade2);

    printf("\n\nFila de prioridades 3: \n");
    Imprimir(&fila.fila_prioridade3);

    Liberar(&fila.fila_prioridade1);
    Liberar(&fila.fila_prioridade2);
    Liberar(&fila.fila_prioridade3);

    return 0;
}
