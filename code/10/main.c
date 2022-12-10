#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("code/10/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    fclose(in);
    return EXIT_SUCCESS;
}