/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:13:25 by sangminpark       #+#    #+#             */
/*   Updated: 2023/01/12 12:31:56 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (n == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == 0)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_freeall(char **list)
{
	size_t	j;

	j = 0;
	while (list[j])
	{
		free(list[j]);
		j++;
	}
	free(list);
	return (NULL);
}

size_t	ft_wordcount(char const *s, char c)
{
	size_t	listsize;
	size_t	i;
	int		quotes;

	i = 0;
	listsize = 0;
	quotes = 0;
	while (s[i] != '\0')
	{
		quotes = is_quotes_set(s[i], quotes);
		if ((i == 0 && s[i] != c) || (s[i] == c && s[i + 1]
				!= '\0' && s[i + 1] != c))
		{
			if (quotes == 0)
				listsize++;
		}
		i++;
	}
	return (listsize);
}

void	split_init(t_scmd *cmd)
{
	cmd->i = 0;
	cmd->k = 0;
	cmd->quotes = 0;
}

char	**ft_split(char const *s, char c)
{
	t_scmd	*cmd;
	char	**strlist;

	cmd = malloc(sizeof(t_scmd));
	split_init(cmd);
	strlist = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!strlist)
		return (NULL);
	while (cmd->i < (int)ft_wordcount(s, c) && s[cmd->k] != '\0')
	{
		cmd->quotes = is_quotes_set(s[cmd->k], cmd->quotes);
		while (s[cmd->k] == c)
			cmd->k++;
		cmd->save = cmd->k;
		while ((s[cmd->k] != c && s[cmd->k] != '\0') || cmd->quotes != 0)
		{
			cmd->quotes = is_quotes_set(s[cmd->k], cmd->quotes);
			cmd->k++;
		}
		strlist[cmd->i] = ft_strndup(&s[cmd->save], cmd->k - cmd->save);
		if (strlist[cmd->i++] == 0)
			return (ft_freeall(strlist));
	}
	strlist[cmd->i] = NULL;
	return (strlist);
}
