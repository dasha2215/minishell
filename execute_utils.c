/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:40:12 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 20:08:20 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	capture_status(int *status)
{
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else
		*status = 1;
}

void	update_status(t_var **envp_list, int status)
{
	char	*exit_status;
	t_var	*current;

	exit_status = ft_itoa(status);
	if (!exit_status)
	{
		perror("minishell: malloc");
		free(exit_status);
		return ;
	}
	current = *envp_list;
	while (current)
	{
		if (ft_strcmp(current->name, "exit_status") == 0
			&& current->exported == 0)
		{
			free(current->value);
			current->value = exit_status;
			return ;
		}
		current = current->next;
	}
	free(exit_status);
}

int	create_pipe(int fds[2], int *status)
{
	if (pipe(fds) == -1)
	{
		perror("minishell: pipe");
		*status = 1;
		return (1);
	}
	return (0);
}

int	empty_pipe(void)
{
	int	fds[2];

	if (pipe(fds) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	close(fds[1]);
	return (redirect_input(NULL, &fds[0]));
}

int	check_pipeline_status(t_tree **tree, int status, int *is_pipe)
{
	if (status == 0)
	{
		*tree = (*tree)->right;
		return (0);
	}
	while (*tree)
	{
		if ((*tree)->type == PIPE)
		{
			*is_pipe = 1;
			*tree = (*tree)->right;
			if (empty_pipe() != 0)
				return (-1);
			break ;
		}
		*tree = (*tree)->right;
	}
	return (1);
}
