/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:44:15 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 19:55:16 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_vars(t_var *envp_list)
{
	int	count;

	count = 0;
	while (envp_list)
	{
		if (envp_list->exported)
			count++;
		envp_list = envp_list->next;
	}
	return (count);
}

void	fill_var(char **var, char *name, char *value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*var = malloc(ft_strlen(name) + ft_strlen(value) + 4);
	if (!(*var))
	{
		perror("minishell: malloc");
		return ;
	}
	while (name[i])
	{
		(*var)[i] = name[i];
		i++;
	}
	(*var)[i++] = '=';
	while (value[j])
		(*var)[i++] = value[j++];
	(*var)[i] = '\0';
}

char	**init_envp(t_var *envp_list, int *size)
{
	char	**new_envp;

	*size = count_vars(envp_list);
	new_envp = malloc((*size + 1) * sizeof(char *));
	if (!new_envp)
	{
		perror("minishell: malloc");
		return (NULL);
	}
	return (new_envp);
}

char	**build_envp(t_var *envp_list)
{
	char	**new_envp;
	int		size;
	int		i;

	i = 0;
	new_envp = init_envp(envp_list, &size);
	if (!new_envp)
		return (NULL);
	while (i < size)
	{
		while (envp_list->exported == 0)
			envp_list = envp_list->next;
		fill_var(&new_envp[i], envp_list->name, envp_list->value);
		if (!new_envp[i])
		{
			free_arr(new_envp);
			return (NULL);
		}
		i++;
		envp_list = envp_list->next;
	}
	new_envp[i] = 0;
	return (new_envp);
}
