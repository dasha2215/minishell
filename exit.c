/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:40:56 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 12:40:57 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate_exec_state(t_exec_state *state)
{
	if (!state)
		return ;
	if (state->stdin_copy != -1)
		close(state->stdin_copy);
	if (state->stdout_copy != -1)
		close (state->stdout_copy);
	free(state);
	state = NULL;
}

int	is_numeric(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

void	builtin_exit(char **cmd, t_tree *tree, t_var *envp_list,
		t_exec_state *state)
{
	int	exit_status;

	printf("exit\n");
	if (cmd && cmd[1] && cmd[2])
	{
		custom_error("exit", NULL, "too many arguments");
		exit_status = 1;
	}
	if (cmd && cmd[1])
	{
		if (is_numeric(cmd[1]))
			exit_status = ft_atoi(cmd[1]);
		else
		{
			custom_error("exit", cmd[1], "numeric argument required");
			exit_status = 2;
		}
	}
	else
		exit_status = state->status;
	free_arr(cmd);
	free_all(tree, envp_list, state);
	exit(exit_status);
}
