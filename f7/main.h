#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

typedef unsigned int uint;

#define TOTAL_FILESYSTEM_SIZE 70000000  //  70MB
#define REQUIRED_FREE_SPACE 30000000    //  30MB

#define ERR_BAD_COMMAND -2
#define ERR_NOT_COMMAND -1

typedef bool filetype;
#define TYPE_DIRECTORY true
#define TYPE_FILE false

typedef bool commandtype;
#define COMMAND_CD true
#define COMMAND_LS false

typedef struct file * file_pointer;

typedef struct file
{
    char *name;
    filetype type;
    uint size;
    file_pointer parent;
    file_pointer * children;
    int num_children;

}   file;

char fpeek(FILE *in);

/**
 * Reads a line of text which is assumed to be a command.
 * Returns the command type (ls or cd),
 * and also sets "string" to a dynamically allocated string
 * representing the rest of the line after the command (including the first space).
 * 
 */
commandtype read_command(FILE *in, char ** string);

file_pointer read_file(FILE *in, file_pointer working_dir);

file init_file(const char *name, uint size, filetype type, file_pointer parent);
void rm_files(file_pointer fp);

file_pointer get_child_directory_by_name(file_pointer dir,const char *name);

uint update_sizes(file_pointer dir);

uint sum_all_dirs_with_max_size_100000(file_pointer dir);

int total_dir_count(file_pointer root);

int dirs_into_array(file_pointer root, file *dirs, int start_index);

int dirsize_diff(const void *dir1, const void *dir2);