/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:50:50 by sangmipa          #+#    #+#             */
/*   Updated: 2023/01/14 14:48:57 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

t_token	*ft_pipe_func(t_token *tree, char *str, char *line)
{
	if (line[1] == '|')
		printf("argv error:||\n");
	tree = insert_pipe_node(tree, "|", T_PIPE);
	tree = ft_cmd_func(tree, str);
	return (tree);
}

t_scmd	*parse_free(t_scmd *cmd)
{
	free(cmd->str);
	free(cmd);
	cmd = malloc(sizeof(t_scmd));
	cmd->quotes = 0;
	cmd->cnt = 0;
	cmd->str = 0;
	return (cmd);
}

t_token	*non_string(t_token *tree, t_scmd *cmd, char *line)
{
	if (cmd->quotes != 0)
		return (0);
	else if (cmd->str != NULL)
	{
		if (cmd->cnt == 1)
			tree = ft_pipe_func(tree, cmd->str, line);
		else
			tree = ft_cmd_func(tree, cmd->str);
		return (tree);
	}
	return (0);
}

char	*str_joins(t_scmd *cmd)
{
	if (fts_strlen(cmd->env) == 1)
		return (fts_strjoin(cmd->str, cmd->env[0], 0));
	else
		return (fts_strjoin2(cmd->str, cmd->env));
}

t_token	*ft_parse(char *line, t_token *tree, t_scmd *cmd, char **env)
{
	while (*line)
	{
		cmd->quotes = is_quotes_set(*line, cmd->quotes);
		if (*line == '|' && cmd->quotes == 0 && cmd->str != 0)
		{
			tree = ft_pipe_func(tree, cmd->str, line);
			cmd->str = 0;
			cmd->cnt = 1;
		}
		else if (env_size_len(cmd, line) == 1)
		{
			if (ft_check_env(line, env) != 0)
			{
				cmd->env = ft_check_env(line, env);
				cmd->str = str_joins(cmd);
			}
			line += env_size(line);
		}
		else
			cmd->str = fts_strjoin(cmd->str, line[0], 1);
		line++;
	}
	tree = non_string(tree, cmd, line);
	return (tree);
}
