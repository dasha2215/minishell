/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:42:03 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 12:42:04 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*system_pwd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_strdup(cwd));
	else
	{
		perror("minishell: getcwd");
		return (0);
	}
	return (0);
}

int	builtin_pwd(t_var *envp_list)
{
	char	cwd[1000];
	char	*pwd;

	pwd = get_env_var("PWD", envp_list);
	if (pwd)
	{
		printf("%s\n", pwd);
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("minishell: pwd");
		return (1);
	}
	return (0);
}
