#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen("f7/in.txt","rb");
    if(!in)
    {
        fprintf(stderr,"File error!\n");
        return EXIT_FAILURE;
    }

    fscanf(in,"%*[^\n]%*c");
    file_pointer working_dir = malloc(sizeof(file));
    *working_dir = init_file("/",0,TYPE_DIRECTORY,NULL);
    file_pointer root = working_dir;
    while(!feof(in))
    {
        char * filename;
        int command_type = read_command(in,&filename);
        if(command_type == COMMAND_CD)
        {
            if(!strncmp("..",filename,2))
            {
                working_dir = working_dir->parent;
            }
            else
            {
                working_dir = get_child_directory_by_name(working_dir,filename);
            }
        }
        else    //  COMMAND_LS
        {
            while(fpeek(in)!='$' && fpeek(in)!=EOF)
            {
                working_dir->children = realloc(working_dir->children,sizeof(file_pointer)*(1+working_dir->num_children));
                working_dir->children[working_dir->num_children++] = read_file(in,working_dir);
            }
        }
        free(filename);
    }

    uint total_size = update_sizes(root);

    printf("Total filesystem size: %u\n",total_size);

    uint dirsize_test_sum = sum_all_dirs_with_max_size_100000(root);

    printf("Sum of the sizes of all directories with max size 100KB: %u\n",dirsize_test_sum);

    uint space_still_needed = REQUIRED_FREE_SPACE - (TOTAL_FILESYSTEM_SIZE - total_size);
    printf("Space still needed for system upgrade: %u\n",space_still_needed);

    file *dirs = NULL;
    int len = total_dir_count(root);
    dirs = malloc(sizeof(file)*len);
    if(len != dirs_into_array(root,dirs,0))
    {
        fprintf(stderr,"Array length mismatch!\n");
        return EXIT_FAILURE;
    }
    qsort(dirs,len,sizeof(file),dirsize_diff);

    file_pointer to_delete = malloc(sizeof(file));
    for(int i=0; i<len; i++)
    {
        *to_delete = dirs[i];
        if(dirs[i].size > space_still_needed)
            break;
    }

    printf("Directory \"%s\" of size %u must be deleted!\n",to_delete->name,to_delete->size);
    free(to_delete);
    free(dirs);

    rm_files(root);

    fclose(in);
    return EXIT_SUCCESS;
}

char fpeek(FILE *in)
{
    char next = fgetc(in);
    ungetc(next,in);
    return next;
}

commandtype read_command(FILE *in, char ** string)
{
    commandtype type;
    char *line = NULL;
    fscanf(in,"%m[^\n]%*c",&line);
    if(line[0] != '$')
    {
        fprintf(stderr,"Not a command!\n");
        free(line);
        exit(ERR_NOT_COMMAND);
    }
    char command[3]={line[2],line[3],'\0'};
    if(!strncmp("cd",command,2))
    {
        type = COMMAND_CD;
    }
    else if(!strncmp("ls",command,2))
    {
        type = COMMAND_LS;
    }
    else
    {
        fprintf(stderr,"Bad command (neither ls nor cd)! [%s]\n",command);
        free(line);
        exit(ERR_BAD_COMMAND);
    }

    if(type == COMMAND_CD && line[4] != ' ')
    {
        fprintf(stderr,"Bad command (expected space)! [%s]\n",command);
        free(line);
        exit(ERR_BAD_COMMAND);
    }

    if(type == COMMAND_CD)
    {
        sscanf(line+4,"%ms",string);
    }
    else    //  COMMAND_LS
    {
        *string = NULL;
    }

    free(line);
    return type;
}

file_pointer read_file(FILE *in, file_pointer working_dir)
{
    file_pointer fp = malloc(sizeof(file));
    char *line = NULL;
    fscanf(in,"%m[^\n]%*c",&line);
    char *type_or_size = NULL;
    char *name = NULL;
    sscanf(line,"%ms %ms",&type_or_size,&name);
    if(!strncmp("dir",type_or_size,3))
    {
        *fp = init_file(name,0,TYPE_DIRECTORY,working_dir);
    }
    else
    {
        int size;
        sscanf(type_or_size,"%d",&size);
        *fp = init_file(name,size,TYPE_FILE,working_dir);
    }
    free(line);
    free(type_or_size);
    free(name);
    return fp;
}

file init_file(const char *name, uint size, filetype type, file_pointer parent)
{
    file f;
    f.name = malloc(sizeof(char) * (1+strlen(name)));
    strcpy(f.name,name);
    f.children = NULL;
    f.num_children = 0;
    f.parent = parent;
    f.size = size;
    f.type = type;
    return f;
}

void rm_files(file_pointer fp)
{
    for(int i=0; i<fp->num_children; i++)
    {
        rm_files(fp->children[i]);
    }
    if(fp->children)
        free(fp->children);
    free(fp->name);
    free(fp);
}

file_pointer get_child_directory_by_name(file_pointer dir, const char *name)
{
    for(int i=0; i<dir->num_children; i++)
    {
        if(!strcmp(dir->children[i]->name,name))
            return dir->children[i];
    }
    return NULL;
}

uint update_sizes(file_pointer dir)
{
    if(dir->type == TYPE_FILE)
        return dir->size;

    uint size = 0;
    for(int i=0; i<dir->num_children; i++)
    {
        dir->children[i]->size = update_sizes(dir->children[i]);
        size += dir->children[i]->size;
    }
    return size;
}

uint sum_all_dirs_with_max_size_100000(file_pointer dir)
{
    if(dir->type == TYPE_FILE)
        return 0;

    uint size = 0;
    for(int i=0; i<dir->num_children; i++)
    {
        size += sum_all_dirs_with_max_size_100000(dir->children[i]);
    }
    if(dir->size <= 100000)
        size += dir->size;
    return size;
}

int total_dir_count(file_pointer dir)
{
    if(dir->type == TYPE_FILE)
        return 0;

    int count = 1;  //  Including self
    for(int i=0; i<dir->num_children; i++)
    {
        count += total_dir_count(dir->children[i]);
    }
    return count;
}

int dirs_into_array(file_pointer root, file *dirs, int start_index)
{
    if(root->type != TYPE_DIRECTORY)
        return 0;

    int dirs_added = 0;
    dirs[start_index++] = *root;
    dirs_added++;
    for(int i=0; i<root->num_children; i++)
    {
        int temp = dirs_into_array(root->children[i],dirs,start_index);
        dirs_added += temp;
        start_index += temp;
    }
    return dirs_added;
}

int dirsize_diff(const void *dir1, const void *dir2)
{
    return ((file_pointer)dir1)->size - ((file_pointer)dir2)->size;
}