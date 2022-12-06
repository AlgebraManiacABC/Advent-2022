#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("f5/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    stack *workspace = NULL;
    int width = 0;
    while(true)
    {
        char *line = NULL;
        fscanf(in,"%m[^\n]",&line);
        fgetc(in);
        if(!line)
        {
            fprintf(stderr,"Memory fail!\n");
            return EXIT_FAILURE;
        }
        if(isdigit(line[1]))
        {
            free(line);
            break;
        }
        width = (strlen(line)+1)/4;
        if(!workspace)
        {
            workspace = malloc(sizeof(stack) * width);
            for(int i=0; i<width; i++)
            {
                workspace[i] = malloc(sizeof(struct stack));
                workspace[i]->boxes = NULL;
                workspace[i]->height = 0;
            }
        }
        for(int i=0; i<width; i++)
        {
            workspace[i]->boxes = realloc(workspace[i]->boxes,sizeof(char)*(workspace[i]->height+1));
            workspace[i]->boxes[workspace[i]->height]=line[(i*4)+1];
            if(line[(i*4)+1] != ' ')
                workspace[i]->height++;
        }
        free(line);
    }

    printStacks(workspace,width);
    //printf("Count = %d\n",countAll(workspace,width));
    puts("");

    int allCount = countAll(workspace,width);
    fscanf(in,"%*[^\n]");
    while(!feof(in))
    {
        int count,from,to;
        //  "Move x from y to z"
        fscanf(in,"%*s %d %*s %d %*s %d",&count,&from,&to);
        for(int i=0; i<count; i++)
        {
            move(workspace,from,to);
            //printStacks(workspace,width);
            //printf("Count = %d\n",countAll(workspace,width));
            if(allCount != countAll(workspace,width))
            {
                printf("WRONG!\n");
            }
        }
    }
    
    printStacks(workspace,width);
    //printf("Count = %d\n",countAll(workspace,width));
    puts("");
    printTopRow(workspace,width);

    for(int i=0; i<width; i++)
    {
        free(workspace[i]->boxes);
        free(workspace[i]);
    }
    free(workspace);

    return EXIT_SUCCESS;
}

void printStacks(stack * workspace, int numStacks)
{
    for(int i=0; i<numStacks; i++)
    {
        printf("%2d: ",i+1);
        for(int j=0; j<workspace[i]->height; j++)
        {
            printf("[%c]%s",workspace[i]->boxes[j],(j+1<workspace[i]->height?" ":""));
        }
        printf("\n");
    }
}

void printTopRow(stack * workspace, int numStacks)
{
    printf("Top of each row: ");
    for(int i=0; i<numStacks; i++)
    {
        printf("%c",workspace[i]->boxes[workspace[i]->height-1]);
    }
    printf("\n");
}

int countAll(stack * workspace, int numStacks)
{
    int count = 0;
    for(int i=0; i<numStacks; i++)
    {
        count += workspace[i]->height;
    }
    return count;
}

void move(stack * workspace, int from, int to)
{
    from--;
    to--;
    if(workspace[from]->height==0)
    {
        printf("WRONG!\n");
        return;
    }
    workspace[to]->boxes = realloc(workspace[to]->boxes,sizeof(char)*++(workspace[to]->height));
    workspace[to]->boxes[workspace[to]->height-1] = workspace[from]->boxes[workspace[from]->height-1];
    workspace[from]->boxes = realloc(workspace[from]->boxes,sizeof(char)*--(workspace[from]->height));
}