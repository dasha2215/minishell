/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:06 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 16:26:55 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_space(const char *s1, const char *s2)
{
	int		full_size;
	int		i;
	char	*ptr;

	i = 0;
	full_size = ft_strlen(s1) + ft_strlen(s2) + 2;
	ptr = (char *)malloc(full_size * sizeof(char));
	if (!ptr)
		return (0);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = ' ';
	i++;
	ptr[i] = '\0';
	ft_strlcat(ptr, s2, full_size);
	return (ptr);
}

void	free_link_list(t_link_list **head, t_link_list *current, char *str)
{
	t_link_list	*next;

	if (!head || !*head)
		return ;
	if (!current)
	{
		if (str)
			custom_error(NULL, NULL, str);
		else
			print_parse_error(NONE);
	}
	else
		print_parse_error(current->type);
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	*head = NULL;
}
