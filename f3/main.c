#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("f3/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    //int sum = 0;
    int sum3 = 0;
    /*
    while(!feof(in))
    {
        char *buffer = NULL;
        fscanf(in,"%ms",&buffer);
        if(!buffer)
        {
            fprintf(stderr,"Grievous error!\n");
            return EXIT_FAILURE;
        }
        int len = strlen(buffer);
        char *firstHalf = malloc(sizeof(char)*((len/2)+1));
        char *secondHalf = malloc(sizeof(char)*((len/2)+1));
        if(!firstHalf || !secondHalf)
        {
            fprintf(stderr,"Memory error!\n");
            free(buffer);
            return EXIT_FAILURE;
        }
        strncpy(firstHalf,buffer,(len/2)+1);
        strncpy(secondHalf,buffer+(len/2),(len/2)+1);
        sum += sharedPriority(firstHalf,secondHalf);
        free(buffer);
        free(firstHalf);
        free(secondHalf);
    }
    */
    while(!feof(in))
    {
        char *buffer1 = NULL, *buffer2 = NULL, *buffer3 = NULL;
        fscanf(in,"%ms %ms %ms",&buffer1,&buffer2,&buffer3);
        if(!buffer1 || !buffer2 || !buffer3)
        {
            fprintf(stderr,"Memory error!\n");
            return EXIT_FAILURE;
        }
        sum3 += thriceSharedPriority(buffer1,buffer2,buffer3);
    }

    //printf("Sum of shared priorities of both compartments: %d\n",sum);
    printf("Sum of shared priorities of elf groups: %d\n", sum3);

    return EXIT_SUCCESS;
}

int sharedPriority(char *a, char *b)
{
    int priority = 0;
    int len = strlen(a);

    for(int i=0; i<len; i++)
    {
        if(charInString(a[i],b))
        {
            priority = priorityOf(a[i]);
            break;
        }
    }
    if(priority == 0)
    {
        printf("Your functions need fixed!\n");
    }

    return priority;
}

int thriceSharedPriority(char *a, char *b, char *c)
{
    int priority = 0;
    int len_a = strlen(a);

    for(int i=0; i<len_a; i++)
    {
        if(charInString(a[i],b) && charInString(a[i],c))
        {
            priority = priorityOf(a[i]);
            break;
        }
    }
    return priority;
}

bool charInString(char c, char *s)
{
    int len = strlen(s);
    for(int i=0; i<len; i++)
    {
        if(s[i] == c) return true;
    }
    return false;
}

int priorityOf(char c)
{
    if(c >= 'A' && c <= 'Z')
        return (c - 'A' + 27);
    else if(c >= 'a' && c <= 'z')
        return (c - 'a' + 1);
    
    fprintf(stderr,"Unexpected character! (%c=%02x)\n",c,c);
    return -1;
}