#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct      s_list
{
    char            *content;
    struct s_list   *next;
}                   t_list;

t_list              *list_new(char *content)
{
    t_list          *new;

    new = malloc(sizeof(new));
    new->content = strdup(content);
    new->next = NULL;
    return (new);
}

void                print_list(t_list *list)
{
    if (list)
    {
        printf("content: %s\n", list->content);
        list = list->next;
        print_list(list);
    }
    printf("end_list\n");
}

void                list_find_if(t_list **list, int (*f)(char *content))
{
    t_list          *head;

    head = *list;
    while (head)
    {
        if ((*f)(head->content))
        {
            printf("found number!\n");
        }
        head = head->next;
    }
}

void                list_add(t_list **list, char *content)
{
    t_list          *new;
    
    new = malloc(sizeof(new));
    new->content = strdup(content);
    new->next = *list;
    *list = new;
}

int                 is_number(char *content)
{
    int             i;

    i = 0;
    while (content[i])
    {
        if (content[i] < '0' || content[i] > '9')
        {
            return (0);
        }
        i += 1;
    }
    return (1);
}

void                lst_map(t_list **head, void (*f)(char *content))
{
    t_list          *list;

    list = *head;
    while (list)
    {
        (*f)(list->content);
        list = list->next;
    }
}

int                 is_lower(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return (1);
    }
    return (0);
}

void                to_upp(char *content)
{
    int           i;

    i = 0;
    while (content[i])
    {
        if (is_lower(content[i]))
        {
            content[i] = content[i] - 'a' + 'A';
        }
        i += 1;
    }
}
void                list_del(t_list **node)
{
    free((*node)->content);
    (*node)->next = NULL;
}

void                list_del_node(t_list **node, t_list **head)
{
    t_list          *list;
    t_list          *link;
    
    list = *head;
    while (list)
    {
        if (strcmp(list->next->content, (*node)->content) == 0)
        {
            link = list->next->next;
            list_del(node);
            list->next = link;
        }
        list = list->next;
    }
}

void                list_delete_if(t_list **head, int (*f)(char *content))
{
    t_list          *list;

    printf("function->list_delete_if:\n");
    list = *head;
    while (list)
    {
        printf("list->content: %s\n", list->content);
        if ((*f)(list->content))
        {
            list_del_node(&list, head);
        }
        list = list->next;
    }
}

int                 main()
{
    t_list          *list;

    list = list_new("Hello");
    list_add(&list, "123");
    list_add(&list, "my name isa Jeff");
    list_add(&list, "Correction: my name is Jeff");
    print_list(list);
    lst_map(&list, (to_upp));
    print_list(list);
    list_find_if(&list, (is_number));
    list_delete_if(&list, (is_number));
    return (0);
}
