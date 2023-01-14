/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nextpipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:32:24 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 01:13:30 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	check_nextpipe(t_token *node, t_exec *exec)
{
	int	status;

	if (node->right != NULL && node->right->type == T_PIPE)
	{
		status = pipe(exec->fd);
		if (status < 0)
			exit_msg(EXIT_FAILURE, STDERR_FILENO, "PIPE CREATION ERROR\n");
		exec->next_pipe = TRUE;
		exec->pipe[WRITE_END] = exec->fd[WRITE_END];
	}
}
