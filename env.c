/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:40:01 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/10 12:40:02 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_var *envp_list)
{
	if (!envp_list)
		return (1);
	while (envp_list)
	{
		if (envp_list->exported == 1 && envp_list->value)
			printf("%s=%s\n", envp_list->name, envp_list->value);
		envp_list = envp_list->next;
	}
	return (0);
}
