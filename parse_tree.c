/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:42:00 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 20:10:37 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node(t_link_list *node)
{
	if (node && node->data)
		free(node->data);
	if (node)
		free(node);
	node = NULL;
}

static t_tree	*pipeit(t_tree **tree, t_link_list **head,
	t_link_list **current, int *error)
{
	t_tree	*tree_current;

	tree_current = get_tree(tree);
	if (!tree_current)
		*error = 1;
	else
		tree_current->type = (*current)->type;
	if ((*current)->prev && tree_current)
	{
		tree_current->left = get_node((*current)->prev);
		if (!tree_current->left)
			*error = 1;
	}
	if ((*current)->next)
	{
		*head = (*current)->next;
		(*current)->next->prev = NULL;
	}
	else
		*head = NULL;
	if ((*current)->prev)
		free_node((*current)->prev);
	free_node(*current);
	*current = *head;
	return (*tree);
}

static t_tree	*build_last(t_tree **tree, t_link_list **current, int *error)
{
	t_tree	*last;

	last = get_tree(tree);
	if (!last)
		*error = 1;
	else
		last->type = (*current)->type;
	last->data = ft_strdup((*current)->data);
	if (!last->data)
		*error = 1;
	free((*current)->data);
	free((*current));
	return (*tree);
}

t_tree	*build_tree(t_link_list **head, t_tree **tree, int *error)
{
	t_link_list	*current;

	if (!head || !*head)
		return (NULL);
	current = *head;
	while (current)
	{
		if (*error != 0)
			break ;
		while (current && current->type < 2)
			current = current->next;
		if (current && current->type == PIPE)
			*tree = pipeit(tree, head, &current, error);
		else if (current && current->type > 2)
			*tree = redirect(tree, head, &current, error);
	}
	if (*head && (*head)->type == CMD)
		*tree = build_last(tree, head, error);
	if (*error != 0)
	{
		free_tree(*tree);
		return (NULL);
	}
	return (*tree);
}
