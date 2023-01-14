/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:20:53 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 14:46:44 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	set_fd(t_exec *data)
{
	if (data->r_fd[INPUT] != STDIN_FILENO)
		dup2(data->r_fd[INPUT], STDIN_FILENO);
	if (data->r_fd[OUTPUT] != STDOUT_FILENO)
		dup2(data->r_fd[OUTPUT], STDOUT_FILENO);
	if (data->next_pipe)
	{
		close(data->fd[READ_END]);
		dup2(data->pipe[WRITE_END], STDOUT_FILENO);
		close(data->pipe[WRITE_END]);
	}
	if (data->prev_pipe)
	{
		if (data->pipe[READ_END] != STDIN_FILENO)
		{
			dup2(data->pipe[READ_END], STDIN_FILENO);
			close(data->pipe[READ_END]);
		}
	}
}

void	update_fd(t_exec *data)
{
	if (data->r_fd[INPUT] != STDIN_FILENO)
		close(data->r_fd[INPUT]);
	if (data->r_fd[OUTPUT] != STDOUT_FILENO)
		close(data->r_fd[OUTPUT]);
	if (data->prev_pipe)
	{
		close(data->pipe[READ_END]);
		data->prev_pipe = FALSE;
	}
	if (data->next_pipe)
	{
		close(data->fd[WRITE_END]);
		data->next_pipe = FALSE;
		data->pipe[READ_END] = data->fd[READ_END];
		data->prev_pipe = TRUE;
	}
}
