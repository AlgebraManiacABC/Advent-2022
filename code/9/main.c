#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("f9/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    rope_segment rope[ROPE_SEGMENT_COUNT];
    for(int i=0; i<ROPE_SEGMENT_COUNT; i++)
    {
        rope[i] = malloc(sizeof(coord));
        if(!rope[i]) return EXIT_FAILURE;
        rope[i]->x = 0;
        rope[i]->y = 0;
        rope[i]->next = init_coords();
        if(!rope[i]->next) return EXIT_FAILURE;
        if(new_coord(rope[i]->next,0,0) < 0) return EXIT_FAILURE;
    }
    while(!feof(in))
    {
        char dir;
        int dist;
        fscanf(in," %c %d ",&dir,&dist);
        for(int i=0; i<dist; i++)
        {
            if(update_rope_head(rope[0],dir)<0) return EXIT_FAILURE;
            for(int j=1; j<ROPE_SEGMENT_COUNT; j++)
                if(follow_lead(rope[j-1],rope[j])<0) return EXIT_FAILURE;
        }
    }

    printf("Tail travelled through %d unique spaces!\n",count_coords(rope[ROPE_SEGMENT_COUNT-1]->next));

    fclose(in);
    return EXIT_SUCCESS;
}

int update_rope(rope_segment head, rope_segment tail, char dir)
{
    switch(dir)
    {
        case 'U':
            head->y++;
            break;
        case 'D':
            head->y--;
            break;
        case 'R':
            head->x++;
            break;
        case 'L':
            head->x--;
            break;
        default:
            return ERR_DIR;
    }
    int err = new_coord(head->next,head->x,head->y);
    if(err < 0)
        return err;
    if( abs(head->x - tail->x)<=1 && abs(head->y - tail->y)<=1 )
        return EXIT_SUCCESS;

    if(head->x == tail->x)
    {
        if(head->y - tail->y > 0)
            tail->y++;
        else
            tail->y--;
    }
    else if(head->y == tail->y)
    {
        if(head->x - tail->x > 0)
            tail->x++;
        else
            tail->x--;
    }
    else
    {
        switch(dir)
        {
            case 'U':
                tail->x = head->x;
                tail->y++;
                break;
            case 'D':
                tail->x = head->x;
                tail->y--;
                break;
            case 'R':
                tail->y = head->y;
                tail->x++;
                break;
            case 'L':
                tail->y = head->y;
                tail->x--;
                break;
            default:
                return ERR_DIR;
        }
    }
    err = new_coord(tail->next,tail->x,tail->y);
    if(err < 0)
        return err;
    return EXIT_SUCCESS;
}

int update_rope_head(rope_segment head, char dir)
{
    switch(dir)
    {
        case 'U':
            head->y++;
            break;
        case 'D':
            head->y--;
            break;
        case 'R':
            head->x++;
            break;
        case 'L':
            head->x--;
            break;
        default:
            return ERR_DIR;
    }
    head->dir_just_moved = dir;
    int err = new_coord(head->next,head->x,head->y);
    if(err < 0)
        return err;
    return EXIT_SUCCESS;
}

int follow_lead(rope_segment leader, rope_segment follower)
{
    if( abs(leader->x - follower->x)<=1 && abs(leader->y - follower->y)<=1 )
    {
        follower->dir_just_moved = ' ';
        return EXIT_SUCCESS;
    }

    if(leader->x == follower->x)
    {
        if(leader->y > follower->y)
        {
            follower->y++;
            follower->dir_just_moved = 'U';
        }
        else
        {
            follower->y--;
            follower->dir_just_moved = 'D';
        }
    }
    else if(leader->y == follower->y)
    {
        if(leader->x > follower->x)
        {
            follower->x++;
            follower->dir_just_moved = 'R';
        }
        else
        {
            follower->x--;
            follower->dir_just_moved = 'L';
        }
    }
    else
    {
        switch(leader->dir_just_moved)
        {
            case 'U':
                if(follower->x > leader->x)
                    follower->dir_just_moved = '`';
                else
                    follower->dir_just_moved = '\'';
                follower->x = leader->x;
                follower->y++;
                break;
            case 'D':
                if(follower->x > leader->x)
                    follower->dir_just_moved = ',';
                else
                    follower->dir_just_moved = '.';
                follower->x = leader->x;
                follower->y--;
                break;
            case 'R':
                if(follower->y > leader->y)
                    follower->dir_just_moved = '.';
                else
                    follower->dir_just_moved = '\'';
                follower->y = leader->y;
                follower->x++;
                break;
            case 'L':
                if(follower->y > leader->y)
                    follower->dir_just_moved = ',';
                else
                    follower->dir_just_moved = '`';
                follower->y = leader->y;
                follower->x--;
                break;
            case '`':   //  Up left
                follower->y++;
                follower->x--;
                follower->dir_just_moved = '`';
                break;
            case '\'':  //  Up right
                follower->y++;
                follower->x++;
                follower->dir_just_moved = '\'';
                break;
            case ',':   //  Down left
                follower->y--;
                follower->x--;
                follower->dir_just_moved = ',';
                break;
            case '.':   //  Down right
                follower->y--;
                follower->x++;
                follower->dir_just_moved = '.';
                break;
            default:
                return ERR_DIR;
        }
    }
    int err = new_coord(follower->next,follower->x,follower->y);
    if(err < 0)
        return err;
    return EXIT_SUCCESS;
}

coordinate_list init_coords()
{
    coordinate_list c = malloc(sizeof(coord));
    if(!c) return NULL;
    c->x = 0;
    c->y = 0;
    c->next = NULL;
    c->dir_just_moved = '\0';
    return c;
}

int new_coord(coordinate_list coords, int x, int y)
{
    while(coords->next)
    {
        if(coords->next->x == x && coords->next->y == y) return 1;
        coords = coords->next;
    }
    coordinate_list new = malloc(sizeof(coord));
    if(!new) return ERR_MALLOC;
    new->x = x;
    new->y = y;
    new->next = NULL;
    coords->next = new;
    return EXIT_SUCCESS;
}

int count_coords(coordinate_list coords)
{
    int count = 0;
    while(coords->next)
    {
        coords = coords->next;
        count++;
    }
    return count;
}