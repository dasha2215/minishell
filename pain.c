/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pain.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:37:06 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 18:09:24 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_stdin_stdout(t_exec_state *state)
{
	if (dup2(state->stdin_copy, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(state->stdin_copy);
		state->stdin_copy = -1;
		close(state->stdout_copy);
		state->stdout_copy = -1;
		return ;
	}
	close(state->stdin_copy);
	state->stdin_copy = -1;
	if (dup2(state->stdout_copy, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(state->stdout_copy);
		state->stdout_copy = -1;
		return ;
	}
	close(state->stdout_copy);
	state->stdout_copy = -1;
}

int	add_exit_status(t_var *current)
{
	current->next = construct_var_node();
	if (!current->next)
		return (0);
	current = current->next;
	current->name = ft_strdup("exit_status");
	if (!current->name)
		return (0);
	current->value = ft_strdup("0");
	if (!current->value)
		return (0);
	current->exported = 0;
	return (1);
}

void	print_new_line(int signo)
{
	(void)signo;
	write(1, "\n", 2);
}
