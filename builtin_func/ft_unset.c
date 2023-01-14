/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:40:57 by sangminpark       #+#    #+#             */
/*   Updated: 2023/01/14 14:47:26 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	check_unset(char *str, char *envp)
{
	int		i;

	i = 0;
	while (str[i] && envp[i] && (str[i] == envp[i]) && (envp[i] != '='))
		i++;
	if ((str[i] == '\0') && (envp[i] == '='))
		return (1);
	return (0);
}

int	check_unset_2(char *str, char *envp)
{
	int		i;

	i = 0;
	if (ft_strlen(str) != ft_strlen(envp))
		return (0);
	while (str[i] && envp[i] && (str[i] == envp[i]))
		i++;
	if (i == (int)ft_strlen(str))
		return (1);
	return (0);
}

int	ft_unset(char *str, char **envp)
{
	int	i;
	int	size;

	size = 0;
	while ((envp)[size] != NULL)
		size++;
	if (size < 1)
		return (-1);
	i = -1;
	while ((envp)[++i] != NULL)
	{
		if (check_unset(str, (envp)[i]) || check_unset_2(str, (envp)[i]))
		{
			while (i < size - 1)
			{
				(envp)[i] = ft_strdup((envp)[i + 1]);
				i++;
			}
			(envp)[size - 1] = NULL;
			return (1);
		}
	}
	g_rtn = 0;
	return (1);
}
