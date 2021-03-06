/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 17:00:43 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/08/26 15:39:05 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>
#include <builtin42.h>

int		ft_o_dir(char *str, char *path)
{
	DIR		*dir;

	if (!ft_strcmp(str, path))
		return (-1);
	if (!(dir = opendir(str)))
		return (-1);
	closedir(dir);
	return (0);
}

char	*ft_cdpath(char *path, char **env, char *res, int i)
{
	char	**arr;
	int		j;

	if ((i = find_in_any_variable(env, &j, "CDPATH")) < 0 ||
			!path || path[0] == '/')
		return (NULL);
	res = NULL;
	arr = ft_strsplit(env[i] + j, ':');
	i = -1;
	while (arr[++i])
	{
		if (path[0] == '.' && path[1] == '.')
			continue ;
		res = ft_new_path_cd(path, arr[i], NULL);
		if ((ft_o_dir(res, path)) == 0)
			break ;
		ft_strdel(&res);
	}
	ft_arrdel(arr);
	if (res != NULL)
	{
		ft_putendl_fd(res, STDOUT_FILENO);
		return (res);
	}
	return (NULL);
}

int		ft_cd_env(char *path, char **env, t_cd *flags)
{
	char	*name;
	int		i;
	int		j;

	name = NULL;
	name = path ? ft_strdup("OLDPWD") : ft_strdup("HOME");
	i = find_in_any_variable(env, &j, name);
	free(name);
	if (i < 0)
		return (ft_error_cd(NULL, (path) ? 6 : 7));
	if (path)
		ft_putendl_fd(env[i] + j, STDOUT_FILENO);
	name = ft_strdup(env[i] + j);
	return ((ft_change_path(name, env, flags)));
}

int		ft_cd_pars(char *path, char **env, t_cd *flags)
{
	struct stat buff;
	char		*tmp;

	if ((tmp = ft_cdpath(path, env, NULL, -1)) != NULL)
		return (ft_change_path(tmp, env, flags));
	if (ft_strcmp(path, "-") == 0 || !path)
		return ((ft_cd_env(path, env, flags)));
	if (stat(path, &buff) < 0)
		return (ft_error_cd(path, 2));
	else if (!S_ISDIR(buff.st_mode))
		return (ft_error_cd(path, 4));
	else
		return (ft_change_path(ft_new_path_cd(path, NULL, flags), env, flags));
	return (0);
}
