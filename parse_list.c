/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:51 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 17:42:16 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_input(t_var *envp_list, t_exec_state *state)
{
	char	*line;

	line = readline("minishell $ ");
	if (line == NULL)
		builtin_exit(NULL, NULL, envp_list, state);
	if (line && *line)
		add_history(line);
	else
		return (NULL);
	return (line);
}

static t_link_list	*parse_string(const char *str)
{
	t_link_list	*head;
	const char	*start;
	const char	*end;

	head = NULL;
	start = str;
	end = str;
	if (!str)
		return (NULL);
	while (*end != '\0')
		process_token(&head, &start, &end);
	if (end > start)
		head = append_last_node(&head, &start, &end);
	return (head);
}

static t_link_list	*modify_file(t_link_list **head)
{
	t_link_list	*current;

	if (!head || !*head)
		return (NULL);
	current = *head;
	while (current != NULL)
	{
		if (current->prev && current->prev->type >= 3 && current->type == 0)
			current->type = 1;
		current = current->next;
	}
	return (*head);
}

static t_link_list	*check_list(t_link_list **head)
{
	t_link_list	*current;

	if (!head || !*head)
		return (NULL);
	current = *head;
	while (current)
	{
		if (current->type >= PIPE && (!current->next
				|| current->next->type == PIPE))
		{
			free_link_list(head, current->next, NULL);
			return (NULL);
		}
		if (current->type >= GREATER && (!current->next
				|| current->next->type >= PIPE))
		{
			free_link_list(head, current->next, NULL);
			return (NULL);
		}
		current = current->next;
	}
	return (*head);
}

void	init_root(t_tree **root, t_var *envp_list, t_exec_state *state)
{
	char		*input;
	t_link_list	*list;
	int			error;

	signal(SIGINT, reset_prompt);
	signal(SIGQUIT, SIG_IGN);
	input = get_input(envp_list, state);
	list = parse_string(input);
	list = modify_file(&list);
	list = merge_and_replace_nodes(&list);
	if (list && list->type == PIPE)
		free_link_list(&list, list, NULL);
	list = check_list(&list);
	error = 0;
	*root = build_tree(&list, root, &error);
	free(input);
	input = NULL;
}
