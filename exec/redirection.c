/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:20:40 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 14:46:23 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	rdr_output(t_rdr *node, t_exec *data)
{
	char	*file_name;
	int		open_num;

	file_name = ft_strchr(node->file_name, ' ') + 1;
	if (data->r_fd[OUTPUT] != STDOUT_FILENO)
		close(data->r_fd[OUTPUT]);
	if (ftd_strcmp(node->type, ">") == 0)
		open_num = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		open_num = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	data->r_fd[OUTPUT] = open_num;
}

int	rdr_input(t_rdr *node, t_exec *data)
{
	int		status;
	char	*file_name;

	file_name = ft_strchr(node->file_name, ' ') + 1;
	status = open(file_name, O_RDONLY);
	if (status < 0)
	{
		ft_putstr_fd("ERROR: No such file or directory\n", STDERR_FILENO);
		g_rtn = 1;
		return (0);
	}
	else
	{
		if (data->r_fd[INPUT] != STDIN_FILENO)
			close(data->r_fd[INPUT]);
		data->r_fd[INPUT] = status;
	}
	return (1);
}

int	*ready_to_heredoc(t_exec *data, int fd[2])
{
	int	status;

	status = pipe(fd);
	if (status < 0)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "PIPE CREATION ERROR\n");
	if (data->r_fd[INPUT] != STDIN_FILENO)
		close(data->r_fd[INPUT]);
	return (0);
}

int	rdr_heredoc(t_rdr *node, t_exec *data)
{
	char	*line;
	int		fd[2];

	ready_to_heredoc(data, fd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd[WRITE_END]);
			return (0);
		}
		if (ftd_strcmp(node->file_name + 3, line) == 0)
		{
			free(line);
			close(fd[WRITE_END]);
			data->r_fd[INPUT] = fd[READ_END];
			return (1);
		}
		write(fd[WRITE_END], line, ft_strlen(line));
		write(fd[WRITE_END], "\n", 1);
		free(line);
	}
}

int	execute_rdr(t_rdr *node, t_exec *data)
{
	int	status;

	status = 1;
	if (ftd_strcmp(node->type, ">") == 0 || ftd_strcmp(node->type, ">>") == 0)
		rdr_output(node, data);
	else if (ftd_strcmp(node->type, "<") == 0)
		status = rdr_input(node, data);
	else if (ftd_strcmp(node->type, "<<") == 0)
		status = rdr_heredoc(node, data);
	if (data->r_fd[OUTPUT] < 0)
	{
		ft_putstr_fd("ERROR: FILE OPEN OUTPUT ERROR", STDERR_FILENO);
		g_rtn = 1;
	}
	if (!status)
		return (0);
	return (1);
}
