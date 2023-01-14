/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 10:11:25 by dpark             #+#    #+#             */
/*   Updated: 2023/01/13 22:30:00 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

void	ft_env(t_exec *data, char **environ, t_cmd *node)
{
	char		**ptr;

	if (node->argv[1])
	{
		g_rtn = 1;
		exit(g_rtn);
	}
	ptr = environ;
	write(data->r_fd[OUTPUT], *ptr, ft_strlen(*ptr));
	while (*++ptr)
	{
		write(data->r_fd[WRITE_END], "\n", 1);
		write(data->r_fd[OUTPUT], *ptr, ft_strlen(*ptr));
	}
	write(data->r_fd[WRITE_END], "\n", 1);
	g_rtn = 0;
	return ;
}
