/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 08:41:57 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/10 09:10:18 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct		node
{
	int				data;
	struct node		*parent;
	struct node		*left;
	struct node		*right;	
}					btree;

btree			*btree_new(int value)
{
	btree		*new;

	new = malloc(sizeof(*new));
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->data = value;
	return (new);
}

void			insert_data(btree **root, int data)
{
	btree			*tmp;

	tmp = *root;
	if (data <= tmp->data)
	{
		if (!tmp->left)
		{
			tmp->left = btree_new(data);
			tmp->left->parent = tmp;
		}
		else
		{
			insert_data(&tmp->left, data);
		}
	}
	else if (data > tmp->data)
	{
		if (!tmp->right)
		{
			tmp->right = btree_new(data);
			tmp->right->parent = tmp;
		}
		else
		{
			insert_data(&tmp->right, data);
		}
	}	
}

void			print_btree_postorder(btree *node)
{
	if (node->left)
	{
		print_btree_postorder(node->left);
	}
	if (node->right)
	{
		print_btree_postorder(node->right);
	}
	printf("%d ", node->data);
}

void			print_btree_inorder(btree *node)
{
	if (node->left)
	{
		print_btree_inorder(node->left);
	}
	printf("%d ", node->data);
	if (node->right)
	{
		print_btree_inorder(node->right);
	}
}

void			print_btree_preorder(btree *node)
{
	printf("%d ", node->data);
	if (node->left)
	{
		print_btree_preorder(node->left);
	}
	if (node->right)
	{
		print_btree_preorder(node->right);
	}
}

int				main(int argc, char **argv)
{
	btree			**tree;
	btree			*root;

	if (argc > 1)
	{
		root = btree_new(atoi(argv[1]));
		tree = &root;
		int		i = 2;
		while (i < argc)
		{
			insert_data(tree, atoi(argv[i]));
			i += 1;
		}
	}
	print_btree_preorder(root);
	printf("\n");
	print_btree_inorder(root);
	printf("\n");
	print_btree_postorder(root);
	printf("\n");
	return (0);
}
