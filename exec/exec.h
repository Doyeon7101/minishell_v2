/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:38 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 14:45:07 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

// redirection.c
void	search_tree(t_token *node, t_exec *exec, char **env, int *sucess);

// exec.c
int		execute_rdr(t_rdr *node, t_exec *data);
void	check_nextpipe(t_token *node, t_exec *exec);
void	with_fork(t_cmd *node, t_exec *data, char **env);

//excute_cmd.c
void	execute_simplecmd(t_cmd *node, t_exec *data, char **env);
void	execute_cmd(t_cmd *node, char **environ);
t_bool	execute_builtin(t_cmd *node, t_exec *data, char **env);

//execute_path2.c
t_ftype	check_ftype(char *path_cmd);
char	*join_path(char *path, char *cmd);

//setting.c
void	update_fd(t_exec *data);
void	set_fd(t_exec *data);

//exit.c
void	exit_msg(int exit_status, int fd, char *msg);

// utils.c
int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_alert_calloc(size_t count, size_t size);
int		ft_strlcat(char *dst, char *src, size_t dstsize);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin3(char *s1, char *s2);
char	*ft_strjoin2(char *s1, char *s2);
char	*get_value_with_key(char *key, char **environ);
void	*safe_alloc(size_t cnt, size_t size);
int		ftd_strcmp(char *s1, char *s2);
int		ftd_strncmp(const char *s1, const char *s2, size_t n);

//builtin.c
void	ft_echo(char **argv, t_exec *data);
void	ft_pwd(t_exec *data);
void	ft_cd(char **argv, t_exec *data, char **env);
void	ft_env(t_exec *data, char **environ, t_cmd *node);
void	ft_export(char **argv, t_exec *data, char **environ);
int		ft_unset(char *str, char **envp);
int		ft_exit(char **argv);
int		print_export(char **envp, t_exec *data);
int		check_env(char *str, char *envp);

//builtin_utils
size_t	ft_strlen2(char *s);
char	*ft_strdup(char *s1);

#endif