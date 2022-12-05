#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("f4/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    int subsets = 0;
    int overlaps = 0;
    while(!feof(in))
    {
        int a1,a2,b1,b2;
        fscanf(in,"%d-%d,%d-%d",&a1,&a2,&b1,&b2);
        if(a1 <= b1 && a2 >= b2)
            subsets++;
        else if(b1 <= a1 && b2 >= a2)
            subsets++;
        
        if(a1 <= b1 && a2 >= b1) overlaps++;
        else if(b1 <= a1 && b2 >= a1) overlaps++;

    }

    printf("Subsets: %d\n",subsets);
    printf("Overlaps: %d\n",overlaps);

    return EXIT_SUCCESS;
}