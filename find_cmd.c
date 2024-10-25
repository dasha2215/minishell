/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:18:34 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 19:31:05 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_absolute_path(char *cmd)
{
	char	*tmp;

	if (access(cmd, X_OK) == 0)
	{
		tmp = ft_strdup(cmd);
		if (!tmp)
			perror("minishell: malloc");
		return (tmp);
	}
	standard_error(NULL, cmd);
	return (NULL);
}

char	*get_command_path(char *cmd, char **envp)
{
	char	*tmp;
	char	*paths;
	char	**path_list;

	if (ft_strchr(cmd, '/'))
		return (check_absolute_path(cmd));
	paths = get_all_paths(envp, cmd);
	if (!paths)
		return (NULL);
	path_list = ft_split(paths, ':');
	if (!path_list)
	{
		perror("minishell: malloc");
		return (NULL);
	}
	tmp = ft_strjoin("/", cmd);
	if (!tmp)
	{
		perror("minishell: malloc");
		return (NULL);
	}
	tmp = find_command(cmd, tmp, path_list);
	free_arr(path_list);
	return (tmp);
}

char	*find_command(char *cmd, char *tmp, char **path_list)
{
	char	*path;
	int		i;

	i = -1;
	while (path_list[++i])
	{
		path = ft_strjoin(path_list[i], tmp);
		if (!path)
		{
			perror("minishell: malloc");
			free(tmp);
			return (NULL);
		}
		if (access(path, X_OK) == 0)
		{
			free(tmp);
			return (path);
		}
		free(path);
	}
	free(tmp);
	custom_error(cmd, NULL, "command not found");
	return (0);
}

char	*get_all_paths(char **envp, char *cmd)
{
	char	*paths;
	int		i;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!paths)
	{
		custom_error(cmd, NULL, "command not found");
		return (NULL);
	}
	return (paths);
}
