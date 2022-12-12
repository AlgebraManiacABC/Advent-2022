#include "main.h"

long long int (*operations[])(long long int old)=
{
    m_op_0,
    m_op_1,
    m_op_2,
    m_op_3,
    m_op_4,
    m_op_5,
    m_op_6,
    m_op_7
};

int main(int argc, char *argv[])
{
    FILE *in = fopen("code/11/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    monkey m[8];
    for(int i=0; i<8; i++)
    {
        m[i] = malloc(sizeof(struct monkey));
        m[i]->items = NULL;
        m[i]->div_by = 0;
        m[i]->item_count = 0;
        m[i]->m_false = 0;
        m[i]->m_true = 0;
        m[i]->operation = NULL;
        m[i]->inspections = 0;
    }
    long long int lcm = 1;
    int m_num = 0;
    while(!feof(in))
    {
        fscanf(in,"%*[^\n]%*c");
        fscanf(in,"%*[^:]%*c ");
        char c = ',';
        m[m_num]->item_count = 0;
        while(c == ',')
        {
            m[m_num]->items = realloc(m[m_num]->items,sizeof(long long int)*(1+m[m_num]->item_count));
            fscanf(in,"%lld%c ",&m[m_num]->items[m[m_num]->item_count++],&c);
            //printf("Item count = %d | c = %c (%d)\n",m[m_num]->item_count,c,c);
        }
        fscanf(in,"%*[^\n]%*c");
        m[m_num]->operation = operations[m_num];
        fscanf(in,"%*[^:]%*c%*s%*s%d ",&m[m_num]->div_by);
        lcm *= m[m_num]->div_by;
        fscanf(in,"%*[^:]%*c%*s%*s%*s%d ",&m[m_num]->m_true);
        fscanf(in,"%*[^:]%*c%*s%*s%*s%d ",&m[m_num]->m_false);
        fscanf(in," ");
        m_num++;
    }

    for(int r=0; r<10000; r++)
    {
        for(int i=0; i<8; i++)
        {
            int temp_count = m[i]->item_count;
            for(int j=0; j<temp_count; j++)
            {
                m[i]->items[0] = m[i]->operation(m[i]->items[0]);
                m[i]->items[0] %= lcm;
                //if(m[i]->items[0] < 0)
                //{
                //    printf("Oh no! (%lld)\n",m[i]->items[0]);
                //}
                m[i]->inspections++;
                //m[i]->items[0] /= 3;
                if(m[i]->items[0] % m[i]->div_by == 0)
                {
                    pass_item_from_to(m[i],m[m[i]->m_true]);
                }
                else
                {
                    pass_item_from_to(m[i],m[m[i]->m_false]);
                }
            }
        }
        if(!(r%2000))
        {
            //printf("Round %d:\n",r);
            //get_monkey_business(m);
            //puts("");
        }
    }

    long long int monkey_business = get_monkey_business(m);
    printf("Monkey business: %lld\n",monkey_business);

    for(int i=0; i<8; i++)
    {
        free(m[i]->items);
        free(m[i]);
    }

    fclose(in);
    return EXIT_SUCCESS;
}

long long int m_op_0(long long int old)
{
    return old*13;
}

long long int m_op_1(long long int old)
{
    return old+7;
}

long long int m_op_2(long long int old)
{
    return old+6;
}

long long int m_op_3(long long int old)
{
    return old+5;
}

long long int m_op_4(long long int old)
{
    return old+8;
}

long long int m_op_5(long long int old)
{
    return old*5;
}

long long int m_op_6(long long int old)
{
    return old*old;
}

long long int m_op_7(long long int old)
{
    return old+2;
}

void pass_item_from_to(monkey a, monkey b)
{
    int thrown = a->items[0];
    for(int i=0; i<a->item_count-1; i++)
        a->items[i] = a->items[i+1];
    a->items = realloc(a->items,sizeof(long long int)*(--(a->item_count)));
    b->items = realloc(b->items,sizeof(long long int)*(++(b->item_count)));
    b->items[b->item_count-1] = thrown;
}

long long int get_monkey_business(monkey *m)
{
    long long int most = 0;
    long long int second_most = 0;
    for(int i=0; i<8; i++)
    {
        if(m[i]->inspections > most)
        {
            second_most = most;
            most = m[i]->inspections;
        }
        else if(m[i]->inspections > second_most)
        {
            second_most = m[i]->inspections;
        }
    }
    //printf("\tmost = %lld\n\tsecond most = %lld\n",most,second_most);
    //for(long long int i=0; i<second_most; i++)
    //{
    //    monkey_business += most;
    //    printf("%lld\n",monkey_business);
    //}
    return most * second_most;
}