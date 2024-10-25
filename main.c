/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:25 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 15:04:35 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status_code;

void	reset_prompt(int signo)
{
	g_status_code = 128 + signo;
	write (2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

t_exec_state	*init_exec_state(void)
{
	t_exec_state	*state;

	state = malloc(sizeof(t_exec_state));
	if (!state)
		return (0);
	state->status = 0;
	state->stdin_copy = -1;
	state->stdout_copy = -1;
	return (state);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec_state	*state;
	t_var			*envp_list;
	t_tree			*root;

	(void)argc;
	(void)argv;
	envp_list = create_envp_list(envp);
	if (!envp_list)
		return (1);
	state = init_exec_state();
	if (!state)
	{
		free_envp_list(envp_list);
		return (1);
	}
	while (1)
	{
		root = NULL;
		init_root(&root, envp_list, state);
		if (root)
			execute(root, &envp_list, state);
		free_tree(root);
	}
	free_envp_list(envp_list);
}
