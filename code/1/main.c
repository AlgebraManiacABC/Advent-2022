#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("f1/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    long int max_cals = 0;
    long int second_max_cals = 0;
    long int third_max_cals = 0;
    while(!feof(in))
    {
        long int temp_cals = 0;
        while(true)
        {
            long int temp;
            fscanf(in,"%ld",&temp);
            //printf("temp = %ld\n",temp);
            temp_cals += temp;
            char c = fgetc(in);
            //printf("c = %d\n",c);
            c = fgetc(in);
            //printf("c = %d\n",c);
            c = fgetc(in);
            //printf("c = %d\n",c);
            //Forgot about windows line ends :skull:
            if(c == '\n' || c == '\r' || c == EOF)
            {
                //printf("Breaking\n");
                break;
            }
            ungetc(c,in);
        }
        if(temp_cals > max_cals)
        {
            third_max_cals = second_max_cals;
            second_max_cals = max_cals;
            max_cals = temp_cals;
        }
        else if(temp_cals > second_max_cals)
        {
            third_max_cals = second_max_cals;
            second_max_cals = temp_cals;
        }
        else if(temp_cals > third_max_cals)
        {
            third_max_cals = temp_cals;
        }
    }
    printf("Max cals: %ld\n",max_cals);
    printf("2nd max cals: %ld\n",second_max_cals);
    printf("3rd max cals: %ld\n",third_max_cals);
    printf("Total of top three: %ld\n",max_cals + second_max_cals + third_max_cals);

    return EXIT_SUCCESS;
}