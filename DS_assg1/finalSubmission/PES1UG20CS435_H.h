// interface.h
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int x;
    int y;
    int info;
    struct node* right;
    struct node* down;

}node;

void line();
void delay(int);
void read(node**);
void pathFinder(node*);
void store(node**, int);
node* pop(node**, int*);
void push(node*, node**, int*);