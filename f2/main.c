#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("f2/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }
    char *rps[]=
    {
        "Rock",
        "Paper",
        "Scissors"
    };

    char opponent;
    char you;
    int score = 0;
    /*
    while(!feof(in))
    {
        fscanf(in,"%c %c ",&opponent,&you);
        printf("You: %s | Them: %s | Outcome:",rps[(int)you-'X'],rps[(int)opponent-'A']);
        score += you - 'X' + 1;
        if(you == (opponent - 'A' + 'X'))
        {
            score += 3;
            printf(" Draw.\n");
        }
        else if((you == Y_ROCK && opponent == O_SCISSORS) ||
                (you == Y_PAPER && opponent == O_ROCK) ||
                (you == Y_SCISSORS && opponent == O_PAPER))
        {
            score += 6;
            printf(" Win!\n");
        }
        else
        {
            printf(" Lose.\n");
        }
    }
    */
    char result;
    while(!feof(in))
    {
        fscanf(in,"%c %c ",&opponent,&result);
        switch(result)
        {
            case WIN:
                score += 6;
                switch(opponent)
                {
                    case O_ROCK:
                        score += S_PAPER;
                        break;
                    case O_PAPER:
                        score += S_SCISSORS;
                        break;
                    case O_SCISSORS:
                        score += S_ROCK;
                        break;
                }
                break;
            case DRAW:
                switch(opponent)
                {
                    case O_ROCK:
                        score += S_ROCK;
                        break;
                    case O_PAPER:
                        score += S_PAPER;
                        break;
                    case O_SCISSORS:
                        score += S_SCISSORS;
                        break;
                }
                score += 3;
                break;
            case LOSE:
                switch(opponent)
                {
                    case O_ROCK:
                        score += S_SCISSORS;
                        break;
                    case O_PAPER:
                        score += S_ROCK;
                        break;
                    case O_SCISSORS:
                        score += S_PAPER;
                        break;
                }
                break;
        }
    }
    printf("Score = %d\n",score);

    return EXIT_SUCCESS;
}