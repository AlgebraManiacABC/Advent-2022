#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("code/10/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    int x = 1;
    int cycles = 0;
    //int sig_sum = 0;
    while(!feof(in))
    {
        cycles++;
        printf("%s",(abs(((cycles-1)%40)-x)<=1)?"█":" ");
        if(!(cycles%40)) puts("");
        //if((cycles-20)%40 == 0)
        //{
        //    //printf("%03d - %03d\n",cycles,cycles*x);
        //    sig_sum += cycles*x;
        //}
        int add = getCommand(in);
        if(add)
        {
            //printf("Addx %d\n",add);
            cycles++;
            printf("%s",(abs(((cycles-1)%40)-x)<=1)?"█":" ");
            if(!(cycles%40)) puts("");
            //if((cycles-20)%40 == 0)
            //{
            //    //printf("%03d - %03d\n",cycles,cycles*x);
            //    sig_sum += cycles*x;
            //}
            x += add;
        }
    }

    //printf("Sum of signal strengths: %d\n",sig_sum);

    fclose(in);
    return EXIT_SUCCESS;
}

int getCommand(FILE *in)
{
    char *buffer = NULL;
    fscanf(in,"%m[^\n]%*c",&buffer);
    if(!strncmp("noop",buffer,4))
        return 0;
    int add;
    sscanf(buffer+strlen("addx "),"%d",&add);
    return add;
}