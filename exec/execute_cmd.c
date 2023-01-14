/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:20:44 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 14:46:03 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	execute_builtin(t_cmd *node, t_exec *data, char **env)
{
	if (ftd_strcmp(node->file_path, "cd") == 0)
		ft_cd(node->argv, data, env);
	else if (ftd_strcmp(node->file_path, "exit") == 0)
		ft_exit(node->argv);
	else if (ftd_strcmp(node->file_path, "unset") == 0)
		ft_unset(*(node->argv + 1), env);
	else if (ftd_strcmp(node->file_path, "pwd") == 0)
		ft_pwd(data);
	else if (ftd_strcmp(node->file_path, "env") == 0)
		ft_env(data, env, node);
	else if (ftd_strcmp(node->file_path, "echo") == 0)
		ft_echo(node->argv, data);
	else if (ftd_strcmp(node->file_path, "export") == 0)
		ft_export(node->argv, data, env);
	else
		return (FALSE);
	return (TRUE);
}

void	set_wpid_status_with_sig(int status)
{
	g_rtn = WEXITSTATUS(status);
	if (WTERMSIG(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_rtn = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			g_rtn = 131;
		else
			g_rtn = 128 + status;
	}
}

void	wait_childs(t_exec *data)
{
	const pid_t	child = data->wpid;
	pid_t		pid;
	int			status;
	int			last_status;

	last_status = 1;
	while (1)
	{
		signal(SIGINT, sigint_c);
		signal(SIGQUIT, SIG_DFL);
		pid = wait(&status);
		if (pid == child)
			last_status = status;
		if (pid == -1)
		{
			set_wpid_status_with_sig(last_status);
			return ;
		}
	}
}

void	execute_simplecmd(t_cmd *node, t_exec *data, char **env)
{
	if (!data->is_pipe)
	{
		if (execute_builtin(node, data, env))
			return ;
	}
	with_fork(node, data, env);
	(data->pipe_cnt)--;
	if (data->pipe_cnt <= 0)
	{
		wait_childs(data);
		return ;
	}
}
