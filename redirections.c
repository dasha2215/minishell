/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:42:05 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 18:58:12 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_tree *tree, int *open_fd)
{
	int	fd;

	if (open_fd == NULL)
	{
		fd = open(tree->left->data, O_RDONLY);
		if (fd < 0)
		{
			standard_error(NULL, tree->left->data);
			return (1);
		}
	}
	else
		fd = *open_fd;
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_output(t_tree *tree, int *open_fd)
{
	int	fd;

	if (tree != NULL && !open_fd)
		fd = open(tree->left->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = *open_fd;
	if (fd < 0)
	{
		standard_error(NULL, tree->left->data);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_output_append(t_tree *tree, int *open_fd)
{
	int	fd;

	if (open_fd == NULL)
	{
		fd = open(tree->left->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			standard_error(NULL, tree->left->data);
			return (1);
		}
	}
	else
		fd = *open_fd;
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
