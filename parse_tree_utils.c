/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:57 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 12:41:59 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*construct_node(void)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = -1;
	tree->data = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

t_tree	*get_tree(t_tree **tree)
{
	t_tree	*current;

	if (!(*tree))
	{
		*tree = construct_node();
		if (!*tree)
			return (NULL);
		return (*tree);
	}
	current = *tree;
	while (current->right)
		current = current->right;
	current->right = construct_node();
	if (!current->right)
	{
		free_tree(*tree);
		return (NULL);
	}
	return (current->right);
}

t_tree	*get_node(t_link_list *node)
{
	t_tree	*tree_node;

	tree_node = construct_node();
	if (!tree_node)
		return (NULL);
	tree_node->data = ft_strdup(node->data);
	if (!tree_node->data)
	{
		free(tree_node);
		return (NULL);
	}
	tree_node->type = node->type;
	return (tree_node);
}
