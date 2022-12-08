#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("f6/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    char four[CHARS]={0};
    for(int i=0; i<CHARS; i++)
    {
        fscanf(in,"%c",four+i);
    }
    int charCount = CHARS;
    while(!feof(in))
    {
        //printf("Testing [%c%c%c%c]...\n",four[0],four[1],four[2],four[3]);
        if(allCharsDifferent(four)) break;
        char temp;
        fscanf(in,"%c",&temp);
        for(int i=0; i<CHARS-1; i++)
        {
            four[i]=four[i+1];
        }
        four[CHARS-1]=temp;
        charCount++;
    }

    printf("charCount = %d\n",charCount);

    return EXIT_SUCCESS;
}

bool allCharsDifferent(const char * four)
{
    for(int i=0; i<CHARS; i++)
    {
        for(int j=i+1; j<CHARS; j++)
        {
            if(four[i]==four[j]) return false;
        }
    }
    return true;
}