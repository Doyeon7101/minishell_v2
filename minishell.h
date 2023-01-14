/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:04:08 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 12:12:17 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_END   0
# define WRITE_END  1
# define INPUT 0
# define OUTPUT 1
# define FAIL 1
# define SUCESS 0 
# define ANSI_GREEN "\x1b[32m"
# define ANSI_RESET "\x1b[0m"

# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

int	g_rtn;

typedef enum e_type
{
	T_AQW,
	T_PIPE,
	T_CMD,
	T_RED,
	T_REDS,
	T_SCMD
}	t_type;

typedef enum e_ftype
{
	F_NOTFOUND,
	F_DIR,
	F_FILE
}	t_ftype;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_rdr
{
	char	*type;
	char	*file_name;
}	t_rdr;

typedef struct s_cmd
{
	char	*file_path;
	char	**argv;
}	t_cmd;

typedef struct s_exec
{
	int		pipe[2];
	int		fd[2];
	int		r_fd[2];
	pid_t	wpid;
	int		pipe_cnt;
	int		is_pipe;
	t_bool	next_pipe;
	t_bool	prev_pipe;
}	t_exec;

typedef struct s_token
{
	t_type			type;
	t_rdr			*rdr;
	t_cmd			*cmd;
	char			*str;
	void			*data;
	struct s_token	*left;
	struct s_token	*right;
}	t_token;

typedef struct s_scmd
{
	int		cnt;
	int		quotes;
	char	*str;
	char	*env;
	int		i;
	int		k;
	int		save;
}		t_scmd;

t_token		*ft_parse(char *line, t_token *tree, t_scmd *cmd, char **env);
void		ft_free_token(t_token *token);
t_scmd		*parse_free(t_scmd *cmd);
void		search_tree(t_token *node, t_exec *exec, char **env, int *sucess);
void		print_tree(t_token *tree);
void		print_gard(void);
void		*ft_alert_calloc(size_t count, size_t size);
int			ftd_strcmp(char *s1, char *s2);
void		check_syntax(t_token *tree, int *ret, t_exec *data);

// signal.c
void		sigint_c(int signum);
void		sigint_p(int signum);
void		initialize_signal(void);
void		check_exit_sigterm(char *line);

#endif