/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:43:04 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 14:47:04 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

void	set_option(int *i, t_bool *is_n, char **argv)
{
	char	*str;

	str = argv[1];
	*is_n = FALSE;
	*i = 1;
	if (ftd_strncmp(str++, "-n", 2) == 0)
	{
		while (42)
		{
			str++;
			if (*str && *str != 'n' && *str != ' ')
				break ;
			if (*str == '\0')
			{
				*is_n = TRUE;
				*i = 2;
				break ;
			}
		}
	}
}

void	ft_echo(char **argv, t_exec *data)
{
	int		i;
	t_bool	is_n;

	if (!argv[1])
	{
		write(data->r_fd[WRITE_END], "\n", 1);
		return ;
	}
	set_option(&i, &is_n, argv);
	if (argv[i])
		write(data->r_fd[WRITE_END], argv[i], ft_strlen(argv[i]));
	while (argv[++i])
	{
		write(data->r_fd[WRITE_END], " ", 1);
		write(data->r_fd[WRITE_END], argv[i], ft_strlen(argv[i]));
	}
	if (!is_n)
		write(data->r_fd[WRITE_END], "\n", 1);
	g_rtn = 0;
	return ;
}
