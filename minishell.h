/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:42:47 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 19:31:30 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <ctype.h>
# include <term.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifndef ARG_MAX
#  define ARG_MAX 1048576
# endif

# ifndef MAX_ARGS
#  define MAX_ARGS 256
# endif

# ifndef MAX_PIDS
#  define MAX_PIDS 2048
# endif

typedef enum e_type
{
	CMD,
	FFILE,
	PIPE,
	GREATER,
	LESS,
	DGREATER,
	DLESS,
	NONE
}	t_type;

typedef struct s_link_list
{
	char				*data;
	int					type;
	struct s_link_list	*prev;
	struct s_link_list	*next;
}	t_link_list;

typedef struct s_tree
{
	int				type;
	char			*data;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_var
{
	char			*name;
	char			*value;
	int				exported;
	struct s_var	*next;
}	t_var;

typedef struct s_exec_state
{
	int	stdin_copy;
	int	stdout_copy;
	int	status;
}	t_exec_state;

char		*get_next_line(int fd);
int			redirect_input(t_tree *tree, int *fd);
int			redirect_output(t_tree *tree, int *fd);
int			redirect_output_append(t_tree *tree, int *fd);
int			redirect_heredoc(t_tree *tree, t_var **envp_list,
				t_exec_state *state);
void		capture_status(int *status);
int			execute_cmd(t_tree *tree, char *input_cmd, t_var **envp_list,
				t_exec_state *state);
void		execute(t_tree *tree, t_var **envp_list, t_exec_state *state);
int			execute_pipe(t_tree *tree, t_var **envp_list,
				t_exec_state *state, int *is_pipe);
int			execute_last(t_tree *tree, char *input_cmd,
				t_var **envp_list, t_exec_state *state);
int			check_pipeline_status(t_tree **tree, int status, int *is_pipe);
int			empty_pipe(void);
int			create_pipe(int fds[2], int *status);
void		capture_status(int *status);
void		reset_stdin_stdout(t_exec_state *state);
t_tree		*construct_node(void);
t_tree		*create_tree(void);
void		command_not_found(char *cmd);
void		file_not_found(char *file);
void		put_error(char *function);
void		free_arr(char **arr);
void		free_tree(t_tree *tree);
char		*get_command_path(char *cmd, char **envp);
char		*find_command(char *cmd, char *tmp, char **path_list);
char		*get_all_paths(char **envp, char *cmd);
char		*get_variable_value(const char *var, t_var *envp_list);
t_var		*get_var_pointer(char *var, t_var **envp_list);
char		*get_env_var(char *var_name, t_var *envp_list);
int			is_builtin(char	*line, t_tree *tree,
				t_var **envp_list, t_exec_state *state);
char		**parse_cmd(char *line, t_var *envp_list);
void		add_argument(char **args, int *index, char *arg);
void		initialize_cmd_parsing(int *arg_index, int *in_single_quote,
				int *in_double_quote, int *args_index);
int			toggle_quotes(char input, int *in_single_quote,
				int *in_double_quote);
void		add_cmd_argument(char *arg, int *arg_index, char **args,
				int *args_index);
void		add_char_to_arg(char *arg, char input, int *arg_index);
int			builtin_echo(char **cmd);
int			builtin_cd(char **cmd, t_var **envp_list);
int			builtin_pwd(t_var *envp_list);
int			builtin_export(char **cmd, t_var **envp_list);
int			update_var(t_var **envp_list, char *var);
void		update_status(t_var **envp_list, int status);
int			verify_var(char *cmd);
int			verify_var_name(char *name, char *var, char *cmd);
int			builtin_unset(char **cmd, t_var **envp_list);
char		**build_envp(t_var *envp_list);
void		print_vars(t_var *envp_list);
int			parse_var(t_var **node, char *var);
t_var		*create_envp_list(char **envp);
void		add_var(t_var **envp_list, char *var);
int			add_exit_status(t_var *current);
t_var		*construct_var_node(void);
char		*system_pwd(void);
int			replace_user_path(char *path);
int			builtin_env(t_var *envp_list);
void		builtin_exit(char **cmd, t_tree *tree, t_var *envp_list,
				t_exec_state *state);
void		free_envp_node(t_var *node);
void		free_envp_list(t_var *envp_list);
void		free_all(t_tree *tree, t_var *envp_list, t_exec_state *state);
void		free_child(char **envp, char **cmd, char *cmd_path);
void		terminate_exec_state(t_exec_state *state);
void		custom_error(char *cmd, char *arg, char *error);
void		standard_error(char *cmd, char *arg);
void		syserror_fork(int fds[2], int *status);

//parsing part
void		init_root(t_tree **root, t_var *envp_list, t_exec_state *state);
t_link_list	*merge_and_replace_nodes(t_link_list **head);
void		process_token(t_link_list **head, const char **start,
				const char **end);
t_link_list	*create_node(const char *string, int length);
void		append_node(t_link_list **head, t_link_list *new);
t_link_list	*append_last_node(t_link_list **head, const char **start,
				const char **end);
t_type		get_delimiter(const char *delimiter, int length);
t_link_list	*create_delimiter(const char *delimiter, int length);
char		*ft_strjoin_space(const char *s1, const char *s2);
void		free_link_list(t_link_list **head, t_link_list *current, char *str);
void		print_parse_error(t_type type);

// parse tree
t_tree		*build_tree(t_link_list **head, t_tree **tree, int *error);
t_tree		*redirect(t_tree **tree, t_link_list **head,
				t_link_list **current, int *error);
t_tree		*construct_node(void);
t_tree		*get_tree(t_tree **tree);
t_tree		*get_node(t_link_list *node);

//debugging 
void		print_tree(t_tree **tree);
void		print_list(t_link_list **head);

//signal
void		signals_wait_cmd(void);
void		reset_prompt(int signo);
void		heredoc_sig(int signo);
void		print_new_line(int signo);

#endif