/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:37:13 by sangminpark       #+#    #+#             */
/*   Updated: 2023/01/12 18:50:03 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*c1;
	const unsigned char	*c2;

	if (n == 0)
		return (0);
	c1 = (const unsigned char *)s1;
	c2 = (const unsigned char *)s2;
	i = 0;
	while (i + 1 < n && *(c1 + i) && *(c2 + i))
	{
		if (*(c1 + i) != *(c2 + i))
			break ;
		i++;
	}
	return (*(c1 + i) - *(c2 + i));
}

char	*fts_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*pnew;

	len = fts_strlen(s1);
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

size_t	fts_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*fts_strjoin(char *s1, char s2, int j)
{
	int		i;
	char	*c;

	(void)j;
	if (s1 == NULL)
	{
		c = ft_alert_calloc(1, sizeof(char) * 2);
		*c = s2;
		c++;
		*c = '\0';
		c--;
		return (c);
	}
	i = fts_strlen(s1) + 1;
	c = ft_alert_calloc(1, sizeof(char) * (i + 1));
	while (*s1)
		*c++ = *s1++;
	if (s2)
		*c = s2;
	c++;
	*c = '\0';
	i++;
	while (--i > 0)
		c--;
	return (c);
}

char	*fts_strjoin2(char *s1, char *s2)
{
	size_t	sindex1;
	size_t	sindex2;
	size_t	index;
	size_t	strindex;
	char	*str;

	sindex1 = fts_strlen(s1);
	sindex2 = fts_strlen(s2);
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
	free(s1);
	free(s2);
	return (str);
}
