#include <stdlib.h>
#include <stdio.h>

typedef struct item
{
    int codigo;
    /* outros campos */
} TProduto;

typedef struct celula
{
    TProduto item;
    struct celula *prox;
} TCelula;

typedef struct fila
{
    TCelula *frente;
    TCelula *tras;
    int tamanho;
} TFila;

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

void Enfileirar(TProduto x, TFila *Fila)
{
    Fila->tras->prox = (TCelula*) malloc(sizeof(TCelula));
    Fila->tras = Fila->tras->prox;
    Fila->tras->item = x;
    Fila->tras->prox = NULL;
    Fila->tamanho++;
}

void Desenfileirar(TFila *Fila, TProduto *Item)
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

TProduto Pesquisar(TFila Fila, TProduto Item)
{
    TProduto x;

    x.codigo = -1;

    if(Vazia(Fila) != 1)
    {
        TFila aux;
        FFVazia(&aux);
        TCelula *aux2;
        TProduto item;
        aux2 = Fila.frente;
        while(aux2->prox != NULL)
        {
            Desenfileirar(&Fila, &item);
            if(Item.codigo == item.codigo)
            {
                x.codigo = item.codigo;
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
        TProduto itemAux;
        Desenfileirar(Fila, &itemAux);
    }

    free(Fila->frente);
}

void Imprimir(TFila *Fila)
{
    TProduto item;
    int tamanho = Fila->tamanho;

    while(tamanho > 0)
    {
        Desenfileirar(Fila, &item);
        printf("%d\n", item.codigo);
        Enfileirar(item, Fila);
        tamanho--;
    }
}

void Imprimir2(TFila *Fila)
{
    TFila aux;
    FFVazia(&aux);
    TProduto item;

    while(Vazia(*Fila) != 1)
    {
        Desenfileirar(Fila, &item);
        printf("%d\n", item.codigo);
        Enfileirar(item, &aux);
    }

    while(Vazia(aux) != 1)
    {
        Desenfileirar(&aux, &item);
        Enfileirar(item, Fila);
    }

    Liberar(&aux);
}

int main()
{
    TFila fila;
    TProduto item;

    FFVazia(&fila);

    item.codigo = 1;
    Enfileirar(item, &fila);

    item.codigo = 2;
    Enfileirar(item, &fila);

    item.codigo = 3;
    Enfileirar(item, &fila);

    Imprimir(&fila);
    printf("\n\n");

    Imprimir(&fila);
    printf("\n\n");

    Imprimir(&fila);
    printf("\n\n");

    item.codigo = 5;
    printf("%d", Pesquisar(fila, item).codigo);

    printf("\n\n");
    Imprimir(&fila);

    printf("\n\n");
    Liberar(&fila);
    Imprimir(&fila);

    printf("\n\n%d", Vazia(fila));

    return 0;
}
