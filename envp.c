/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:40:04 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 12:40:05 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_var(char *var)
{
	char	**var_split;
	char	*key;
	char	*value;
	int		verify;

	verify = 1;
	var_split = ft_split(var, '=');
	if (!var_split)
	{
		perror("minishell: malloc");
		return (0);
	}
	key = var_split[0];
	value = var_split[1];
	if (!verify_var_name(key, var, "export"))
		verify = 0;
	if (key)
		free(key);
	if (value)
		free(value);
	if (var_split)
		free(var_split);
	return (verify);
}

int	verify_var_name(char *name, char *var, char *cmd)
{
	int	i;

	i = 1;
	if (!(name[0] >= 'a' && name[0] <= 'z')
		&& !(name[0] >= 'A' && name[0] <= 'Z')
		&& name[0] != '_')
	{
		custom_error(cmd, var, "not a valid identifier");
		return (0);
	}
	while (name[i])
	{
		if (!(name[i] >= 'a' && name[i] <= 'z')
			&& !(name[i] >= 'A' && name[i] <= 'Z')
			&& !(name[i] >= '0' && name[i] <= '9')
			&& name[i] != '_')
		{
			custom_error(cmd, var, "not a valid identifier");
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_env_var(char *var_name, t_var *envp_list)
{
	char	*var;

	var = NULL;
	while (envp_list)
	{
		if (ft_strcmp(envp_list->name, var_name) == 0)
		{
			var = envp_list->value;
			break ;
		}
		envp_list = envp_list->next;
	}
	return (var);
}

t_var	*get_var_pointer(char *var, t_var **envp_list)
{
	t_var	*current;
	int		name_len;

	current = *envp_list;
	name_len = ft_strlen(var);
	while (current)
	{
		if (ft_strncmp(current->name, var, name_len) == 0
			&& current->name[name_len] == '\0')
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	print_vars(t_var *envp_list)
{
	while (envp_list)
	{
		if (envp_list->exported == 0)
		{
			envp_list = envp_list->next;
			continue ;
		}
		if (!envp_list->value)
			printf("%s=\"\"\n", envp_list->name);
		else
			printf("%s=\"%s\"\n", envp_list->name, envp_list->value);
		envp_list = envp_list->next;
	}
}
