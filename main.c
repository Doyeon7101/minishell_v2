/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:25 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 12:46:26 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec(t_exec *data)
{
	data->pipe_cnt = 0;
	data->is_pipe = 0;
	data->next_pipe = FALSE;
	data->prev_pipe = FALSE;
	data->pipe[READ_END] = STDIN_FILENO;
	data->pipe[WRITE_END] = STDOUT_FILENO;
	data->r_fd[INPUT] = STDIN_FILENO;
	data->r_fd[OUTPUT] = STDOUT_FILENO;
}

void	init_signal_exec(t_exec *data, t_token **tree)
{
	initialize_signal();
	init_exec(data);
	*tree = NULL;
}

void	check_vaild_execute(t_exec *data, t_token *tree, \
						char **env, t_scmd *cmd)
{
	int	ret;

	ret = 1;
	if (cmd->quotes != 0)
	{
		printf("ERROR: quotes error\n");
		return ;
	}
	check_syntax(tree, &ret, data);
	if (ret == -1)
		printf("ERROR: fail to syntax analysis\n");
	else if (tree)
		search_tree(tree, data, env, &ret);
}

void	prompt(char **env, t_exec *data, t_scmd *cmd)
{
	char	*line;
	t_token	*tree;
	int		ret;

	g_rtn = 0;
	while (1)
	{
		ret = 1;
		init_signal_exec(data, &tree);
		line = readline("parkshell$ ");
		check_exit_sigterm(line);
		if (is_line_spaces(line))
			;
		else
		{
			tree = ft_parse(line, tree, cmd, env);
			check_vaild_execute(data, tree, env, cmd);
			cmd = parse_free(cmd);
			ft_free_token(tree);
		}
		if (ftd_strcmp(line, ""))
			add_history(line);
		free(line);
		line = NULL;
	}
}

int	main(void)
{
	extern char	**environ;
	t_exec		data;
	t_scmd		*cmd;

	cmd = malloc(sizeof(t_cmd));
	print_gard();
	prompt(environ, &data, cmd);
	return (0);
}
