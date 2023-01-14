/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 22:28:04 by dpark             #+#    #+#             */
/*   Updated: 2023/01/14 14:47:38 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

char	*is_path_argument(char *p, int *is_path, char **env)
{
	char	*path;

	path = NULL;
	*is_path = TRUE;
	if (ftd_strcmp(p, "~") == 0)
		path = get_value_with_key("HOME", env);
	else if (p[0] == '~' || p[0] == '.' || p[0] == '/' || \
				ftd_strncmp("..", p, 2) == 0)
		path = p;
	else if (ftd_strcmp("-", p) == 0)
		path = get_value_with_key("OLDPWD", env);
	else if (*p == '$')
	{
		*is_path = FALSE;
		path = get_value_with_key(p + 1, env);
		if (!path)
			path = get_value_with_key("HOME", env);
		if (ft_strchr(path, '/'))
			*is_path = TRUE;
	}
	else
		return (NULL);
	return (path);
}

t_bool	update_path(char *path, char *now, t_exec *exec, char **env)
{
	int		ret;
	char	**argv;
	char	*pwd;

	ret = chdir(path);
	if (ret == -1)
	{
		free(now);
		return (FALSE);
	}
	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = "export";
	argv[1] = ft_strjoin2("OLDPWD=", now);
	argv[2] = NULL;
	ft_export(argv, exec, env);
	argv = (char **)malloc(sizeof(char *) * 3);
	pwd = getcwd(NULL, 0);
	argv[0] = "export";
	argv[1] = ft_strjoin2("PWD=", pwd);
	argv[2] = NULL;
	ft_export(argv, exec, env);
	free(pwd);
	free(now);
	return (TRUE);
}

void	ft_cd(char **argv, t_exec *exec, char **env)
{
	char	*path;
	int		is_path;
	t_bool	is_malloc;
	char	*now;

	g_rtn = 0;
	is_path = FALSE;
	is_malloc = FALSE;
	if (!argv[1])
		return ;
	now = getcwd(NULL, 0);
	path = is_path_argument(argv[1], &is_path, env);
	if (!path || !is_path)
	{
		path = ft_strjoin2(now, ft_strjoin2("/", argv[1]));
		is_malloc = TRUE;
	}
	if (!update_path(path, now, exec, env))
	{
		ft_putstr_fd("cd: No such file or directory\n", STDIN_FILENO);
		g_rtn = 1;
		return ;
	}
	if (is_malloc)
		free(path);
}
