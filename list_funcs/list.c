#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

typedef struct  s_list
{
    char            *content;
    struct s_list   *next;
}               t_list;

void            list_add_front(t_list **head, char *content)
{
    t_list      *new;

    new = malloc(sizeof(t_list));
    new->content = strdup(content);
    if (!(*head))
    {
        *head = new;
        new->next = NULL;
    }
    else
    {
        new->next = *head;
        *head = new;
    }
}

void            print_list(t_list *list)
{
    if (list->content)
    {
        printf("%s -> ", list->content);
    }
    if (list->next)
    {
        print_list(list->next);
    }
    else
    {
        printf("end\n");
    }
}

void            to_upper(char **str)
{
    char        *tmp;
    int         i;

    tmp = *str;
    i = 0;
    while (tmp[i])
    {
        if (tmp[i] >= 'a' && tmp[i] <= 'z')
        {
            tmp[i] = tmp[i] - 'a' + 'A';
        }
        i += 1;
    }
}

void            list_map(t_list **head, void (*f)(char **str))
{
    t_list      *list;

    list = *head;
    while (list)
    {
        (*f)(&list->content);
        list = list->next;
    }
}

void            capitalize(t_list **head)
{
    list_map(head, to_upper);
}

void            list_del_node(t_list **node, t_list **lag)
{
    if ((*node)->next == NULL)
    {    
        (*lag)->next = NULL;
    }
    else
    {
        (*lag)->next = (*node)->next;
        (*node) = (*node)->next;
    }
        //  free((*node)->content);
   // free(*node);
}

int             is_num(char *str)
{
    int         i;

    i = 0;
    while (str[i])
    {
        if (str[i] >= '0' || str[i] <= '9')
        {
            return (1);
        }
        i += 1;
    }
    return (0);
}

void            delete_numbers(t_list **head)
{
    t_list      *tmp;
    t_list      *lag;

    lag = *head;
    tmp = lag->next;
    while (tmp)
    {
        if (is_num(tmp->content))
        {
            list_del_node(&tmp, &lag);
        }
        tmp = tmp->next;
        lag = lag->next;
    }
}

int             main(int argc, char **argv)
{
    t_list      *list;

    list = NULL;
    
    int     i;
    i = argc - 1;

    while (i)
    {
        list_add_front(&list, argv[i]);
        i -= 1;
    }
    printf("->print_list\n");
    print_list(list);
    printf("\n->end print_list\n");
    printf("\n->capitalize\n");
    capitalize(&list);
    printf("\n->end capitalize\n");
    printf("->print_list\n");
    print_list(list);
    printf("\n->end print_list\n");
    printf("\n->delete numbers\n");
    delete_numbers(&list);
    printf("\n->end delete numbers\n");
    printf("->print_list\n");
    print_list(list);
    printf("\n->end print_list\n");

    return (0);
}
