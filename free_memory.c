/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:11 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 18:03:11 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp_list(t_var *envp_list)
{
	t_var	*next;

	if (!envp_list)
		return ;
	next = envp_list->next;
	while (next)
	{
		free_envp_node(envp_list);
		envp_list = next;
		next = envp_list->next;
	}
	if (envp_list)
		free_envp_node(envp_list);
	envp_list = NULL;
}

void	free_envp_node(t_var *node)
{
	if (!node)
		return ;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	if (tree->data)
		free(tree->data);
	free(tree);
	tree = NULL;
}

void	free_all(t_tree *tree, t_var *envp_list, t_exec_state *state)
{
	if (tree)
		free_tree(tree);
	if (envp_list)
		free_envp_list(envp_list);
	if (state)
		terminate_exec_state(state);
	clear_history();
}
