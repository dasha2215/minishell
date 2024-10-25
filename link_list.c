/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:15 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 16:23:45 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_link_list	*create_node(const char *string, int length)
{
	t_link_list	*new;

	new = (t_link_list *)malloc(sizeof(t_link_list));
	if (!new)
		return (NULL);
	new->data = ft_substr(string, 0, length);
	if (!new->data)
	{
		free(new);
		return (NULL);
	}
	new->type = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	append_node(t_link_list **head, t_link_list *new)
{
	t_link_list	*tail;

	if (!new)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		tail = *head;
		while (tail->next)
			tail = tail->next;
		tail->next = new;
		new->prev = tail;
	}
}

t_link_list	*append_last_node(t_link_list **head, const char **start,
				const char **end)
{
	t_link_list	*new_node;

	new_node = create_node(*start, *end - *start);
	if (!new_node)
	{
		free_link_list(head, NULL, "Malloc Failed");
		return (NULL);
	}
	append_node(head, new_node);
	return (*head);
}

t_type	get_delimiter(const char *delimiter, int length)
{
	if (length == 1)
	{
		if (delimiter[0] == '|')
			return (PIPE);
		if (delimiter[0] == '>')
			return (GREATER);
		if (delimiter[0] == '<')
			return (LESS);
		if (delimiter[0] == ' ')
			return (-1);
	}
	else if (length == 2)
	{
		if (ft_strncmp(delimiter, ">>", 2) == 0)
			return (DGREATER);
		if (ft_strncmp(delimiter, "<<", 2) == 0)
			return (DLESS);
	}
	return (-2);
}

t_link_list	*create_delimiter(const char *delimiter, int length)
{
	t_link_list	*new;

	new = (t_link_list *)malloc(sizeof(t_link_list));
	if (!new)
		return (NULL);
	new->data = ft_substr(delimiter, 0, length);
	if (!new->data)
	{
		free(new);
		return (NULL);
	}
	new->type = get_delimiter(delimiter, length);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
