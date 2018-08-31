#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct		s_list
{
	char		*content;
	struct s_list	*next;
}			t_list;

void	ft_list_add(char *arg, t_list *list)
{
	t_list		*new_head;

	new_head = malloc(sizeof(list));
	new_head->content = (char*)strdup(arg);
	new_head->next = list;
}

void	list_map(void (*f)(t_list *list))
{
	while (list->content)
	{
		(*f)(list->content);
		list = list->next;
	}
}

void	print_content(t_list *list)
{
	printf("\ncontent in node: %s\n", list->content);
}

t_list	*list_search(t_list *list, char *criteria)
{
	while (list->content)
	{
		if (strcmp(list->content, criteria))
		{
			break ;
		}
		list = list->next;
	}
	return (list);
}

int	main(int argc, char **argv)
{
	int		i;
	t_list		*list;
	char		*start;

	list = malloc(sizeof(t_list));
	start = strdup("first_node or last node?: ");
	list->content = start;
	list->next = NULL;
	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
			ft_list_add(argv[i], list);
			i += 1;
		}
		list_map((print_content)(list));
	}
}
