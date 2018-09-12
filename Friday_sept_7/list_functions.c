#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//list_create
//list add_back
//list pop_back
//list map
//list find

typedef struct      s_list
{
    char            *content;
    struct s_list   *next; 
    struct s_list   *head;
}                   t_list;


void                add_back(t_list *list, char *content, t_list *head)
{
    while (list)
    {
        list = list->next;
        if (!list)
        {
            list = malloc(sizeof(t_list));
            list->head = head;
            break ;
        }
    }
    list->content = content;
    printf("add_back: list->content = %s\n", list->content);
    list->next = NULL;
 //   list = list->next;
}

void                print_list(t_list *list)
{
    printf("function -> print_list\n");
    while (list)
    {
        printf("%s\n", list->content);
        list = list->next;
    }
}

int                 main()
{
    t_list      *list;

    list = malloc(sizeof(t_list));
    list->content = strdup("first");
    list->head = list;
    list->next = NULL;
    printf("list->content = %s\n", list->content);
    add_back(list, strdup("second"), list->head);
    add_back(list, strdup("third"), list->head);
    add_back(list, strdup("fourth"), list->head);
    print_list(list->head);
    printf("list->content = %s\n", list->content);

}
