/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:40:17 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 18:19:51 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_redirections(t_tree *tree, t_var **envp_list, t_exec_state *state)
{
	if (tree->left && tree->type == LESS)
		state->status = redirect_input(tree, NULL);
	else if (tree->left && tree->type == DLESS)
		redirect_heredoc(tree, envp_list, state);
	else if (tree->left && tree->type == GREATER)
		state->status = redirect_output(tree, NULL);
	else if (tree->left && tree->type == DGREATER)
		state->status = redirect_output_append(tree, NULL);
	else
		return (0);
	return (1);
}

int	execute_pipeline(t_tree *tree, t_var **envp_list, t_exec_state *state,
	int pid[MAX_PIDS])
{
	int	is_pipe;
	int	i;

	is_pipe = -1;
	i = 0;
	signal(SIGINT, print_new_line);
	while (tree)
	{
		execute_redirections(tree, envp_list, state);
		if (tree->type == PIPE)
			pid[i++] = execute_pipe(tree, envp_list, state, &is_pipe);
		else if (tree && tree->type == CMD)
		{
			if (is_pipe == 1)
				pid[i++] = execute_last(tree, tree->data, envp_list, state);
			else if (!is_builtin(tree->data, tree, envp_list, state))
				pid[i++] = execute_last(tree, tree->data, envp_list, state);
		}
		if (check_pipeline_status(&tree, state->status, &is_pipe) == -1)
			return (i);
	}
	close(STDIN_FILENO);
	return (i);
}

void	wait_for_children(int pid[MAX_PIDS], int num,
		t_exec_state *state)
{
	int	i;

	i = 0;
	if (num == 0)
		return ;
	while (i < num)
	{
		if (pid[i] != -1)
			waitpid(pid[i], &(state->status), 0);
		i++;
	}
	capture_status(&(state->status));
}

int	create_fd_copies(t_exec_state *state)
{
	state->stdin_copy = dup(STDIN_FILENO);
	if (state->stdin_copy == -1)
	{
		perror("minishell: dup stdin");
		return (1);
	}
	state->stdout_copy = dup(STDOUT_FILENO);
	if (state->stdout_copy == -1)
	{
		perror("minishell: dup stdout");
		close(state->stdin_copy);
		state->stdin_copy = -1;
		return (1);
	}
	return (0);
}

void	execute(t_tree *tree, t_var **envp_list, t_exec_state *state)
{
	int		pid[MAX_PIDS];
	int		num_pids;

	signal(SIGINT, print_new_line);
	signal(SIGQUIT, SIG_IGN);
	if (create_fd_copies(state) != 0)
		return ;
	state->status = 0;
	num_pids = execute_pipeline(tree, envp_list, state, pid);
	wait_for_children(pid, num_pids, state);
	update_status(envp_list, state->status);
	reset_stdin_stdout(state);
}
