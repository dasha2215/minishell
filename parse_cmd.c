/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:41:41 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 18:04:47 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_value(const char *var, t_var *envp_list)
{
	t_var	*current;

	current = envp_list;
	while (current)
	{
		if ((ft_strcmp(var, "?")) == 0
			&& (ft_strcmp("exit_status", current->name)) == 0
			&& current->exported == 0)
			return (current->value);
		else if (current->exported && !ft_strcmp(var, current->name)
			&& (current->value) && current->exported != 0)
			return (current->value);
		current = current->next;
	}
	return ("");
}

int	handle_variable_expansion(char *arg, int *arg_index, const char **input,
		t_var *envp_list)
{
	char	var[256];
	char	*value;
	int		var_index;

	(*input)++;
	var_index = 0;
	if (**input == '?')
	{
		value = get_variable_value("?", envp_list);
		(*input)++;
	}
	else if (**input == '\0' || !(ft_isalnum(**input)) || **input == '_')
		return (0);
	else
	{
		while (**input && (ft_isalnum(**input) || **input == '_'))
			var[var_index++] = *(*input)++;
		var[var_index] = '\0';
		value = get_variable_value(var, envp_list);
	}
	while (*value)
		arg[(*arg_index)++] = *value++;
	return (1);
}

int	expand_var(char **input, char *arg, int *arg_index, t_var *envp_list)
{
	if (**input == '$')
	{
		if (handle_variable_expansion(arg, arg_index, (const char **)input,
				envp_list))
			return (1);
		else
			(*input)--;
	}
	return (0);
}

int	build_cmd(char *input, t_var *envp_list, char **args, char *arg)
{
	int	arg_index;
	int	in_single_quote;
	int	in_double_quote;
	int	args_index;

	initialize_cmd_parsing(&arg_index, &in_single_quote,
		&in_double_quote, &args_index);
	while (*input)
	{
		if (toggle_quotes(*input, &in_single_quote, &in_double_quote))
		{
			input++;
			continue ;
		}
		if (!in_single_quote && expand_var(&input, arg, &arg_index, envp_list))
			continue ;
		else if (*input == ' ' && !in_single_quote && !in_double_quote)
			add_cmd_argument(arg, &arg_index, args, &args_index);
		else
			add_char_to_arg(arg, *input, &arg_index);
		input++;
	}
	add_cmd_argument(arg, &arg_index, args, &args_index);
	args[args_index] = NULL;
	return (!(in_single_quote || in_double_quote));
}

char	**parse_cmd(char *input, t_var *envp_list)
{
	char	**args;
	char	*arg;
	int		is_valid;

	args = malloc(MAX_ARGS * sizeof(char *));
	if (!args)
		return (NULL);
	arg = malloc(ARG_MAX + 1);
	if (!arg)
	{
		free(args);
		return (NULL);
	}
	is_valid = build_cmd(input, envp_list, args, arg);
	if (!is_valid)
	{
		free(arg);
		free_arr(args);
		custom_error(NULL, NULL, "Quote not closed");
		return (NULL);
	}
	free(arg);
	return (args);
}
