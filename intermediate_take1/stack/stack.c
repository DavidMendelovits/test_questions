/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 09:52:03 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/02 10:21:22 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

struct s_node
{
	void			*content;
	struct s_node	*next;
};

struct s_stack
{
	struct s_node	*top;
};

struct s_stack		*init(void)
{
	struct s_stack	*new;

	new = malloc(sizeof(new));
	new->top = NULL;
	return (new);
}

int					isEmpty(struct s_stack *stack)
{
	if (stack->top == NULL)
	{
		return (1);
	}
	return (0);
}

void				*pop(struct s_stack *stack)
{
	void			*ret;
	struct s_node	*free_;

	if (isEmpty(stack))
	{
		return (NULL);
	}
	ret = stack->top->content;
	free_ = stack->top;
	stack->top = stack->top->next;
	free(free_);
	return (ret);
}

void				push(struct s_stack *stack, void *content)
{
	struct s_node	*new;

	new = malloc(sizeof(*new));
	new->content = content;
	new->next = stack->top;
	stack->top = new;
}

void				*peek(struct s_stack *stack)
{
	return (stack->top->content);
}
