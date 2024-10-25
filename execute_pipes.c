/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:40:08 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 15:50:12 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipe(t_tree *tree, t_var **envp_list,
			t_exec_state *state, int *is_pipe)
{
	int	pid;

	pid = -1;
	if (tree->type == PIPE)
	{
		if (tree->left)
			pid = execute_cmd(tree, tree->left->data, envp_list, state);
		else
			state->status = empty_pipe();
		*is_pipe = 1;
	}
	return (pid);
}

int	child_process(char *input_cmd, t_var *envp_list)
{
	char	**cmd;
	char	**envp;
	char	*cmd_path;

	envp = build_envp(envp_list);
	if (!envp)
		return (1);
	cmd = parse_cmd(input_cmd, envp_list);
	if (!cmd)
	{
		perror("minishell: malloc");
		free_arr(envp);
		return (1);
	}
	cmd_path = get_command_path(cmd[0], envp);
	if (!cmd_path)
	{
		free_child(envp, cmd, NULL);
		return (127);
	}
	execve(cmd_path, cmd, envp);
	perror("minishell: execve");
	free_child(envp, cmd, cmd_path);
	return (1);
}

int	execute_cmd(t_tree *tree, char *input_cmd,
			t_var **envp_list, t_exec_state *state)
{
	int		fds[2];
	int		status;
	pid_t	pid;

	if (create_pipe(fds, &(state->status)) != 0)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		syserror_fork(fds, &(state->status));
		return (-1);
	}
	if (pid == 0)
	{
		redirect_output(NULL, &fds[1]);
		close(fds[0]);
		if (!is_builtin(input_cmd, tree, envp_list, state))
			state->status = child_process(input_cmd, *envp_list);
		status = state->status;
		free_all(tree, *envp_list, state);
		exit(status);
	}
	close(fds[1]);
	redirect_input(NULL, &fds[0]);
	return (pid);
}

int	execute_last(t_tree *tree, char *input_cmd,
			t_var **envp_list, t_exec_state *state)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		syserror_fork(NULL, &(state->status));
		return (-1);
	}
	if (pid == 0)
	{
		if (!is_builtin(input_cmd, tree, envp_list, state))
			state->status = child_process(input_cmd, *envp_list);
		status = state->status;
		free_all(tree, *envp_list, state);
		exit(status);
	}
	return (pid);
}

void	free_child(char **envp, char **cmd, char *cmd_path)
{
	if (envp)
		free_arr(envp);
	if (cmd)
		free_arr(cmd);
	if (cmd_path)
		free(cmd_path);
}
