#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define ROPE_SEGMENT_COUNT 10

#define ERR_MALLOC (-1)
#define DUPE_COORD (1)
#define ERR_DIR (-2)

typedef struct coord * coordinate_list;

typedef struct coord
{
    int x;
    int y;
    coordinate_list next;
    char dir_just_moved;

}   coord;

typedef coord * rope_segment;

int update_rope(rope_segment head, rope_segment tail, char dir);
int update_rope_head(rope_segment head, char dir);
int follow_lead(rope_segment leader, rope_segment follower);

coordinate_list init_coords();

//  Places the given (x,y) ordered pair at the end of the coordinate list.
//  Does not add duplicate pairs.
int new_coord(coordinate_list coords, int x, int y);

int count_coords(coordinate_list coords);