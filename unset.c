/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:42:08 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 20:07:08 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_to_remove(char **cmd, char *var)
{
	int	len;
	int	i;

	i = 0;
	while (cmd[i])
	{
		len = ft_strlen(cmd[i]);
		if (ft_strncmp(var, cmd[i], len) == 0 && var[len] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	remove_var(t_var **envp_list, char *cmd)
{
	t_var	*current;
	t_var	*prev;
	t_var	*del;

	current = *envp_list;
	while (current)
	{
		if (ft_strcmp(current->name, cmd) == 0 && current->exported == 1)
		{
			del = current;
			if (prev)
				prev->next = current->next;
			else
				*envp_list = current->next;
			free_envp_node(del);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	builtin_unset(char **cmd, t_var **envp_list)
{
	int		i;

	i = 1;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		if (!verify_var_name(cmd[i], cmd[i], "unset"))
			return (1);
		remove_var(envp_list, cmd[i]);
		i++;
	}
	return (0);
}
