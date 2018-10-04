#include "ft_ls.h"

#define OPTIONS "alrRt"
#define WOW() printf("->%s\n", __func__);
int             opt_check(char c, t_op *o)
{
    WOW();
    if (c == 'a')
    {
        o->a = 1;
    }
    else if (c == 'l')
    {
        o->l = 1;
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
    else
    {
        return (0);
    }
    return (1);
}

char            **split_input(int argc, char **argv, t_op *o)
{
    WOW();
    int             i;
    int             j;
    char            **paths;
    int             p;
    int             path_count;

    i = 1;
    path_count = 0;
    while (i < argc)
    {
        if (argv[i][0] == '-' && strlen(argv[i]) > 1)
        {
            j = 1;
            while (argv[i][j])
            {
                if (!opt_check(argv[i][j], o))
                {
                    printf("ls: invalid option -- '%c'\n", argv[i][j]);
                    return (NULL);
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
    i = 1;
    p = 0;
    paths = malloc(sizeof(*paths) * (path_count + 1));
    while (i < argc)
    {
        if (argv[i][0] != '-' || strlen(argv[i]) == 1)
        {
            paths[p] = strdup(argv[i]);
            p += 1;
        }
        i += 1;
    }
    paths[p] = NULL;
    return (paths);
}

t_dir           *read_single_file(char *filename)
{
    WOW();
    t_dir           *entries;

    entries = malloc(sizeof(t_dir));
    entries->file = malloc(sizeof(t_file));
    entries->file->name = strdup(filename);
    return (entries);
}

void            add_entry_front(t_dir **head, char *filename)
{
    WOW();
    t_dir           *new;

    new = malloc(sizeof(t_dir));
    new->file = malloc(sizeof(t_file));
    new->prev = NULL;
    new->file->name = strdup(filename);
    if (*head)
    {
        new->next = *head;
        (*head)->prev = new;
    }
    else
    {
        new->next = NULL;
    }
    *head = new;
}

t_dir           *pull_entries(DIR *dirp, t_op *o)
{
    WOW();
    struct dirent   *entry;
    t_dir           *dir;

    dir = NULL;
    while (entry = readdir(dirp))
    {
        if (entry->d_name[0] != '.' || o->a)
        {
            add_entry_front(&dir, entry->d_name);     
        }
    }
    return (dir);
}

void            print_entries(t_dir *dir)
{
    static int      start = 1;
    if (start)
    {
        WOW();
        start = 0;
    }
    printf("%s\n", dir->file->name);
    if (dir->next)
    {
        print_entries(dir->next);
    }
}

void            list_entries(t_dir *dir, t_op *o)
{
    WOW();
    print_entries(dir);
}

void            ft_swap(t_file **a, t_file **b)
{
    t_file      *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void            sort_alph(t_dir **head, t_op *o)
{
    WOW();
    t_dir       *tmp1;
    t_dir       *tmp2;
    int         sorted;

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
                sorted = 0;
                ft_swap(&tmp1->file, &tmp2->file);
            }
            else if (o->r && strcmp(tmp1->file->name, tmp2->file->name) < 0)
            {
                sorted = 0;
                ft_swap(&tmp1->file, &tmp2->file);
            }
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
    }
}

void            sort_entries(t_dir **head, t_op *o)
{
    WOW();
    if (o->t)
    {
//        sort_time(head, o);
        return ;
    }
    sort_alph(head, o);
}

void            read_mode(t_file **file, struct stat buf)
{
    WOW();
    memset((*file)->permissions, '-', 10);
    (*file)->permissions[10] = '\0';
    if (S_ISDIR(buf.st_mode))
    {
        (*file)->permissions[0] = 'd';
    }
    if (buf.st_mode & S_IRUSR)
    {
        (*file)->permissions[1] = 'r';
    }
    if (buf.st_mode & S_IWUSR)
    {
        (*file)->permissions[2] = 'w';
    }
    if (buf.st_mode & S_IXUSR)
    {
        (*file)->permissions[3] = 'x';
    }
    if (buf.st_mode &  S_IRGRP)
    {
        (*file)->permissions[4] = 'r';
    }
    if (buf.st_mode & S_IWGRP)
    {
        (*file)->permissions[5] = 'w';
    }
    if (buf.st_mode & S_IXGRP)
    {
        (*file)->permissions[6] = 'x';
    }
    if (buf.st_mode & S_IROTH)
    {
        (*file)->permissions[7] = 'r';
    }
    if (buf.st_mode & S_IWOTH)
    {
        (*file)->permissions[8] = 'w';
    }
    if (buf.st_mode & S_IXOTH)
    {
        (*file)->permissions[9] = 'x';
    }

}

void            read_links(t_file **file, struct stat buf)
{
    WOW();
    (*file)->links = buf.st_nlink;
}

void            read_uid_gid(t_file **file, struct stat buf)
{
    WOW();
    char            *username;
    char            *groupname;
    struct passwd   *uid;
    struct group    *gid;

    uid = getpwuid(buf.st_uid);
    gid = getgrgid(buf.st_gid);

    printf("%s\n", (*file)->name);
    (*file)->uid = strdup(uid->pw_name);

    printf("we got here\n");
    (*file)->gid = strdup(gid->gr_name);
}

void            read_size(t_file **file, struct stat buf)
{
    WOW();
    (*file)->size = buf.st_size;
}

void            read_mtime(t_file **file, struct stat buf)
{
    WOW();
    (*file)->mod_time = buf.st_mtime;
    (*file)->formatted_time = strndup(ctime(&buf.st_mtime), 16);;

}

void            pull_long_format(t_dir **head, t_op *o)
{
    WOW();
    t_dir           *tmp;
    struct stat     buf;

    tmp = *head;
    while (tmp)
    {
        lstat(tmp->file->name, &buf);
        read_mode(&tmp->file, buf);
        read_links(&tmp->file, buf);
        read_uid_gid(&tmp->file, buf);
        read_size(&tmp->file, buf);
        read_mtime(&tmp->file, buf);
  //      printf("%s -> permissions: %s links: %d uid: %s gid: %s size: %lu mtime: %s\n", tmp->file->name, tmp->file->permissions, (int)tmp->file->links, tmp->file->uid, tmp->file->gid, tmp->file->size, tmp->file->formatted_time);
        tmp = tmp->next;
    }
}

void            print_long(t_dir *entries)
{
    static int start = 1;
    if (start)
    {
        WOW();
        start = 0;
    }
    printf("%s ", entries->file->permissions);
    printf("%ld ", entries->file->links);
    printf("%s ", entries->file->uid);
    printf("%s ", entries->file->gid);
    printf("%ld ", entries->file->size);
    printf("%s ", entries->file->formatted_time);
    printf("%s\n", entries->file->name);
    if (entries->next)
    {
        print_long(entries->next);
    }
}

void            list_long(t_dir *entries, t_op *o)
{
    print_long(entries);
}

int             ft_ls(char *path, t_op *o)
{
    WOW();
    t_dir           *entries;
    DIR             *dirp;
    int             R = 0;

    dirp = opendir(path);
    if (!dirp)
    {
        if (errno == ENOTDIR)
        {
            entries = read_single_file(path);
        }
        else
        {
            printf("ls: invalid pathname '%s'\n", path);
            return (0);
        }
    }
    else
    {
        entries = pull_entries(dirp, o);
    }
    if (entries)
    {
        if (o->l)
        {
            pull_long_format(&entries, o);
        }
        sort_entries(&entries, o);
        (o->l) ? list_long(entries, o) : list_entries(entries, o);
    }
    return (1);
}

void            print_options(t_op o)
{
    if (o.a)
    {
        printf("a\n");
    }
    if (o.l)
    {
        printf("l\n");
    }
    if (o.r)
    {
        printf("r\n");
    }
    if (o.R)
    {
        printf("R\n");
    }
    if (o.t)
    {
        printf("t\n");
    }
}

void            init_options(t_op *o)
{
    o->a = 0;
    o->l = 0;
    o->r = 0;
    o->R = 0;
    o->t = 0;
}

int             main(int argc, char **argv)
{
    t_op            op;
    char            **paths;
    int             p;

    if (argc == 1)
    {
        ft_ls(".", &op);
    }
    init_options(&op);
    paths = split_input(argc, argv, &op);
    print_options(op);
    if (!paths)
    {
        return (1);
    }
    p = 0;
    while (paths[p])
    {
        if (!ft_ls(paths[p], &op))
            return (1);
        free(paths[p]);
        p += 1;
    }
    if (p == 0)
    {
        ft_ls(".", &op);
    }
    free(paths);
    return (0);
}
