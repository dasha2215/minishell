/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:39:59 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 12:40:00 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo_n(char *option)
{
	if (ft_strncmp(option, "-n", 2) != 0)
		return (0);
	option = option + 2;
	while (*option)
	{
		if (*option && *option != 'n')
			return (0);
		option++;
	}
	return (1);
}

int	builtin_echo(char **cmd)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	while (cmd[i] && builtin_echo_n(cmd[i]))
	{
		nl = 0;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}
