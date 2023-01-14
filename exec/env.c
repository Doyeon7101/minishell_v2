/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 22:28:13 by dpark             #+#    #+#             */
/*   Updated: 2023/01/12 19:59:22 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_value_with_key(char *key, char **environ)
{
	char		**ptr;
	int			size;

	ptr = environ;
	while (*ptr)
	{
		size = ft_strchr(*ptr, '=') - *ptr;
		if (ftd_strncmp(*ptr, key, size) == 0)
			return (ft_strchr(*ptr, '=') + 1);
		ptr++;
	}
	return (NULL);
}
