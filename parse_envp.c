/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:46 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 20:07:33 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*destroy_envp_list(t_var *list)
{
	perror("minishell: malloc");
	free_envp_list(list);
	return (NULL);
}

t_var	*construct_var_node(void)
{
	t_var	*node;

	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->name = NULL;
	node->value = NULL;
	node->exported = -1;
	node->next = NULL;
	return (node);
}

char	*update_shell_level(char *level)
{
	int		lv;

	lv = ft_atoi(level);
	lv++;
	return (ft_itoa(lv));
}

int	parse_var(t_var **node, char *var)
{
	char	*equals;
	int		len;

	equals = ft_strchr(var, '=');
	if (!equals)
	{
		(*node)->name = ft_strdup(var);
		if (!(*node)->name)
			return (0);
		return (1);
	}
	len = equals - var;
	(*node)->name = ft_substr(var, 0, len);
	if (!(*node)->name)
		return (0);
	if (ft_strcmp((*node)->name, "SHLVL") == 0)
		(*node)->value = update_shell_level(equals + 1);
	else
		(*node)->value = ft_strdup(equals + 1);
	if (!(*node)->value)
		return (0);
	return (1);
}

t_var	*create_envp_list(char **envp)
{
	t_var	*list;
	t_var	*current;
	int		i;

	i = -1;
	list = construct_var_node();
	if (!list)
		return (NULL);
	current = list;
	while (envp[++i])
	{
		if (!parse_var(&current, envp[i]))
			return (destroy_envp_list(list));
		current->exported = 1;
		if (envp[i + 1])
		{
			current->next = construct_var_node();
			if (!current->next)
				return (destroy_envp_list(list));
			current = current->next;
		}
	}
	if (!add_exit_status(current))
		return (destroy_envp_list(list));
	return (list);
}
