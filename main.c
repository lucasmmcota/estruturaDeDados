#include <stdlib.h>
#include <stdio.h>

#define MAX 10

typedef struct
{
    int codigo;
} TProduto;

typedef struct celula
{
    TProduto item;
    struct celula *prox;
    struct celular *ant;
} TCelula;

typedef struct
{
    TCelula *primeiro;
    TCelula *ultimo;
    int tamanho;
} TListaDupla;

void FLDVazia(TListaDupla *Lista)
{
    Lista->primeiro = (TCelula *) malloc(sizeof(TCelula));
    Lista->ultimo = Lista->primeiro;
    Lista->primeiro->prox = NULL;
    Lista->primeiro->ant = NULL;
    Lista->tamanho = 0;
}

int Vazia(TListaDupla Lista)
{
    return (Lista.primeiro == Lista.ultimo);
}

void Inserir(TProduto x, TListaDupla *Lista)
{
    Lista->ultimo->prox = (TCelula *) malloc(sizeof(TCelula));
    Lista->ultimo->prox->ant = Lista->ultimo;
    Lista->ultimo = Lista->ultimo->prox;
    Lista->ultimo->item = x;
    Lista->ultimo->prox = NULL;
    Lista->tamanho++;
}

TCelula* Pesquisar(TListaDupla Lista, TProduto Item)
{
    TCelula* Aux;
    Aux = Lista.primeiro;

    while(Aux->prox != NULL)
    {
        if(Aux->prox->item.codigo == Item.codigo)
        {
            return Aux;
        }
        Aux = Aux->prox;
    }

    return NULL;
}

void Excluir(TListaDupla *Lista, TProduto *Item)
{
    /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
    TCelula *Aux1, *Aux2;
    Aux1 = Pesquisar(*Lista, *Item);

    if(Aux1 != NULL)
    {
        Aux2 = Aux1->prox;
        Aux1->prox = Aux2->prox;
        *Item = Aux2->item;
        if (Aux1->prox == NULL)
        {
            Lista->ultimo = Aux1;
        }
        free(Aux2);
        Lista->tamanho--;
    }
}

void Imprimir(TListaDupla Lista)
{
    if(Vazia(Lista) != 1)
    {
        TCelula* Aux;
        Aux = Lista.primeiro->prox;

        while(Aux != NULL)
        {
            printf("%d\n", Aux->item.codigo);
            Aux = Aux->prox;
        }
    }
}

void Alterar(TListaDupla *Lista, TProduto *Item, TProduto item)
{
    if(Vazia(*Lista) != 1)
    {
        TCelula *aux;
        aux = Pesquisar(*Lista, *Item);

        if(aux != NULL)
        {
            aux->prox->item = item;
        }
    }
}

void Liberar(TListaDupla *Lista)
{
    while(Vazia(*Lista) != 1)
    {
        Excluir(Lista, &Lista->primeiro->prox->item);
    }

    free(Lista->primeiro);
}

int main()
{

    return 0;
}
