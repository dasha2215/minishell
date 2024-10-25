/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:54 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 15:41:21 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_redirect_no_prev(t_link_list **head, t_link_list **current)
{
	if ((*current)->next && (*current)->next->next)
	{
		*head = (*current)->next->next;
		(*head)->prev = NULL;
	}
	else
	{
		(*head)->prev = NULL;
		*head = NULL;
	}
}

static void	update_redirect_prev(t_link_list **head, t_link_list **current)
{
	if ((*current)->next && (*current)->next->next)
	{
		(*current)->prev->next = (*current)->next->next;
		(*current)->next->next->prev = (*current)->prev;
		(*current)->prev->prev = NULL;
		*head = (*current)->prev;
	}
	else
	{
		(*current)->prev->next = NULL;
		(*current)->prev->prev = NULL;
		*head = (*current)->prev;
	}
}

void	free_current_redirect(t_link_list **current)
{
	if (!(*current))
		return ;
	if ((*current)->next && (*current)->next->data)
		free((*current)->next->data);
	if ((*current)->next)
		free((*current)->next);
	if ((*current)->data)
		free((*current)->data);
	if ((*current))
		free((*current));
	(*current) = NULL;
}

t_tree	*redirect(t_tree **tree, t_link_list **head,
	t_link_list **current, int *error)
{
	t_tree	*tree_current;

	tree_current = get_tree(tree);
	if (!tree_current)
		*error = 1;
	else
		tree_current->type = (*current)->type;
	if ((*current)->next && tree_current)
	{
		tree_current->left = get_node((*current)->next);
		if (!tree_current->left)
			*error = 1;
	}
	if ((*current)->prev)
		update_redirect_prev(head, current);
	else
		update_redirect_no_prev(head, current);
	free_current_redirect(current);
	*current = *head;
	return (*tree);
}
