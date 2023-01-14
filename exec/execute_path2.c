/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:56:19 by dpark             #+#    #+#             */
/*   Updated: 2023/01/11 21:18:10 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_ftype	check_ftype(char *path_cmd)
{
	struct stat	file_stat;

	if (stat(path_cmd, &file_stat))
		return (F_NOTFOUND);
	if ((file_stat.st_mode & S_IFMT) == S_IFDIR)
		return (F_DIR);
	return (F_FILE);
}

char	*join_path(char *path, char *cmd)
{
	char	*ret;
	size_t	size;

	if (ft_strchr(path, ':'))
	{
		size = ft_strchr(path, ':') - path + ft_strlen(cmd) + 2;
		ret = ft_alert_calloc(size, 1);
		ft_strlcat(ret, path, ft_strchr(path, ':') - path + 1);
	}
	else
	{
		size = ft_strlen(path) + ft_strlen(cmd) + 2;
		ret = ft_alert_calloc(size, 1);
		ft_strlcat(ret, path, size);
	}
	ft_strlcat(ret, "/", size);
	ft_strlcat(ret, cmd, size);
	return (ret);
}
