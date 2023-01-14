/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:07 by dpark             #+#    #+#             */
/*   Updated: 2023/01/11 12:18:01 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int		index;
	char	*target;

	index = 0;
	target = NULL;
	while (s[index] != '\0')
	{
		if (s[index] == c)
		{
			target = &s[index];
			break ;
		}
		index++;
	}
	if (s[index] == '\0' && s[index] == c)
		target = &s[index];
	return (target);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	uc;
	size_t			i;

	ptr = (unsigned char *)b;
	uc = (unsigned char)c;
	i = 0;
	while (i++ < len)
		*ptr++ = uc;
	return (b);
}

void	*ft_alert_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = malloc(count * size);
	if (!ret)
	{
		printf("malloc error!\n");
		exit(1);
	}
	ft_memset(ret, 0, count * size);
	return (ret);
}

int	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	index;
	size_t	dstlen;
	int		srclen;

	index = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	while (dst[index] != '\0')
		dst++;
	if (dstsize > 0)
	{
		while ((int)index < ((int)dstsize - (int)dstlen - 1)
			&& src[index] != '\0')
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	if (dstsize < dstlen)
		return (srclen + dstsize);
	else
		return (dstlen + srclen);
}
