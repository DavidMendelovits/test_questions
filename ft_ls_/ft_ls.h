#ifndef FT_LS_H
# define FT_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <strings.h>
#include <string.h>

typedef struct      s_opt
{
    int             l:1;
    int             a:1;
    int             t:1;
    int             r:1;
    int             R:1;
}                   t_opt;

typedef struct      s_file
{
    char            *name;
    char            *permissions;
    time_t          time;
    size_t          block_size;
}                   t_file;

typedef struct      s_dir
{
    struct s_file   *file;
    struct s_dir    *next;
    struct s_dir    *prev;
}                   t_dir;

typedef struct      s_list
{
    char            *path;
    struct s_list   *next;
    struct s_list   *prev;
}                   t_list;

int             ft_ls(char *path, t_opt *o);
#endif
