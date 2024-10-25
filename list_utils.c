/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:18 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 17:33:34 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_link_list	*handle_double(t_link_list **head,
				const char **start, const char **end)
{
	t_link_list	*new_node;
	t_link_list	*new_delimeter;

	new_node = NULL;
	new_delimeter = NULL;
	if (*end > *start)
	{
		new_node = create_node(*start, *end - *start);
		if (!new_node)
		{
			free_link_list(head, NULL, "Malloc Failed");
			return (NULL);
		}
		append_node(head, new_node);
	}
	new_delimeter = create_delimiter(*end, 2);
	if (!new_delimeter)
	{
		free_link_list(head, NULL, "Malloc Failed");
		return (NULL);
	}
	append_node(head, new_delimeter);
	*end += 2;
	*start = *end;
	return (*head);
}

static t_link_list	*handle_single(t_link_list **head,
				const char **start, const char **end)
{
	t_link_list	*new_node;
	t_link_list	*new_delimeter;

	new_node = NULL;
	new_delimeter = NULL;
	if (*end > *start)
	{
		new_node = create_node(*start, *end - *start);
		if (!new_node)
		{
			free_link_list(head, NULL, "Malloc Failed");
			return (NULL);
		}
		append_node(head, new_node);
	}
	new_delimeter = create_delimiter(*end, 1);
	if (!new_delimeter)
	{
		free_link_list(head, NULL, "Malloc Failed");
		return (NULL);
	}
	append_node(head, new_delimeter);
	*end += 1;
	*start = *end;
	return (*head);
}

static t_link_list	*handle_space(t_link_list **head,
				const char **start, const char **end)
{
	t_link_list	*new_node;

	new_node = NULL;
	if (*end > *start)
	{
		new_node = create_node(*start, *end - *start);
		if (!new_node)
		{
			free_link_list(head, NULL, "Malloc Failed");
			return (NULL);
		}
		append_node(head, new_node);
	}
	*end += 1;
	*start = *end;
	return (*head);
}

//static int	skip(const char *s)
//{
//	char	c;
//	int		i;

//	i = 1;
//	c = *s;
//	if (c == '\\')
//		return (i);
//	while (*(s + i) && *(s + i) != c)
//		i++;
//	if ((*s + i) != c)
//		return (i + 1);
//	return (i);
//}

static int	skip(const char *s)
{
	char	c;
	int		i;

	i = 1;
	c = *s;
	if (c == '\\')
		return (i);
	while (*(s + i) && *(s + i) != c)
		i++;
	if (*(s + i) != c)
		return (i);
	return (i + 1);
}

void	process_token(t_link_list **head, const char **start, const char **end)
{
	if (ft_strncmp(*end, ">>", 2) == 0 || ft_strncmp(*end, "<<", 2) == 0)
		*head = handle_double(head, start, end);
	else if (**end == '|' || **end == '<' || **end == '>')
		*head = handle_single(head, start, end);
	else if (**end == ' ' || **end == '\t')
		*head = handle_space(head, start, end);
	else if (**end == '"' || **end == '\'')
		*end += skip(*end);
	else
		(*end)++;
}
