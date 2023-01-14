NAME = minishell
CC = gcc
CFLAGS = -Werror -Wall -Wextra 
COMFILE_FLAGS = -lreadline -L$(shell brew --prefix readline)/lib/
OBJ_FLAGS = -I$(shell brew --prefix readline)/include/ 

MAIN_SRCS = main.c \
		./exec/execute_cmd.c \
		./exec/execute_path.c \
		./exec/execute_path2.c \
		./exec/redirection.c \
		./exec/setting.c \
		./exec/utils.c \
		./exec/utils2.c \
		./exec/exec.c \
		./exec/env.c \
		./exec/exit.c \
		./exec/check_nextpipe.c \
		./parse/ft_parse.c \
		./parse/ft_parser_util.c \
		./parse/ft_parser_util02.c \
		./parse/ft_parser_util03.c \
		./parse/ft_split.c \
		./parse/ft_tree.c \
		./parse/ft_tree_util.c \
		./parse/libft.c \
		./signal/signal.c \
		./builtin_func/ft_cd.c \
		./builtin_func/ft_echo.c \
		./builtin_func/ft_env.c \
		./builtin_func/ft_pwd.c \
		./builtin_func/ft_export.c \
		./builtin_func/ft_unset.c \
		./builtin_func/ft_exit.c \
		./builtin_func/libft.c \
		./check_syntax/check_syntax.c \
		./print_gard.c

MAIN_OBJS = $(MAIN_SRCS:.c=.o)
all : $(NAME)

$(NAME) : $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(COMFILE_FLAGS) $(MAIN_OBJS) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean :
	rm -rf $(MAIN_OBJS) 

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re