#include <stdlib.h>
#include <stdio.h>

#define MAX 10

typedef struct
{
    int codigo;
    /*
       outros componentes
       de produto
    */
} TProduto;

typedef struct celula
{
    TProduto item;
    struct celula *prox;
} TCelula;

typedef struct
{
    TCelula *primeiro;
    TCelula *ultimo;
    int tamanho;
} TLista;

void FLVazia(TLista *Lista)
{
    Lista->primeiro = (TCelula *) malloc(sizeof(TCelula));
    Lista->ultimo = Lista->primeiro;
    Lista->primeiro->prox = NULL;
    Lista->tamanho = 0;
}

int Vazia(TLista Lista)
{
    return (Lista.primeiro == Lista.ultimo);
}

void Inserir(TProduto x, TLista *Lista)
{
    Lista->ultimo->prox = (TCelula *) malloc(sizeof(TCelula));
    Lista->ultimo = Lista->ultimo->prox;
    Lista->ultimo->item = x;
    Lista->ultimo->prox = NULL;
    Lista->tamanho++;
}

TCelula* Pesquisar(TLista Lista, TProduto Item)
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

void Excluir(TLista *Lista, TProduto *Item)
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

void Imprimir(TLista Lista)
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

void Alterar(TLista *Lista, TProduto *Item, TProduto item)
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

void Liberar(TLista *Lista)
{
    while(Vazia(*Lista) != 1)
    {
        Excluir(Lista, &Lista->primeiro->prox->item);
    }

    free(Lista->primeiro);
}

int main()
{
    TLista lista;
    TProduto item;

    FLVazia(&lista);
    printf("\n\n%d\n\n", Vazia(lista));

    item.codigo = 1;
    Inserir(item, &lista);

    item.codigo = 2;
    Inserir(item, &lista);

    item.codigo = 3;
    Inserir(item, &lista);

    Imprimir(lista);

    TProduto item2;

    item2.codigo = 4;
    Alterar(&lista, &item, item2);

    Imprimir(lista);

    printf("\n\n");

    Liberar(&lista);
    Imprimir(lista);

    printf("\n\n%d", Vazia(lista));

    return 0;
}
