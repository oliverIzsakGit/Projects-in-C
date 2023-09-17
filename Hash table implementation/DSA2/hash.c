#include<stdio.h>
#include<stdlib.h>

//the implementation was taken from this website : https://www.log2base2.com/algorithms/searching/open-hashing.html

//
#define size 10000

// added method by me to be able to chance size of hash table.

struct Hnode
{
    int data;
    struct Hnode* next;
};

struct Hnode* chain[size];

void init()
{

    int i;
    for (i = 0; i < size; i++)
        chain[i] = NULL;
}

void insert(int value)
{
    //create a newnode with value
    struct Hnode* newNode = malloc(sizeof(struct Hnode));
    newNode->data = value;
    newNode->next = NULL;

    //calculate hash key
    int key = value % size;

    //check if chain[key] is empty
    if (chain[key] == NULL)
        chain[key] = newNode;
    //collision
    else
    {
        //add the node at the end of chain[key].
        struct Hnode* temp = chain[key];
        while (temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

/*
 * return 1, search found
 * return 0, Otherwise
 */
int search(int value)
{
    int key = value % size;
    struct Hnode* temp = chain[key];
    while (temp)
    {
        if (temp->data == value)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int delete(int value)
{
    int key = value % size;
    struct Hnode* temp = chain[key];
    while (temp->next)
    {
        if (temp->next->data == value) {
            temp->next = temp->next->next;
            return 1;
        }


        temp = temp->next;
    }
    return 0;
}







void print()
{
    int i;

    for (i = 0; i < size; i++)
    {
        struct Hnode* temp = chain[i];
        printf("chain[%d]-->", i);
        while (temp)
        {
            printf("%d -->", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}



