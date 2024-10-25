/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:28 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 18:21:13 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_argument(char **args, int *index, char *arg)
{
	args[*index] = ft_strdup(arg);
	if (!args[*index])
		perror("minishell: malloc");
	(*index)++;
}

void	initialize_cmd_parsing(int *arg_index, int *in_single_quote,
		int *in_double_quote, int *args_index)
{
	*arg_index = 0;
	*in_single_quote = 0;
	*in_double_quote = 0;
	*args_index = 0;
}

int	toggle_quotes(char input, int *in_single_quote, int *in_double_quote)
{
	if (input == '\'')
	{
		if (!(*in_double_quote))
		{
			*in_single_quote = !(*in_single_quote);
			return (1);
		}
	}
	else if (input == '"')
	{
		if (!(*in_single_quote))
		{
			*in_double_quote = !(*in_double_quote);
			return (1);
		}
	}
	return (0);
}

void	add_cmd_argument(char *arg, int *arg_index, char **args,
		int *args_index)
{
	if (*arg_index > 0)
	{
		arg[*arg_index] = '\0';
		add_argument(args, args_index, arg);
		*arg_index = 0;
	}
}

void	add_char_to_arg(char *arg, char input, int *arg_index)
{
	arg[*arg_index] = input;
	(*arg_index)++;
}
