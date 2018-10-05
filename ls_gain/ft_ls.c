#include "ft_ls.h"
#define WOW() printf("->%s\n", __func__)

void                init_options(t_opt *o)
{
    o->l = 0;
    o->a = 0;
    o->t = 0;
    o->r = 0;
    o->R = 0;
}

int                 is_opt(char c)
{
    if (c == 'l' || c == 'a' || c == 'r' || c == 'R' || c == 't')
    {
        return (1);
    }
    return (0);
}

int                 opt_check(t_opt *o, char *arg)
{
    WOW();
    int             i;

    i = 1;
    while (arg[i])
    {
        if (is_opt(arg[i]))
        {
            if (arg[i] == 'l')
            {
                o->l = 1;
            }
            else if (arg[i] == 'a')
            {
                o->a = 1;
            }
            else if (arg[i] == 'r')
            {
                o->r = 1;
            }
            else if (arg[i] == 'R')
            {
                o->R = 1;
            }
            else if (arg[i] == 't')
            {
                o->t = 1;
            }
        }
        else
        {
            return (0);
        }
        i += 1;
    }
    return (1);
}

void                list_add_front(t_list **head, char *content)
{
    WOW();
    t_list          *new;

    new = malloc(sizeof(t_list));
    new->content = strdup(content);
    new->prev = NULL;
    if (!(*head))
    {
        new->next = NULL;
        *head = new;
    }
    else
    {
        new->next = *head;
        (*head)->prev = new;
        *head = new;
    }
}

void                print_list(t_list *head)
{
    WOW();
    if (!head)
    {
        return ;
    }
    if (head->content)
    {
        printf("%s\n", head->content);
    }
    if (head->next)
    {
        print_list(head->next);
    }
}

t_list              *split_args_options(t_opt *o, int argc, char **argv)
{
    WOW();
    int             i;
    int             j;
    t_list          *list;

    i = 1;
    list = NULL;
    while (i < argc)
    {
        if (argv[i][0] == '-')
        {
            if (!opt_check(o, argv[i]))
            {
                return (NULL);
            }
        }
        else
        {
            list_add_front(&list, argv[i]);
        }
        i += 1;
    }
    return (list);
}

void                dir_add_front(t_dir **head, char *filename, char *path)
{
    WOW();
    t_dir           *new;
    
    new = malloc(sizeof(t_dir));
    new->file = malloc(sizeof(t_file));
    new->file->name = strdup(filename);
    new->prev = NULL;
    new->path = path;
    if (!(*head))
    {
        new->next = NULL;
        *head = new;
    }
    else
    {
        new->next = *head;
        (*head)->prev = new;
        *head = new;
    }
}

void                pull_inode(t_dir **entry, struct stat buf)
{
    WOW();
    memset((*entry)->file->permissions, '-', 10);
    (*entry)->file->permissions[10] = '\0';
    if (S_ISDIR(buf.st_mode))
    {
        (*entry)->file->permissions[0] = 'd';
    }
    if (buf.st_mode & S_IRUSR)
    {
        (*entry)->file->permissions[1] = 'r';
    }
    if (buf.st_mode & S_IWUSR)
    {
        (*entry)->file->permissions[2] = 'w';
    }
    if (buf.st_mode & S_IXUSR)
    {
        (*entry)->file->permissions[3] = 'x';
    }
    if (buf.st_mode &  S_IRGRP)
    {
        (*entry)->file->permissions[4] = 'r';
    }
    if (buf.st_mode & S_IWGRP)
    {
        (*entry)->file->permissions[5] = 'w';
    }
    if (buf.st_mode & S_IXGRP)
    {
        (*entry)->file->permissions[6] = 'x';
    }
    if (buf.st_mode & S_IROTH)
    {
        (*entry)->file->permissions[7] = 'r';
    }
    if (buf.st_mode & S_IWOTH)
    {
        (*entry)->file->permissions[8] = 'w';
    }
    if (buf.st_mode & S_IXOTH)
    {
        (*entry)->file->permissions[9] = 'x';
    }
}

void                pull_nlinks(t_dir **entry, struct stat buf)
{
    WOW();
    (*entry)->file->links = buf.st_nlink;
}

void                pull_uid_gid(t_dir **entry, struct stat buf)
{
    WOW();
    struct passwd   *uid;
    struct group    *gid;

    uid = getpwuid(buf.st_uid);
    (*entry)->file->uid = strdup(uid->pw_name);
    gid = getgrgid(buf.st_gid);
    (*entry)->file->gid = strdup(gid->gr_name);
}

void                pull_size(t_dir **entry, struct stat buf)
{
    WOW();
    (*entry)->file->size = (size_t)buf.st_size;
}

void                pull_time(t_dir **entry, struct stat buf)
{
    WOW();
    (*entry)->file->time = buf.st_mtime;
    (*entry)->file->formatted_time = strndup(ctime(&buf.st_mtime), 16);
}

char                *path_join(char *front, char *back)
{
    WOW();
    char            *new;
    int             i;
    int             j;

    printf("front: %s\nback: %s\n", front, back);
    new = malloc(sizeof(char) * (strlen(front) + strlen(back) + 2));
    i = 0;
    j = 0;
    while (front[j])
    {
        new[i] = front[j];
        i += 1;
        j += 1;
    }

    j = 0;
    if (new[i - 1] != '/')
    {
        new[i] = '/';
        i += 1;
    }
    while (back[j])
    {
        new[i] = back[j];
        i += 1;
        j += 1;
    }
    new[i] = '\0';
    printf("new: %s\n", new);
    return (new);
}

void                pull_long_format(t_dir **entry)
{
    WOW();
    struct stat     buf;
    char            *path;

    if ((*entry)->path)
    {
        printf("path: %s\n", (*entry)->path);
        path = path_join((*entry)->path, (*entry)->file->name);
        printf("path: %s\n", (*entry)->path);
    }
    else
    {
        path = (*entry)->file->name;
    }
    printf("filename: %s\n", (*entry)->file->name);
    lstat(path, &buf);
    pull_inode(entry, buf);
    pull_nlinks(entry, buf);
    pull_uid_gid(entry, buf);
    pull_size(entry, buf);
    pull_time(entry, buf);

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

t_dir               *read_dir(DIR *dirp, t_opt *o, char *path)
{
    struct dirent   *_dirent;
    t_dir           *dir;

    dir = NULL;
    while ((_dirent = readdir(dirp)))
    {
        if (_dirent->d_name[0] != '.' || o->a)
        {
            dir_add_front(&dir, _dirent->d_name, path);
        }
        if (o->l)
        {
            pull_long_format(&dir);
        }
    }
    return (dir);
}

void                print_dir(t_dir *dir)
{
    if (!dir)
    {
        return ;
    }
    if (dir->file)
    {
        printf("%s/", dir->path);
        printf("%s\n", dir->file->name);
    }
    if (dir->next)
    {
        print_dir(dir->next);
    }
}

void                swap_nodes(t_file **a, t_file **b)
{
    WOW();
    t_file          *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void                sort_lex(t_dir **head, t_opt *o)
{
    WOW();
    t_dir           *tmp;
    int             sorted;


    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        tmp = *head;
        while (tmp->next)
        {
            if (strcmp(tmp->file->name, tmp->next->file->name) > 0 && !o->r)
            {
                swap_nodes(&tmp->file, &tmp->next->file);
                sorted = 0;
            }
            else if (strcmp(tmp->file->name, tmp->next->file->name) < 0 && o->r)
            {
                swap_nodes(&tmp->file, &tmp->next->file);
                sorted = 0;
            }
            tmp = tmp->next;
        }
    }
}

void                sort_time(t_dir **head, t_opt *o)
{
    WOW();
    t_dir           *tmp;
    int             sorted;

    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        tmp = *head;
        while (tmp->next)
        {
            if (tmp->file->time < tmp->next->file->time && !o->r)
            {
                swap_nodes(&tmp->file, &tmp->next->file);
                sorted = 0;
            }
            else if (tmp->file->time > tmp->next->file->time && o->r)
            {
                swap_nodes(&tmp->file, &tmp->next->file);
                sorted = 0;
            }
            tmp = tmp->next;
        }
    }
}

void                sort_dir(t_dir **head, t_opt *o)
{
    if (o->t)
    {
        sort_time(head, o);
    }
    else
    {
        sort_lex(head, o);
    }

}

void                do_recursion(t_dir *entries, t_opt *o, char *path)
{
    char            *_path;

    while (entries)
    {
        if (entries->file->permissions[0] == 'd')
        {
            entries->path = path_join(path, entries->file->name);
            printf("path: %s\n", entries->path);
            ft_ls(entries->path, o);
        }
        entries = entries->next;
    }
}

int                 ft_ls(char *path, t_opt *o)
{
    DIR             *dirp;
    t_dir           *dir;

    dirp = opendir(path);
    dir = read_dir(dirp, o, path);
    sort_dir(&dir, o);
    if (o->l)
    {
        print_long(dir);
    }
    else
    {
        print_dir(dir);
    }
    if (o->R)
    {
        do_recursion(dir, o, path);
    }
    return (1);
}

void                queue_dir(t_list *list, t_opt *o)
{
    if (!list)
    {
        return ;
    }
    if (list)
    {
        ft_ls(list->content, o);
    }
    if (list->next)
    {
        queue_dir(list->next, o);
    }
}

int                 main(int argc, char **argv)
{
    t_opt           options;
    t_list          *list;

    init_options(&options);
    if (argc == 1)
    {
        ft_ls(".", &options);
    }
    else
    {
        list = NULL;
        list = split_args_options(&options, argc, argv);
        print_list(list);
        if (list)
            queue_dir(list, &options);
        else
        {
            ft_ls(".", &options);
        }
    }
    return (1);
}
