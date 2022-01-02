// server.c
#include "PES1UG20CS435_H.h"

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void line()
{
    printf("\n_______________________________________________________________________________________________________\n");
}

void push(node* temp, node** stack, int* top)
{
    ++(*top);
    stack[*top] = temp;
}

node* pop(node** stack, int* top)
{
    node* temp;
    temp = stack[*top];
    --(*top);
    return temp;
}

void read(node** head)
{
    FILE* fp = fopen("input.txt", "r");
    if (!fp) return;

    char line[1024];

    int row = 0;
    int col = 0;
    int prevRow = -1;

    while (fgets(line, 1024, fp))
    {
        col = 0;
        row++;
        if (row == 1 || row == 2) continue; // skipping line 1 & 2
        prevRow++;

        // creating the head node for each row and initializing them to NULL
        node* rows = (node*)malloc(sizeof(node));
        rows->down = rows->right = NULL;
        rows->info = prevRow;

        node* cur = *head;
        while (cur->down != NULL) cur = cur->down;

        // attaching the the rows one below the other 
        cur->down = rows;
        cur = cur->down;

        char* value = strtok(line, " ");
        while (value && col < 10)
        {
            node* cur_col = *head;

            // initializing column head
            if (prevRow == 0)
            {
                node* cols = (node*)malloc(sizeof(node));
                cols->right = cols->down = NULL;
                cols->info = col;
                while (cur_col->right != NULL) cur_col = cur_col->right;
                cur_col->right = cols;
                cur_col = cols;
            }
            else
            {
                // traversing to the end of the column (as head would already be initialized at this point)
                cur_col = cur_col->right;
                while (cur_col->info != col) cur_col = cur_col->right;
            }

            node* temp = (node*)malloc(sizeof(node));

            if (atoi(value) == 0)
            {
                //storing coordinates in the node structure
                temp->x = prevRow;
                temp->y = col;

                temp->info = atoi(value);
                temp->down = temp->right = NULL;

                cur->right = temp;
                cur = cur->right;
            }

            if (temp->x == prevRow)
            {
                while (cur_col->down != NULL) cur_col = cur_col->down;
                cur_col->down = temp;
            }

            // obtaining the next value from the file
            value = strtok(NULL, " ");
            col++;
        }
    }
    fclose(fp);
}

void pathFinder(node* head)
{
    node* start = NULL;
    int start_x;
    int start_y;
    int end_x;
    int end_y;

    FILE* fp = fopen("input.txt", "r");
    if (!fp) return;
    else
    {
        char line[1024];
        int row = 0;
        while (fgets(line, 1024, fp))
        {
            char* value = strtok(line, " ");
            row++;
            if (row == 1)
            {
                start_x = atoi(value);
                value = strtok(NULL, " ");
                start_y = atoi(value);
            }
            else if (row == 2)
            {
                end_x = atoi(value);
                value = strtok(NULL, " ");
                end_y = atoi(value);
            }
            else break;
        }
    }

    fclose(fp);

    node* finish = NULL;
    node* temp = NULL;
    node* row = head->down;
    node* col = head->right;

    while (row->info != end_x) row = row->down;
    temp = row->right;
    while (temp->y != end_y) temp = temp->right;
    finish = temp;

    row = head->down;
    col = head->right;

    while (row->info != start_x) row = row->down;
    temp = row->right;
    while (temp->y != start_y) temp = temp->right;

    start = temp;
    int top = -1;
    int top1 = -1;

    node* path[100]; // stores path
    node* stk[100]; // stores intersections
    node* cur = start;

    push(cur, path, &top1);

    while (cur != finish)
    {
        // checking for node to the right
        if (cur->right != NULL && (cur->right->y == ((cur->y) + 1)))
        {
            // node present at right & down
            if (cur->down != NULL && cur->down->x == ((cur->x) + 1)) push(cur, stk, &top);
            // move right
            cur = cur->right;
            push(cur, path, &top1);
        }
        else if (cur->right == NULL) // no path to the right
        {
            // move down
            if (cur->down != NULL && cur->down->x == ((cur->x) + 1))
            {
                cur = cur->down;
                push(cur, path, &top1);
            }

            else
            {
                // no path to the right, retrace
                if (top >= 0)
                {
                    cur = pop(stk, &top);
                    // pop till top record of stk is encountered
                    while ((temp = pop(path, &top1)) != cur);

                    // move down
                    push(cur, path, &top1);
                    cur = cur->down;
                    push(cur, path, &top1);
                }
                else return;
            }
        }
        else
        {
            // no path to the right
            if (cur->down != NULL && cur->down->x == ((cur->x) + 1))
            {
                cur = cur->down;
                push(cur, path, &top1);
            }
            else
            {
                // no path at all, move back another intersection
                if (top >= 0)
                {
                    cur = pop(stk, &top);
                    while ((temp = pop(path, &top1)) != cur);
                    push(cur, path, &top1);
                    cur = cur->down;
                    push(cur, path, &top1);
                }
                else
                {
                    return;
                }
            }
        }
    }

    store(path, top1);
}
void store(node** path, int top)
{
    FILE* fp = fopen("out.txt", "w");
    if (!fp) return;

    if (top == -1) fprintf(fp, "%d", -1);
    else for (int i = 0; i <= top; i++) fprintf(fp, "%d %d\n", path[i]->x, path[i]->y);

    fclose(fp);
}