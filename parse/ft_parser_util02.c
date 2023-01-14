/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_util02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:37:53 by sangminpark       #+#    #+#             */
/*   Updated: 2023/01/13 17:35:07 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

int	env_error(char *line)
{
	if (is_space(*line) == 0 && *line != '\"' && *line != '\''
		&& *line != '|' && *line != '<' && *line != '>' && *line)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	int			len;
	int			sign;
	char		*ptr;
	long long	temp;

	temp = (long long)n;
	len = ft_itoa_len(temp);
	ptr = malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (0);
	if (n < 0)
	{
		temp = -(long long)n;
		sign = -1;
	}
	ptr[len] = '\0';
	while (--len >= 0)
	{
		ptr[len] = '0' + temp % 10;
		temp /= 10;
	}
	if (sign == -1)
		ptr[0] = '-';
	return (ptr);
}

int	env_strlen(char *environ, char	*str)
{
	int	size;

	size = 0;
	while ((environ)[size] != '=')
		size++;
	if (size < (int)fts_strlen(str))
		size = (int)fts_strlen(str);
	return (size);
}

char	*ft_check_env(char *line, char **environ)
{
	int		i;		
	int		size;
	char	*str;

	i = 0;
	str = 0;
	line++;
	if (*line == '?')
		return (str = ft_itoa(g_rtn));
	while (env_error(line) == 1)
	{
		str = fts_strjoin(str, line[0], 0);
		line++;
	}
	i = -1;
	while (environ[++i])
	{
		size = env_strlen(environ[i], str);
		if (ft_strncmp(str, environ[i], size) == 0)
		{
			str = fts_strdup(&(environ)[i][size + 1]);
			return (str);
		}
	}
	return (0);
}

int	env_size(char *line)
{
	int	i;

	i = 0;
	i++;
	while (env_error(&line[i]) == 1)
		i++;
	i--;
	return (i);
}
