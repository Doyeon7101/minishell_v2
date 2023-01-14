/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:28 by dpark             #+#    #+#             */
/*   Updated: 2023/01/11 12:13:43 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

void	exit_msg(int exit_status, int fd, char *msg)
{
	g_rtn = exit_status;
	ft_putstr_fd("ERROR: ", fd);
	ft_putstr_fd(msg, fd);
	exit(exit_status);
}
