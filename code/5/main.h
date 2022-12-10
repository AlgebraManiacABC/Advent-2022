#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

typedef struct stack
{
    int height;
    char *boxes;

}   * stack;

void printStacks(stack * workspace, int numStacks);
void printTopRow(stack * workspace, int numStacks);

int countAll(stack * workspace, int numStacks);

void move(stack * workspace, int from, int to);
void moveMultiple(stack * workspace, int count, int from, int to);