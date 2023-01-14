/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:26:18 by sangminpark       #+#    #+#             */
/*   Updated: 2023/01/12 15:48:10 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

t_token	*new_node(char *str, int type)
{
	t_token	*temp;
	char	**argv;

	temp = (t_token *)malloc(sizeof(t_token));
	temp->rdr = (t_rdr *)malloc(sizeof(t_rdr));
	temp->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (type == T_REDS)
	{
		temp->rdr->type = file_name(str);
		temp->rdr->file_name = str;
	}
	else if (type == T_SCMD)
	{
		temp->cmd->file_path = file_name(str);
		argv = ft_split(str, ' ');
		temp->cmd->argv = quotes_func(argv);
	}
	temp->type = type;
	temp->left = NULL;
	temp->right = NULL;
	return (temp);
}

t_token	*insert_pipe_node(t_token *node, char *str, int type)
{
	if (node == NULL)
		return (new_node(str, type));
	else
		node->right = insert_pipe_node(node->right, str, type);
	return (node);
}

t_token	*red_node(t_token *node, char *str, int type)
{
	if (node->type == T_CMD)
	{
		if (node->left == NULL)
			node->left = new_node(NULL, T_RED);
		node->left = red_node(node->left, str, type);
	}
	else if (node->type == T_RED)
	{
		if (node->left == NULL)
			node->left = new_node(str, T_REDS);
		else if (node->right == NULL)
		{
			node->right = new_node(NULL, T_RED);
			node->right = red_node(node->right, str, type);
		}
		else
			node->right = red_node(node->right, str, type);
	}
	return (node);
}

t_token	*insert_red_node(t_token *node, char *str, int type)
{
	if (node == NULL)
	{
		node = new_node(NULL, T_CMD);
		node = red_node(node, str, type);
	}
	else if (node->type == T_PIPE)
	{
		if (node->right == NULL)
		{
			if (node->left == NULL)
				node->left = new_node(NULL, T_CMD);
			node->left = red_node(node->left, str, type);
		}
		else
			node->right = insert_red_node(node->right, str, type);
	}
	else
		node = red_node(node, str, type);
	return (node);
}

t_token	*insert_scmd_node(t_token *node, char *str, int type)
{
	if (node == NULL)
	{
		node = new_node(NULL, T_CMD);
		node = insert_scmd_node(node, str, type);
	}
	else if (node->type == T_PIPE)
	{
		if (node->right == NULL)
		{
			if (node->left == NULL)
				node->left = new_node(NULL, T_CMD);
			node->left = insert_scmd_node(node->left, str, type);
		}
		else
			node->right = insert_scmd_node(node->right, str, type);
	}
	else if (node->type == T_CMD)
	{
		node->right = new_node(str, T_SCMD);
	}
	return (node);
}
