// client.c
#include "PES1UG20CS435_H.h"

int main()
{
    int ch;
    int vertices;
    int dfs_result = 0;
    int bfs_result = 0;
    int start_point, end_point;

    FILE* fp = fopen("input.txt", "rear");

    if (fp == NULL)
    {
        printf("\nError encountered in opening file.");
        exit(0);
    }

A:

    line();
    printf("MENU");
    line();
    printf("1. Read input.txt\n");
    printf("2. Display adjacency list\n");
    printf("3. Produce outdfs.txt & outbfs.txt\n");
    printf("0. Exit");
    line();
    printf("Input your choice : ");
    scanf(" %d", &ch);
    line();

    switch (ch)
    {

    case 1:

        printf("\nReading from input file ...\n");
        coord start, end;
        getcord(&start, fp);
        getcord(&end, fp);

        printf("\nStart: (%d, %d)\nEnd: (%d, %d)\n", start.x, start.y, end.x, end.y);

        vertices = num_v(fp);
        vertex_node* adj_list = (vertex_node*)malloc((vertices + 1) * sizeof(vertex_node));

        read_map(fp, adj_list);

        printf("input.txt evaluated\n");
        delay(1);
        break;

    case 2:

        printf("\nAdjacency List :\n");
        display_adj_list(adj_list, vertices);
        delay(1);
        break;

    case 3:

        printf("\nPath :\n");
        int* d_path = (int*)calloc(vertices, sizeof(int));
        int* b_path = (int*)calloc(vertices, sizeof(int));

        start_point = find_vertex(adj_list, &start, vertices);
        end_point = find_vertex(adj_list, &end, vertices);

        find_path(adj_list, start_point, end_point, vertices, &dfs_result, &bfs_result, d_path, b_path);
        store_path(adj_list, start_point, end_point, vertices, dfs_result, bfs_result, d_path, b_path);

        free(adj_list);
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