/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:43:43 by sangminpark       #+#    #+#             */
/*   Updated: 2023/01/12 19:35:07 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

char	*ft_strdup(char *s1)
{
	size_t	len;
	size_t	i;
	char	*pnew;

	len = ft_strlen(s1);
	pnew = (char *)malloc(sizeof(char) * (len + 1));
	if (pnew == 0)
		return (0);
	i = 0;
	while (i <= len)
	{
		*(pnew + i) = *(s1 + i);
		i++;
	}
	return (pnew);
}

size_t	ft_strlen2(char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

char	*ft_strjoin3(char *s1, char *s2)
{
	size_t	sindex1;
	size_t	sindex2;
	size_t	index;
	size_t	strindex;
	char	*str;

	sindex1 = ft_strlen2(s1);
	sindex2 = ft_strlen2(s2);
	index = 0;
	strindex = 0;
	if (s1 == NULL)
		s1 = malloc(sizeof(char) * 1);
	str = (char *)malloc(sizeof(char) * (sindex1 + sindex2 + 1));
	if (str == NULL)
		return (NULL);
	while (index < sindex1)
		str[strindex++] = s1[index++];
	index = 0;
	while (index < sindex2)
		str[strindex++] = s2[index++];
	str[strindex] = '\0';
	return (str);
}

int	print_export(char **envp, t_exec *data)
{
	int		i;
	char	*declare;

	i = -1;
	declare = "declare -x ";
	while (envp[++i])
	{
		write(data->r_fd[WRITE_END], declare, ft_strlen(declare));
		write(data->r_fd[WRITE_END], envp[i], ft_strlen(envp[i]));
		write(data->r_fd[WRITE_END], "\n", 1);
	}
	return (1);
}

int	check_env(char *str, char *envp)
{
	int	i;

	i = 0;
	while (str[i] && envp[i] && (str[i] == envp[i]) && (str[i] != '=')
		&& (envp[i] != '='))
		i++;
	if (i == 0)
		return (0);
	if ((envp[i] == '=') && (str[i] == '='))
	{
		if (str[i + 1] == 0)
			return (3);
		return (1);
	}
	else if ((envp[i] == '=') && str[i] == 0)
	{
		return (2);
	}
	return (0);
}
