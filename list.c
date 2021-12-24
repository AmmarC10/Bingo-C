#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void init(List *L)
{
    L->length = 0;
    L->head = NULL;
}
int length(List L)
{
    return L.length;
}
void add(List *L, int c)
{

    NodeType *new;

    new = (NodeType *)malloc(sizeof(NodeType)); //error-check this
    new->data = c;
    new->next = L->head;
    L->head = new;
    L->length++;
}

void print(NodeType *head)
{

    if (head == NULL)
    {
        return;
    }

    print(head->next);
    if (head->data < 10)
    {
        printf("L0%d ", head->data);
    }
    else if (head->data <= 15)
    {
        printf("L%d ", head->data);
    }
    else if (head->data <= 30)
    {
        printf("I%d ", head->data);
    }
    else if (head->data <= 45)
    {
        printf("N%d ", head->data);
    }
    else if (head->data <= 60)
    {
        printf("U%d ", head->data);
    }
    else if (head->data <= 75)
    {
        printf("X%d ", head->data);
    }
    else
    {
        printf("%d ", head->data);
    }
}

int check(List L, int item)
{
    int i;
    NodeType *p;
    p = L.head;
    while (p != NULL)
    {
        if (p->data == item)
        {
            return 1;
        }
        p = p->next;
    }
    return 0;
}
