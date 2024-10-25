/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_and_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:21 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 16:23:31 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_link_list	*create_merge_node(t_link_list *current, t_link_list **head)
{
	char		*new_data;
	t_link_list	*new_node;

	new_data = ft_strjoin_space(current->data, current->next->data);
	if (!new_data)
		return (NULL);
	new_node = create_node(new_data, ft_strlen(new_data));
	free(new_data);
	if (!new_node)
		return (NULL);
	new_node->prev = current->prev;
	new_node->next = current->next->next;
	if (current->prev)
		current->prev->next = new_node;
	else
		*head = new_node;
	if (current->next->next)
		current->next->next->prev = new_node;
	return (new_node);
}

static void	free_merge(t_link_list *current)
{
	free(current->next->data);
	free(current->next);
	free(current->data);
	free(current);
}

t_link_list	*merge_and_replace_nodes(t_link_list **head)
{
	t_link_list	*current;
	t_link_list	*new_node;

	if (!head || !*head)
		return (NULL);
	current = *head;
	while (current != NULL && current->next != NULL)
	{
		if (current->type == 0 && current->next->type == 0)
		{
			new_node = create_merge_node(current, head);
			if (!new_node)
			{
				free_link_list(head, NULL, "Malloc Failed");
				return (NULL);
			}
			free_merge(current);
			current = new_node;
		}
		else
			current = current->next;
	}
	return (*head);
}
