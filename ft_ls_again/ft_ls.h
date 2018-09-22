#ifndef FT_LS_H
# define FT_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <grp.h>

typedef struct      s_op
{
    int             a:1;
    int             l:1;
    int             r:1;
    int             R:1;
    int             t:1;
}                   t_op;

typedef struct      s_file
{
    char            *name;
    char            permissions[11];
    size_t          links;
    char            *uid;
    char            *gid;
    size_t          size;
    time_t          mod_time;
    char            *formatted_time;
}                   t_file;

typedef struct      s_dir
{
    struct s_file   *file;
    struct s_dir    *next;
    struct s_dir    *prev;
}                   t_dir;


#endif 
