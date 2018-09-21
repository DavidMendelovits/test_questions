#include "ft_ls.h"

void                init_op_struct(t_op *o)
{

    printf("->%s\n", __func__);
    o->a = 0;
    o->l = 0;
    o->r = 0;
    o->R = 0;
    o->t = 0;
}

void                write_option(t_op *o, char c)
{
    printf("->%s\n", __func__);
    if (c == 'l')
    {
        o->l = 1;
    }
    else if (c == 'a')
    {
        o->a = 1;
    }
    else if (c == 'r')
    {
        o->r = 1;
    }
    else if (c == 'R')
    {
        o->R = 1;
    }
    else if (c == 't')
    {
        o->t = 1;
    }
}

int                 is_valid_opt(char c)
{
    if (c == 'l' || c == 'a' || c == 'r' || c =='R' || c == 't')
    {
        return (1);
    }
    return (0);
}

char                **split_input(t_op *o, int argc, char **argv)
{
    printf("->%s\n", __func__);
    int         i;
    int         j;
    char        **paths;
    int         path_count;

    i = 1;
    path_count = 0;
    while (i < argc)
    {
        if (argv[i][0] == '-')
        {
            j = 1;
            while (argv[i][j])
            {
                if (!is_valid_opt(argv[i][j]))
                {
                    printf("ls: invalid option -- '%c'\n", argv[i][j]);
                    return (NULL);
                }
                else
                {
                    write_option(o, argv[i][j]);
                }
                j += 1;
            }
        }
        else
        {
            path_count += 1;
        }
        i += 1;
    }
    printf("\nhuh\n");
    paths = malloc(sizeof(*paths) * (path_count + 1));
    if (!path_count)
    {
        paths[0] = strdup(".");
        paths[1] = NULL;
        return (paths);
    }
    i = 1;
    j = 0;
    while (i < argc)
    {
        printf("\n%d\n", i);
        if (argv[i][0] != '-')
        {
            paths[j] = strdup(argv[i]);
            printf("paths[%d] = %s\n", j, paths[j]);
            j += 1;
        }
        i += 1;
    }
    paths[j] = NULL;
    return (paths);
}

void                push_front(t_dir **head, char *name)
{
    printf("->%s\n", __func__);
    t_dir           *new;

    new = malloc(sizeof(t_dir));
    new->prev = NULL;
    new->file = malloc(sizeof(t_file));
    new->file->name = strdup(name);
    if (*head)
    {
        (*head)->prev = new;
        new->next = *head;
    }
    else
    {
        new->next = NULL;
    }
    *head = new;
}

t_dir               *pull_entries(DIR *dirp, t_op *o)
{
    printf("->%s\n", __func__);
    t_dir           *dir;
    struct dirent   *current;

    dir = NULL;
    while ((current = readdir(dirp)))
    {
        if (current->d_name[0] != '.' || o->a)
        {
            push_front(&dir, current->d_name);
            printf("%s -> %s\n", current->d_name, dir->file->name);
        }    
    }
    return (dir);
}

t_dir               *store_filename(char *name)
{
    t_dir           *dir;

    dir = malloc(sizeof(t_dir));
    dir->file = malloc(sizeof(t_file));
    dir->file->name = strdup(name);
    dir->prev = NULL;
    dir->next = NULL;
    return (dir);
}

t_dir               *read_directory(char *path, t_op *o)
{
    printf("->%s\n", __func__);
    DIR             *dirp;
    t_dir           *dir;

    dirp = opendir(path);
    if (dirp == NULL)
    {
        if (errno == ENOTDIR)
        {
            printf("%s\n", path);
            dir = store_filename(path);
            return (dir);
        }
        else if (errno == ENOENT)
        {
            printf("ls: cannot access '%s': no such file or directory\n", path);
        }
        return (NULL);
    }
    dir = pull_entries(dirp, o);
    return (dir);
}

void                print_dir(t_dir *dir)
{
    static int          start = 1;
    if (start)
    {
        printf("->%s\n", __func__);
        start = 0;
    }
    if (dir)
    {
        printf("%s\n", dir->file->name);
        print_dir(dir->next);
    }
}

void                swap_nodes(t_dir **a, t_dir **b)
{
    printf("->%s\n", __func__);
    t_file           *tmp;

    tmp = (*a)->file;
    (*a)->file = (*b)->file;
    (*b)->file = tmp;
}

void                sort_alphabet(t_dir **head, t_op *o)
{
    printf("->%s\n", __func__);
    t_dir           *tmp1;
    t_dir           *tmp2;
    int             sorted;


    sorted = 0;
    while (!sorted)
    {
        tmp1 = *head;
        tmp2 = (*head)->next;
        sorted = 1;
        while (tmp2)
        {
            if (!o->r && strcmp(tmp1->file->name, tmp2->file->name) > 0)
            {
                swap_nodes(&tmp1, &tmp2);
                sorted = 0;
            }
            else if (o->r && strcmp(tmp1->file->name, tmp2->file->name) < 0)
            {
                swap_nodes(&tmp1, &tmp2);
                sorted = 0;
            }
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
    }
}

void                extract_stats(t_dir **node, struct stat buf)
{
    printf("->%s\n", __func__);
    (*node)->file->mode = buf.st_mode;
    if (S_ISDIR(buf.st_mode))
    {
        printf("%s is a directory\n", (*node)->file->name);
    }
    else if (S_ISREG(buf.st_mode))
    {
        printf("%s is a regular file\n", (*node)->file->name);
    }

}

void                long_format(t_dir **head, t_op *o)
{
    printf("->%s\n", __func__);
    struct stat     buf;
    t_dir           *tmp;

    tmp = *head;
    while (tmp)
    {
        lstat(tmp->file->name, &buf);
        extract_stats(&tmp, buf);
        tmp = tmp->next;
    }
}

int                 ft_ls(char *path, t_op *o)
{
    printf("->%s\n", __func__);
    t_dir           *dir;

    dir = read_directory(path, o);
    if (o->l)
    {
        long_format(&dir, o);
    }
    if (o->t)
    {
//        sort_time(&dir, o);
    }
    else
    {
        sort_alphabet(&dir, o);
    }
    print_dir(dir);
    return (1);
}

int                 main(int argc, char **argv)
{
    t_op        op;
    char        **paths;
    int         i;

    init_op_struct(&op);
    if (argc == 1)
    {
        ft_ls(".", &op);
    }
    else if (argc > 1)
    {
        paths = split_input(&op, argc, argv);
        if (!paths)
        {
            printf("paths = NULL\n");
            return (0);
        }
        i = 0;
        while (paths[i])
        {
            if (!ft_ls(paths[i], &op))
            {
                printf("Error -> invalid path name\n");
            }
            free(paths[i]);
            i += 1;
        }
    }
}
