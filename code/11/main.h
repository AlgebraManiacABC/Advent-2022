#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

typedef struct monkey
{
    int item_count;
    long long int *items;
    long long int (*operation)(long long int old);
    int div_by;
    int m_true;
    int m_false;
    int inspections;

}   *monkey;

long long int m_op_0(long long int old);
long long int m_op_1(long long int old);
long long int m_op_2(long long int old);
long long int m_op_3(long long int old);
long long int m_op_4(long long int old);
long long int m_op_5(long long int old);
long long int m_op_6(long long int old);
long long int m_op_7(long long int old);

void pass_item_from_to(monkey a, monkey b);

long long int get_monkey_business(monkey *m);