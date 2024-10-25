/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:39:54 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 18:58:37 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_paths(char *path, t_var **envp_list)
{
	t_var	*old_node;
	t_var	*pwd_node;

	old_node = get_var_pointer("OLDPWD", envp_list);
	pwd_node = get_var_pointer("PWD", envp_list);
	free(old_node->value);
	old_node->value = pwd_node->value;
	if (ft_strncmp(path, "/", 1) == 0 && (!(ft_strlen(path) >= 2
				&& ft_strncmp(path, "/.", 2) == 0)))
		pwd_node->value = path;
	else
	{
		free(path);
		pwd_node->value = system_pwd();
		if (!pwd_node->value)
			return (1);
	}
	return (0);
}

char	*init_new_path(char *path, int *i, int *j,
			t_var *envp_list)
{
	char	*home;
	char	*new_path;

	if (path[0] == '~')
	{
		home = get_env_var("HOME", envp_list);
		if (!home)
		{
			custom_error("cd", NULL, "HOME not set");
			return (NULL);
		}
		new_path = malloc(ft_strlen(path) + ft_strlen(home) + 1);
		if (!new_path)
			return (NULL);
		ft_strlcpy(new_path, home, ft_strlen(home) + 1);
		*j = ft_strlen(home);
		*i = 1;
		return (new_path);
	}
	new_path = malloc(ft_strlen(path) + 1);
	if (!new_path)
		return (NULL);
	*i = 0;
	*j = 0;
	return (new_path);
}

void	build_new_path(char *path, char *new_path, int *i, int *j)
{
	while (path[*i])
	{
		if (*i == 0 && path[*i] == '/')
		{
			new_path[(*j)++] = path[(*i)++];
			if (path[*i] && path[*i] == '/' && path[(*i) + 1] != '/')
				new_path[(*j)++] = path[(*i)++];
			else
			{
				while (path[*i] == '/')
					(*i)++;
			}
		}
		else if (path[*i] == '/' && (path[(*i) - 1] == '/'
				|| new_path[*j] == '/'))
			(*i)++;
		else
			new_path[(*j)++] = path[(*i)++];
		new_path[*j] = '\0';
	}
}

char	*construct_path(char *path, t_var *envp_list)
{
	char	*new_path;
	int		i;
	int		j;

	new_path = init_new_path(path, &i, &j, envp_list);
	if (!new_path)
		return (NULL);
	build_new_path(path, new_path, &i, &j);
	new_path[j] = '\0';
	return (new_path);
}

char	*get_home(t_var *envp_list)
{
	char	*home;
	char	*path;

	home = get_env_var("HOME", envp_list);
	if (!home)
	{
		custom_error("cd", NULL, "HOME not set");
		return (NULL);
	}
	path = ft_strdup(get_env_var("HOME", envp_list));
	if (!path)
	{
		perror("minishell: malloc");
		return (NULL);
	}
	return (path);
}

int	builtin_cd(char **cmd, t_var **envp_list)
{
	char	*path;

	path = NULL;
	if (cmd[1] && cmd[2])
	{
		custom_error("cd", NULL, "too many arguments");
		return (1);
	}
	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
		path = get_home(*envp_list);
	else
		path = construct_path(cmd[1], *envp_list);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		standard_error("cd", path);
		free(path);
		return (1);
	}
	return (update_paths(path, envp_list));
}
