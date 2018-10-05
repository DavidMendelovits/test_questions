#include "ft_ls.h"
#define WOW() printf("->%s\n",__func__)

void                init_options(t_opt *o)
{
    WOW();
    o->l = 0;
    o->a = 0;
    o->r = 0;
    o->R = 0;
    o->t = 0;
}

void                add_path_front(t_list **head, char *path)
{
    WOW();
    t_list          *new;

    new = malloc(sizeof(t_list));
    new->path = strdup(path);
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

void                print_paths(t_list *paths)
{
    WOW();
    if (!paths)
    {
        return ;
    }
    if (paths->path)
    {
        printf("%s\n", paths->path);
    }
    if (paths->next)
    {
        print_paths(paths->next);
    }
}

int                 opt_check(t_opt *o, char *arg)
{
    WOW();
    int             i;

    i = 0;
    while (arg[i])
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
        else
        {
            return (0);
        }
        i += 1;
    }
    return (1);
}

t_list              *split_options(t_opt *o, int argc, char **argv)
{
    WOW();
    t_list          *paths;
    int             i;

    i = 1;
    paths = NULL;
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
            add_path_front(&paths, argv[i]);
        }
        i += 1;
    }
    return (paths);
}

int                 main(int argc, char **argv)
{
    t_opt           options;
    t_list          *paths;

    init_options(&options);
    printf("argc: %d\n", argc);
    if (argc == 1)
    {
  //      ft_ls(".", &options);
    }
    else
    {
        paths = split_options(&options, argc, argv);
        print_paths(paths);
    }
    return (1);
}
