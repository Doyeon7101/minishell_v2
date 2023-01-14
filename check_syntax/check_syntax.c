/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:48:21 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 14:48:22 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*check_filename(t_rdr *rdr, int *ret)
{
	if (ftd_strcmp(">>", rdr->type) == 0)
	{
		if (rdr->file_name[3] == '\0')
			*ret = -1;
	}
	else
	{
		if (rdr->file_name[2] == '\0')
			*ret = -1;
	}
	return (0);
}

void	check_syntax(t_token *tree, int *ret, t_exec *data)
{
	if (*ret == -1)
		return ;
	if (tree == NULL)
		*ret = -1;
	if (tree->type == T_PIPE)
	{
		data->is_pipe = 1;
		(data->pipe_cnt)++;
	}
	if (tree->type == T_REDS)
		check_filename(tree->rdr, ret);
	if (tree->left != NULL)
		check_syntax(tree->left, ret, data);
	if (tree->right != NULL)
		check_syntax(tree->right, ret, data);
}
