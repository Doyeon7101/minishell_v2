/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:33 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 14:46:09 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_execve(void)
{
	if (errno == EISDIR || errno == EACCES)
		exit_msg(126, STDERR_FILENO, strerror(EISDIR));
	else if (errno == ENOENT)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, strerror(errno));
}

int	check_is_path(char *str, char **argv, char **environ)
{
	t_ftype		f_type;

	if (str[0] == '/')
	{
		f_type = check_ftype(str);
		if (f_type == F_FILE)
		{
			execve(str, argv, environ);
			return (0);
		}
	}
	return (1);
}

void	if_notfound(t_cmd *node, char **environ, char *path)
{
	if (path == NULL)
	{
		if (execve(node->file_path, node->argv, environ) == -1)
			exit_msg(127, STDERR_FILENO, "command not found\n");
	}
}

void	execute_cmd(t_cmd *node, char **environ)
{
	char		*path_cmd;
	char		*path;

	path_cmd = NULL;
	if (check_is_path(node->file_path, node->argv, environ))
	{
		path = get_value_with_key("PATH", environ);
		while (1)
		{
			if (path[0] == '/')
			{
				path_cmd = join_path(path, node->file_path);
				if (check_ftype(path_cmd) == F_FILE || \
					check_ftype(path_cmd) == F_DIR)
					break ;
				free(path_cmd);
			}
			path = ft_strchr(path, ':');
			if_notfound(node, environ, path);
			path++;
		}
	}
	printf("***%s\n", path_cmd);
	if (execve(path_cmd, node->argv, environ) == -1)
	{
		exit_execve();
	}
}
