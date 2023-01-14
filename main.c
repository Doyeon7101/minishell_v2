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

t_bool	is_line_spaces(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ')
			return (FALSE);
	}
	return (TRUE);
}

void	print_tree(t_token *tree)
{
	int i = 0;

	if (tree == NULL)
		return ;
	printf("%d:", tree->type);
 	if (tree->type == T_REDS)
	{
		printf("  type:%s, name:%s", tree->rdr->type, tree->rdr->file_name);
		//printf("  type:%lu, name:%lu\n", sizeof(tree->rdr->type), sizeof(tree->rdr->file_name));
	}
 	else if (tree->type == T_SCMD)
	{
		printf("  file_path:%s, ", tree->cmd->file_path);
		printf("argv:");
		while (tree->cmd->argv[i])
		{
			printf("%s ", tree->cmd->argv[i]);
			i++;
		}
		//printf("  type:%lu, name:%lu\n", sizeof(tree->cmd->file_path), sizeof(tree->cmd->argv));
	}
	printf("\n");
	print_tree(tree->left);
	print_tree(tree->right);
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
			ret = 1;
			tree = ft_parse(line, tree, cmd, env);
			// print_tree(tree);
			check_syntax(tree, &ret, data);
			if (cmd->quotes != 0)
				printf("ERROR: quotes error\n");
			else if (ret == -1)
				printf("ERROR: fail to syntax analysis\n");
			else if (tree)
				search_tree(tree, data, env, &ret);
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
