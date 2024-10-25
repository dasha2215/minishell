/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:39:50 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 12:39:52 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **cmd, t_tree *tree,
			t_var **envp_list, t_exec_state *state)
{
	if (strcmp(cmd[0], "echo") == 0)
		state->status = builtin_echo(cmd);
	else if (strcmp(cmd[0], "cd") == 0)
		state->status = builtin_cd(cmd, envp_list);
	else if (strcmp(cmd[0], "pwd") == 0)
		state->status = builtin_pwd(*envp_list);
	else if (strcmp(cmd[0], "export") == 0)
		state->status = builtin_export(cmd, envp_list);
	else if (strcmp(cmd[0], "unset") == 0)
		state->status = builtin_unset(cmd, envp_list);
	else if (strcmp(cmd[0], "env") == 0)
		state->status = builtin_env(*envp_list);
	else if (strcmp(cmd[0], "exit") == 0)
		builtin_exit(cmd, tree, *envp_list, state);
	else
		return (0);
	return (1);
}

int	is_builtin(char	*line, t_tree *tree, t_var **envp_list, t_exec_state *state)
{
	char	**cmd;
	int		is_builtin;

	cmd = parse_cmd(line, *envp_list);
	if (!cmd)
	{
		state->status = 1;
		return (1);
	}
	is_builtin = execute_builtin(cmd, tree, envp_list, state);
	free_arr(cmd);
	if (!is_builtin)
		return (0);
	return (1);
}
