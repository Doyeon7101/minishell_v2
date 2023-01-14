/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:32:52 by sangminpark       #+#    #+#             */
/*   Updated: 2023/01/12 19:44:52 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

void	ft_free_token(t_token *token)
{
	if (token == 0)
		return ;
	ft_free_token(token->left);
	ft_free_token(token->right);
	free(token);
}

char	**quotes_func(char **argv)
{
	int		i;
	int		j;
	int		quotes;
	char	**str;

	quotes = 0;
	str = malloc(sizeof(char) * (1));
	i = -1;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			quotes = is_quotes_set(argv[i][j], quotes);
			if ((argv[i][j] == '\"' && quotes == 1) ||
					(argv[i][j] == '\'' && quotes == 2))
				str[i] = fts_strjoin(str[i], argv[i][j], 0);
			else if (argv[i][j] != '\"' && argv[i][j] != '\'')
				str[i] = fts_strjoin(str[i], argv[i][j], 0);
		}
		str[i + 1] = NULL;
	}
	return (str);
}
