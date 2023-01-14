/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:34:04 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 12:26:20 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_c(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 0);
}

void	sigint_p(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\e[%dC  \n", rl_end + 11);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

/**
 * ctrl + c : SIGINT
 * ctrl + backslash : SIGQUIT
 * ctrl + D : SIGTERM
 * */
void	initialize_signal(void)
{
	signal(SIGINT, sigint_p);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

/**
 * printf("\033[1A"); // 커서를 위로 한 줄 올린다.
 * printf("\033[10C"); // 커서를 10만큼 앞으로 전진시킨다.
*/
void	check_exit_sigterm(char *line)
{
	if (!line)
	{
		printf("\033[1A");
		printf("\033[10C");
		printf(" bye\n");
		exit(1);
	}
}
