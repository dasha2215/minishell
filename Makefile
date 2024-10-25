NAME = minishell

# SRC_DIR = src
# SRC_FILES = main.c
SRC = execute.c find_cmd.c get_next_line.c builtins.c export.c unset.c \
		parse_envp.c build_envp.c free_memory.c main.c parse_cmd.c \
		parse_cmd_utils.c exit_utils.c redirections.c execute_utils.c \
		execute_pipes.c envp.c cd.c echo.c pwd.c env.c exit.c \
		parse_list.c merge_and_replace.c debug.c list_utils.c link_list.c \
		free_list.c parse_tree.c parse_tree_redirect.c parse_tree_utils.c \
		heredoc.c pain.c
# execute_utils.c 
OBJ = $(SRC:.c=.o)
HEADER = minishell.h

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

MYLIB_DIR = ../libft
MYLIB = $(MYLIB_DIR)/libft.a

all: $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(MYLIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MYLIB) -lreadline

$(MYLIB):
	@make -C $(MYLIB_DIR)

clean:
	$(RM) $(OBJ)
	@make clean -C $(MYLIB_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(MYLIB_DIR)

re: fclean all

.PHONY: all clean fclean re
