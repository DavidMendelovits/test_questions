/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 09:19:59 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/02 09:46:05 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

struct s_node
{
	void			*content;
	struct s_node	*next;
};

struct s_queue
{
	struct s_node	*first;
	struct s_node	*last;
};

struct s_queue		*init(void)
{
	struct s_queue		*new;

	new = malloc(sizeof(*new));
	new->first = NULL;
	new->last = NULL;
	return (new);
}

int					isEmpty(struct s_queue *queue)
{
	if (queue->first == NULL)
		return (1);
	return (0);
}

void				enqueue(struct s_queue *queue, void *content)
{
	struct s_node		*new;
	
	new = malloc(sizeof(*new));
	new->content = content;
	new->next = NULL;
	if (isEmpty(queue))
	{
		queue->first = new;
		queue->last = new;
	}
	else
	{
		queue->last->next = new;
		queue->last = new;
	}
}

void				*dequeue(struct s_queue *queue)
{
	void			*ret;
	struct s_node	*free_;

	if (isEmpty(queue))
	{
		return (NULL);
	}
	ret = queue->first->content;
	free_ = queue->first;
	queue->first = queue->first->next;
	free(free_);
	if (queue->first == NULL)
	{
		queue->last = NULL;
	}
	return (ret);
}

void				*peek(struct s_queue *queue)
{
	return (queue->first->content);
}
