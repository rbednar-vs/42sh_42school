/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_processing_compl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:53:36 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/19 19:08:28 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

char				*find_path_compl(char *compl, int tmp)
{
	char			*path;
	size_t			i;
	size_t			j;

	if (g_rline.pos == 0)
		return (NULL);
	if (compl && compl[0] && tmp != -1)
	{
		i = g_rline.pos - 1;
		while (i > 0 && (ft_isalnum(g_rline.cmd[i]) || g_rline.cmd[i] == '.' ||
			g_rline.cmd[i] == '/' || g_rline.cmd[i] == '_'))
			i--;
		j = g_rline.pos - 1;
		while (j > 0 && (ft_isalnum(g_rline.cmd[j])
			|| g_rline.cmd[j] == '.'))
		{
			if (g_rline.cmd[j] == '/')
				break ;
			j--;
		}
		path = ft_strndup(g_rline.cmd + i + 1, j - i);
	}
	else
		path = ft_strdup("./");
	return (path);
}

char				*path_parse_compl(void)
{
	size_t			i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], "PATH=", 5) == 0)
			return (g_env[i] + 5);
		i++;
	}
	return (NULL);
}
