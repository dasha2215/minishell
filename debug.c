/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:39:56 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 15:49:40 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_tree(t_tree **tree)
// {
// 	t_tree *current;

// 	if (!tree || !(*tree))
// 	{
// 		printf("NULL tree\n");
// 		return;
// 	}
// 	current = *tree;
// 	while (current)
// 	{
// 		if (current->left)
// 			printf("%s", current->left->data);
// 		if (current->type == PIPE)
// 			printf("|");
//// 		else if (current->type == GREATER)
//// 			printf(">");
//// 		else if (current->type == LESS)
//// 			printf("<");
//// 		else if (current->type == DGREATER)
//// 			printf(">>");
//// 		else if (current->type == DLESS)
//// 			printf("<<");
//// 		else
//// 			printf("%s", current->data);
//// 		if (current->right)
//// 			current = current->right;
//// 		else
//// 			break;
//// 	}
//// 		printf("\n");
//// }

// void print_list(t_link_list **head)
// {
// 	t_link_list *current;

// 	if (!head || !*head)
// 	{
// 		printf("list NULL\n");
// 		return;
// 	}
// 	current = *head;
// 	while (current && current->next)
// 	{
// 		printf("Data: %s, Type: %d\n", current->data, current->type);
// 		current = current->next;
// 	}
// 	printf("Data: %s, Type: %d\n", current->data, current->type);
// 	printf("================================================\n");
// 	while (current->prev)
// 	{
// 		printf("Data: %s, Type: %d\n", current->data, current->type);
// 		current = current->prev;
// 	}
// 	printf("Data: %s, Type: %d\n", current->data, current->type);
// }