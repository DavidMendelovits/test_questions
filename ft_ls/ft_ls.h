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
    mode_t          mode; // file type / mode
    char            *permissions;
    nlink_t         links;
    uid_t           *uid;
    gid_t           *gid;
    size_t          size;
    struct timespec mod_time;
}                   t_file;

typedef struct      s_dir
{
    struct s_file   *file;
    struct s_dir    *next;
    struct s_dir    *prev;
}                   t_dir;


#endif 
