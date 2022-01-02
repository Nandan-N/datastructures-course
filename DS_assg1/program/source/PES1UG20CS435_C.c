// client.c
#include "PES1UG20CS435_H.h"

int main()
{
    int ch;
    node* head = (node*)malloc(sizeof(node));
    head->info = 0;
    head->down = head->right = NULL;

A:

    line();
    printf("MENU");
    line();
    printf("1. Read input.txt\n");
    printf("2. Produce out.txt\n");
    printf("0. Exit");
    line();
    printf("Input your choice : ");
    scanf(" %d", &ch);
    line();

    switch (ch)
    {

    case 1:

        read(&head);
        printf("input.txt evaluated\n");
        delay(1);
        break;

    case 2:

        pathFinder(head);
        printf("Path found and appended to out.txt\n");
        delay(1);
        break;

    case 0:

        exit(0);
        break;

    default:

        printf("\nInvalid entry. Try again ... ");
        delay(1);
        goto A;
        break;
    }

    line();

    goto A;

    return 0;
}