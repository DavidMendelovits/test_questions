#include "ft_ls.h"

#define OPTIONS "lrRat"
#define OPTIONS_ERROR "Error -> invalid options...\n"

void                init_options(t_opt *options)
{
    options->l = 0;
    options->r = 0;
    options->R = 0;
    options->a = 0;
    options->t = 0;
}                

int                 is_opt(char c)
{
    int             i;

    i = 0;
    while (OPTIONS[i])
    {
        if (c == OPTIONS[i])
        {
            return (1);
        }
        i += 1;
    }
    return (0);
}

void                extract_opt(t_opt *o, char c)
{
    if (c == 'l')
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
    else if (c == 'a')
    {
        o->a = 1;
    }
    else if (c == 't')
    {
        o->t = 1;
    }
}


void                lst_add_back(t_list **head, char *content)
{
    t_list          *new;
    t_list          *tmp;
    t_list          *lag;

    new = (t_list *)malloc(sizeof(t_list));
    new->next = NULL;
    new->path = strdup(content);
    tmp = *head;
    if (tmp)
    {
        lag = *head;
        tmp = tmp->next;
        while (tmp)
        {
            lag = lag->next;
            tmp = tmp->next;
        }
        new->prev = lag;
        lag->next = new;
    }
    else
    {
        *head = new;
    }
}

t_list              *split_arguments(int argc, char **argv, t_opt *options)
{
    int             i;
    int             j;
    t_list          *list;

    list = NULL;
    i = 1;
    while (i < argc)
    {
        if (argv[i][0] == '-')
        {
            j = 1;
            while (argv[i][j] != '\0')
            {
                if (!is_opt(argv[i][j]))
                {
                    return (NULL);
                }
                else
                {
                    extract_opt(options, argv[i][j]);
                }
                j += 1;
            }
        }
        else
        {
            lst_add_back(&list, argv[i]);
        }
        i += 1;
    }
    return (list);
}

void                print_list(t_list *list)
{
    if (list)
    {
        printf("content = %s\n", list->path);
        list = list->next;
        print_list(list);
    }
}

void                copy_details(t_file **file, struct dirent *current, struct stat buf, t_opt *o)
{
    printf("\nfunction -> copy_details\n");    
    if (o->l)
    {
        if (lstat(current->d_name, &buf) == -1)
        {
            printf("\nerror with lstat\n");
        }
        else
        {
            (*file)->name = strdup(current->d_name);
            (*file)->block_size = (size_t)buf.st_size;
        }
    }
}

t_file              *extract_file_details(struct dirent *current, t_opt *o)
{
    t_file          *file;
    struct stat     stat_buf;

    printf("\nfunction -> extract_file_details\n");
    file = (t_file *)malloc(sizeof(t_file));
    if (o->t || o->l)
    {
        copy_details(&file, current, stat_buf, o);
    }
    else
    {
        file->name = strdup(current->d_name);
        printf("extracted filename: %s\n", file->name);
    }
    return (file);
}

void                add_entry_front(t_dir **head, struct dirent *current, t_opt *o)
{
    t_file          *file;
    t_dir           *new;

    new = (t_dir *)malloc(sizeof(t_dir));
    new->prev = NULL;
    new->file = extract_file_details(current, o);
    if (!(*head))
    {
        *head = new;
        new->next = NULL;
    }
    else
    {
        new->next = *head;
        (*head)->prev = new;
        *head = new;
    }
}

t_dir               *populate_entry_list(char *path, t_opt *o)
{
    DIR             *dir;
    struct dirent   *current;
    t_dir           *list;

    dir = opendir((const char *)path);
    list = NULL;
    while ((current = readdir(dir)))
    {
        if (o->a || current->d_name[0] != '.')
        {
            add_entry_front(&list, current, o);
        }
    }
    closedir(dir);
    return (list);
}

void                print_entries(t_dir *entries)
{
    printf("\nfunction -> print_entries\n");
    while (entries)
    {
        printf("%s\n", entries->file->name);
        entries = entries->next;
    }
}

int                 ft_ls(char *path, t_opt *o)
{
    t_dir           *entries;

    entries = populate_entry_list(path, o);
    print_entries(entries);

    return (1);
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
    else if (argc >= 2)
    {
        list = split_arguments(argc, argv, &options);
        if (!list)
        {
            write(2, OPTIONS_ERROR, strlen(OPTIONS_ERROR));
        }
        print_list(list);
        while (list)
        {
            ft_ls(list->path, &options);
            list = list->next;
        }
   //     free_list(&list);
    }
    return (0);
}
