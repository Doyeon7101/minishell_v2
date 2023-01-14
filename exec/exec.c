/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:41 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 14:44:55 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	with_fork(t_cmd *node, t_exec *data, char **env)
{
	pid_t		pid;

	pid = fork();
	data->wpid = pid;
	if (pid > 0)
		update_fd(data);
	else if (pid == 0)
	{
		signal(SIGINT, sigint_c);
		signal(SIGQUIT, SIG_DFL);
		set_fd(data);
		if (execute_builtin(node, data, env))
			exit(g_rtn);
		execute_cmd(node, env);
		exit(1);
	}
	else
		exit_msg(1, STDERR_FILENO, "ERROR! : PID_ERROR\n");
}

void	init_fdr(t_exec *exec)
{
	if (exec->r_fd[INPUT] != STDIN_FILENO)
		dup2(STDIN_FILENO, exec->r_fd[INPUT]);
	if (exec->r_fd[OUTPUT] != STDOUT_FILENO)
		dup2(STDOUT_FILENO, exec->r_fd[OUTPUT]);
}

void	search_tree(t_token *node, t_exec *exec, char **env, int *sucess)
{
	if (node->type == T_PIPE)
		check_nextpipe(node, exec);
	else if (node->type == T_CMD)
		init_fdr(exec);
	else if (node->type == T_REDS)
	{
		if (!execute_rdr(node->rdr, exec))
		{
			*sucess = 0;
			return ;
		}
	}
	else if (node->type == T_SCMD)
		execute_simplecmd(node->cmd, exec, env);
	if (node->left != NULL && *sucess)
		search_tree(node->left, exec, env, sucess);
	if (node->right != NULL && *sucess)
		search_tree(node->right, exec, env, sucess);
}
