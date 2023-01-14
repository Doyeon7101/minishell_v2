/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:43:10 by dpark             #+#    #+#             */
/*   Updated: 2023/01/13 22:43:32 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

void	ft_pwd(t_exec *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		g_rtn = 1;
		return ;
	}
	write(data->r_fd[OUTPUT], path, ft_strlen(path));
	free(path);
	path = NULL;
	write(data->r_fd[OUTPUT], "\n", 1);
	g_rtn = 0;
	return ;
}
