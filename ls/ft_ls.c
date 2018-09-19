#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>

#define INVALID_FILE "Error -> invalid filename\n"

typedef struct          s_files
{
    char                *name;
    struct s_files      *next;
}                       t_files;

int             find_dir(DIR **_dir, char *filename)
{
    *_dir = opendir(filename);
    if (!(*_dir))
    {
        write(2, INVALID_FILE, strlen(INVALID_FILE));
        return (0);
    }
    return (1);
}

void            read_directory(DIR *dir, t_files *files)
{
    struct dirent       *entry;

    while ((entry = readdir(dir)))
    {
  //      if (entry->d_name[0] = '.')
    //    {
      //      continue ;
       // }
        printf("%s\n", entry->d_name);
    //    files->name = strdup(entry->d_name);
    //    printf("files-name = %s\n", files->name);
     //   files = files->next;
    }
}

int             ft_ls(char *path)
{
    DIR         *_dir;
    t_files     files;

    if (!find_dir(&_dir, path))
    {
        return (0);
    }
    read_directory(_dir, &files);
    closedir(_dir);
    return (1);
}

int             main(int argc, char **argv)
{
    int         i;

    if (argc == 1)
    {
        ft_ls(".");
    }
    //put in option handling here
    if (argc > 1)
    {
        i = 1;
        while (i < argc)
        {
            if (!ft_ls(argv[i]))
            {
                write(2, "error\n", 6);
            }
            i += 1;
        }
    }
    return (0);
}
