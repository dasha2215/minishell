/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:33:13 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 18:18:27 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_heredoc_fds(int pipe_fds[2])
{
	int		stdout;

	stdout = open("/dev/tty", O_WRONLY);
	if (redirect_output(NULL, &stdout) != 0)
	{
		close(pipe_fds[1]);
		exit(1);
	}
}

void	heredoc_exit(int signo)
{
	(void)signo;
	exit(EXIT_FAILURE);
}

void	get_heredoc(t_tree *tree, int pipe_fds[2],
			t_var **envp_list, t_exec_state *state)
{
	char	*line;

	signal(SIGINT, heredoc_exit);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fds[0]);
	if (!isatty(STDOUT_FILENO))
		set_heredoc_fds(pipe_fds);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, tree->left->data) == 0)
		{
			free(line);
			close(pipe_fds[1]);
			free_all(tree, *envp_list, state);
			exit(0);
		}
		write(pipe_fds[1], line, ft_strlen(line));
		write(pipe_fds[1], "\n", 1);
		free(line);
	}
}

int	redirect_heredoc(t_tree *tree, t_var **envp_list, t_exec_state *state)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe");
		state->status = 1;
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		syserror_fork(pipe_fds, &(state->status));
		return (1);
	}
	if (pid == 0)
		get_heredoc(tree, pipe_fds, envp_list, state);
	else
	{
		close(pipe_fds[1]);
		redirect_input(NULL, &pipe_fds[0]);
		waitpid(pid, &(state->status), 0);
		capture_status(&(state->status));
	}
	return (0);
}

void	heredoc_sig(int signo)
{
	(void)signo;
}
