/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_processing42.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:27:42 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/02/18 17:25:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int					realloc_all_gvariables_array(void)
{
	ft_realloc_array(&g_env, g_var_size, g_var_size * 2);
	ft_realloc_array(&g_lovar, g_var_size, g_var_size * 2);
	g_var_size *= 2;
	return (0);
}

/*
** If we need to get line and symbol (after '=') from that the value of the
** variable starts, we sent the name, int what array to search and an integer pointer
*/

size_t				find_in_variables(char **arr, size_t *j, char *name)
{
	size_t			i;
	size_t			tmp;

	i = 0;
	while (arr[i])
	{
		tmp = ft_strchri(arr[i], '=') + 1;
		if (ft_strncmp(arr[i], name, tmp) == 0 && arr[i][tmp])
		{
			*j = tmp;
			return (i);
		}
		i++;
	}
	return (-1);
}

char				**init_exec_environ(void)
{
	char			**envir;
	size_t			i;

	envir = (char**)ft_xmalloc(sizeof(char*) * (g_var_size + 1));
	i = 0;
	while(g_env[i])
	{
		envir[i] = ft_strdup(g_env[i]);
		i++;
	}
	return (envir);
}

int					add_new_to_exec_env(char ***array, char *add)
{
	size_t			i;
	char			**tmp;

	i = 0;
	tmp = *array;
	while (tmp[i])
		i++;
	if (i == g_var_size)
	{
		ft_realloc_array(&tmp, g_var_size, g_var_size * 2);
		realloc_all_gvariables_array();
	}
	tmp[i] = ft_strdup(add);
	return (0);
}