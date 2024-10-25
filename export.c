/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:00 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 12:41:01 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_value(char **target, const char *new_value)
{
	free(*target);
	if (new_value)
	{
		*target = ft_strdup(new_value);
		if (!*target)
			perror("minishell: malloc");
	}
	else
		*target = NULL;
}

int	update_var(t_var **envp_list, char *var)
{
	t_var	*current;
	char	*equals;
	int		name_len;

	current = *envp_list;
	equals = ft_strchr(var, '=');
	if (!equals)
		name_len = ft_strlen(var);
	else
		name_len = equals - var;
	while (current)
	{
		if (ft_strncmp(current->name, var, name_len) == 0
			&& current->name[name_len] == '\0' && current->exported == 1)
		{
			if (equals)
				update_value(&(current->value), equals + 1);
			else
				update_value(&(current->value), NULL);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	add_var(t_var **envp_list, char *var)
{
	t_var	*current;

	current = (*envp_list);
	while (current->next)
		current = current->next;
	current->next = construct_var_node();
	if (!current->next)
	{
		perror("minishell: malloc");
		return ;
	}
	current = current->next;
	if (!parse_var(&current, var))
	{
		perror("minishell: malloc");
		return ;
	}
	current->exported = 1;
}

int	builtin_export(char **cmd, t_var **envp_list)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
	{
		print_vars(*envp_list);
		return (0);
	}
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
		{
			if (!verify_var(cmd[i]))
				return (1);
		}
		else
		{
			if (!verify_var_name(cmd[i], cmd[i], "export"))
				return (1);
		}
		if (!update_var(envp_list, cmd[i]))
			add_var(envp_list, cmd[i]);
		i++;
	}
	return (0);
}
