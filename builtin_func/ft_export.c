/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:40:54 by sangminpark       #+#    #+#             */
/*   Updated: 2023/01/13 22:30:18 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

char	*new_export(char *str, char *envp)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != '='))
		i++;
	if (str[i] == '=')
	{
		if (str[i + 1] == 0)
		{
			(envp) = ft_strdup(str);
			(envp) = ft_strjoin3((envp), "\'\'");
		}
		else
			(envp) = ft_strdup(str);
	}
	else if (str[i] == '\0')
	{
		(envp) = ft_strdup(str);
		(envp) = ft_strjoin3((envp), "=\'\'");
	}
	return (envp);
}

int	export(char *str, char **envp)
{
	while ((*envp))
	{
		if (check_env(str, (*envp)) == 1)
		{
			(*envp) = ft_strdup(str);
			return (1);
		}
		else if (check_env(str, (*envp)) == 2)
		{
			(*envp) = ft_strdup(str);
			(*envp) = ft_strjoin3((*envp), "=\'\'");
			return (1);
		}
		else if (check_env(str, (*envp)) == 3)
		{
			(*envp) = ft_strdup(str);
			(*envp) = ft_strjoin3((*envp), "=\'\'");
			return (1);
		}
		envp++;
	}
	*envp = new_export(str, *envp);
	envp++;
	*envp = 0;
	return (1);
}

int	error_msg(char *argv, t_exec *data)
{
	ft_putstr_fd("bash: export: ", STDOUT_FILENO);
	if (argv)
		write(data->r_fd[WRITE_END], argv, strlen(argv));
	ft_putstr_fd(": not a valid identifier\n", STDOUT_FILENO);
	return (0);
}

int	export_error(char *argv, t_exec *data)
{
	if ((argv[0] < '0' || argv[0] > '9') && argv[0] != '=')
		return (1);
	else
		return (error_msg(argv, data));
	return (1);
}

void	ft_export(char **argv, t_exec *data, char **environ)
{
	g_rtn = 0;
	if (!argv[1])
	{
		print_export(environ, data);
		g_rtn = 0;
		return ;
	}
	argv++;
	while (*argv)
	{
		if (export_error(*argv, data) == 0)
			argv++;
		else
		{
			export(*argv, environ);
			argv++;
		}
	}
	return ;
}
