/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:37:53 by sangminpark       #+#    #+#             */
/*   Updated: 2023/01/12 18:18:18 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

char	*file_name(char *str)
{
	char	*chr;

	chr = 0;
	while (is_space(str[0]) == 1 && *str)
		str++;
	while (is_space(str[0]) == 0 && *str)
	{
		chr = fts_strjoin(chr, str[0], 1);
		str++;
	}
	return (chr);
}

t_token	*ft_cmd_func(t_token *tree, char *str)
{
	char	*chr;
	int		quotes;

	quotes = 0;
	chr = 0;
	while (*str && str)
	{
		quotes = is_quotes_set(str[0], quotes);
		if ((str[0] == '>' || str[0] == '<') && quotes == 0)
		{
			tree = is_redirects_func(tree, &str[0]);
			str += file_name_size(&str[0]);
		}
		else
		{
			chr = fts_strjoin(chr, str[0], 0);
		}
		str++;
	}
	if (chr != NULL)
		tree = insert_scmd_node(tree, chr, T_SCMD);
	return (tree);
}

int	is_quotes_set(char str, int quotes)
{
	int	result;

	result = quotes;
	if (str == '\'')
	{
		if (quotes == 1)
			result = 0;
		else if (quotes == 2)
			result = 2;
		else
			result = 1;
	}
	else if (str == '\"')
	{
		if (quotes == 2)
			result = 0;
		else if (quotes == 1)
			result = 1;
		else
			result = 2;
	}
	return (result);
}

int	is_space(char str)
{
	if (str == ' ')
	{
		return (1);
	}
	return (0);
}
