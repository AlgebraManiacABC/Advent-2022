#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}