/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:22:40 by sangminpark       #+#    #+#             */
/*   Updated: 2023/01/12 18:17:12 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "../minishell.h"

//t_token	*ft_pipe_func(t_token *tree, t_scmd *cmd, char *line);
t_token	*ft_parse(char *line, t_token *tree, t_scmd *cmd, char **env);
int		env_size(char *line);

//ft_parser_util02
char	*ft_check_env(char *line, char **environ);
int		file_name_size(char *str);
t_token	*is_redirects_func(t_token *tree, char *str);

//ft_parser_util
char	*fts_strdup_len(const char *str, int len);
t_token	*ft_cmd_func(t_token *tree, char *str);
int		is_quotes_set(char str, int quotes);
int		is_space(char str);
char	*file_name(char *str);

//ft_tree_util
void	ft_free_token(t_token *token);
void	print_tree(t_token *tree);
char	**quotes_func(char **argv);
int		ft_itoa_len(long long n);
int		file_name_size(char *str);
t_token	*is_redirects_func(t_token *tree, char *str);
int		env_size_len(t_scmd *cmd, char *line);

//ft_tree
t_token	*new_node(char *str, int type);
t_token	*insert_pipe_node(t_token *node, char *str, int type);
t_token	*insert_red_node(t_token *node, char *str, int type);
t_token	*insert_scmd_node(t_token *node, char *str, int type);
void	print_tree(t_token *tree);

//libft
char	*fts_strjoin(char *s1, char s2, int j);
char	*fts_strjoin2(char *s1, char *s2);
size_t	fts_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*fts_strdup(const char *s1);

//ft_split
char	*ft_strndup(const char *s, size_t n);
char	**ft_split(char const *s, char c);
char	**ft_freeall(char **list);

#endif