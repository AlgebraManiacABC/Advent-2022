#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("f8/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    int **trees = NULL;
    int rows = 0;
    int cols = 0;
    while(!feof(in))
    {
        char * buffer;
        fscanf(in,"%ms",&buffer);
        rows++;
        cols = strlen(buffer);
        trees = realloc(trees,sizeof(int *)*rows);
        trees[rows-1] = malloc(sizeof(int)*cols);
        for(int i=0; i<cols; i++)
        {
            trees[rows-1][i] = buffer[i] - '0';
        }
        free(buffer);
    }

    int visible = 0;
    int max_scenic_score = 0;
    for(int r=0; r<rows; r++)
    {
        int row_visible = 0;
        int temp_scenic_score;
        for(int c=0; c<cols; c++)
        {
            if(isVisible(r,c,trees,rows,cols))
                row_visible++;
            temp_scenic_score = scenicScore(r,c,trees,rows,cols);
            if(temp_scenic_score > max_scenic_score)
                max_scenic_score = temp_scenic_score;
        }
        printf("%03d: ",r);
        for(int i=0; i<row_visible; i++)
        {
            printf("*");
        }
        printf("\n");
        visible += row_visible;
    }

    printf("All visible trees: %d\n",visible);
    printf("Max scenic score: %d\n",max_scenic_score);

    fclose(in);
    return EXIT_SUCCESS;
}

bool isVisibleNorth(int r, int c, int **trees, int rows)
{
    for(int i=r-1; i>=0; i--)
    {
        if(trees[i][c] >= trees[r][c])
            return false;
    }
    return true;
}

bool isVisibleSouth(int r, int c, int **trees, int rows)
{
    for(int i=r+1; i<rows; i++)
    {
        if(trees[i][c] >= trees[r][c])
            return false;
    }
    return true;
}

bool isVisibleEast(int r, int c, int **trees, int cols)
{
    for(int i=c+1; i<cols; i++)
    {
        if(trees[r][i] >= trees[r][c])
            return false;
    }
    return true;
}

bool isVisibleWest(int r, int c, int **trees, int cols)
{
    for(int i=c-1; i>=0; i--)
    {
        if(trees[r][i] >= trees[r][c])
            return false;
    }
    return true;
}


bool isVisible(int r, int c, int **trees, int rows, int cols)
{
    if(isVisibleEast(r,c,trees,cols) || isVisibleWest(r,c,trees,cols)
        || isVisibleNorth(r,c,trees,rows) || isVisibleSouth(r,c,trees,rows))
        return true;
    return false;
}

int viewingDistanceNorth(int r, int c, int **trees, int rows)
{
    int dist = 0;
    for(int i=r-1; i>=0; i--)
    {
        dist++;
        if(trees[i][c] >= trees[r][c])
            break;
    }
    return dist;
}

int viewingDistanceSouth(int r, int c, int **trees, int rows)
{
    int dist = 0;
    for(int i=r+1; i<rows; i++)
    {
        dist++;
        if(trees[i][c] >= trees[r][c])
            break;
    }
    return dist;
}

int viewingDistanceWest(int r, int c, int **trees, int cols)
{
    int dist = 0;
    for(int i=c-1; i>=0; i--)
    {
        dist++;
        if(trees[r][i] >= trees[r][c])
            break;
    }
    return dist;
}

int viewingDistanceEast(int r, int c, int **trees, int cols)
{
    int dist = 0;
    for(int i=c+1; i<cols; i++)
    {
        dist++;
        if(trees[r][i] >= trees[r][c])
            break;
    }
    return dist;
}

int scenicScore(int r, int c, int **trees, int rows, int cols)
{
    int score = viewingDistanceNorth(r,c,trees,rows);
    score *= viewingDistanceSouth(r,c,trees,rows);
    score *= viewingDistanceEast(r,c,trees,cols);
    score *= viewingDistanceWest(r,c,trees,cols);
    return score;
}