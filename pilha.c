#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct
{
    int codigo;
    /* outros componentes */
} TProduto;

typedef struct celula
{
    TProduto item;
    struct celula *prox;
} TCelula;

typedef struct
{
    TCelula *fundo;
    TCelula *topo;
    int tamanho;
} TPilha;

void FPVazia(TPilha *Pilha)
{
    Pilha->topo = (TCelula *) malloc(sizeof(TCelula));
    Pilha->fundo = Pilha->topo;
    Pilha->topo->prox = NULL;
    Pilha->tamanho = 0;
}

int Vazia(TPilha Pilha)
{
    return (Pilha.topo == Pilha.fundo);
}

void Empilhar(TPilha *Pilha, TProduto x)
{
    TCelula* Aux;
    Aux = (TCelula*) malloc(sizeof(TCelula));
    Pilha->topo->item = x;
    Aux->prox = Pilha->topo;
    Pilha->topo = Aux;
    Pilha->tamanho++;
}

void Desempilhar(TPilha *Pilha,TProduto *Item)
{
    TCelula* q;
    if(Vazia(*Pilha))
    {
        printf("Erro: lista vazia !\n");
        return;
    }
    q = Pilha->topo;
    Pilha->topo = q->prox;
    *Item = q->prox->item;
    free(q);
    Pilha->tamanho--;
}

void Imprimir(TPilha *Pilha)
{
    TProduto Item;
    TPilha PilhaAux;
    FPVazia(&PilhaAux);

    while(!Vazia(*Pilha))
    {
        Desempilhar(Pilha, &Item);
        Empilhar(&PilhaAux, Item);
    }

    while(!Vazia(PilhaAux))
    {
        Desempilhar(&PilhaAux, &Item);
      //  ImprimiProduto(Item);
        Empilhar(Pilha, Item);
    }

    free(PilhaAux.topo);
}

void Liberar(TPilha *Pilha)
{
    TProduto Item;

    while(!Vazia(*Pilha))
    {
        Desempilhar(Pilha, &Item);
    }

    free(Pilha->topo);
}

int Tamanho(TPilha Pilha)
{
    return (Pilha.tamanho);
}

int main()
{
    return 0;
}
