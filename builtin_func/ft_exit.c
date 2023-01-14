/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:40:51 by sangminpark       #+#    #+#             */
/*   Updated: 2023/01/14 14:44:35 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	result;

	i = 0;
	n = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * n);
}

void	exit_util(char **argv)
{
	int	i;

	i = -1;
	while (argv[1][++i])
	{
		if (argv[1][i] < '0' || argv[1][i] > '9')
		{
			printf("exit\nbash: exit: %s: numeric argument required\n", argv[1]);
			g_rtn = 255;
			exit(g_rtn);
		}
	}
	if (argv[2] == NULL)
	{
		printf("exit\n");
		g_rtn = ft_atoi(argv[1]);
		exit(g_rtn);
	}
	else
	{
		printf("exit\nbash :exit: too many arguments\n");
	}
}

int	ft_exit(char **argv)
{
	if (argv[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	else
	{
		exit_util(argv);
	}
	g_rtn = 1;
	return (g_rtn);
}
