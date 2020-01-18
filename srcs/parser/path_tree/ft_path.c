/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:36:08 by rbednar           #+#    #+#             */
/*   Updated: 2020/01/18 21:06:25 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/*
** Func init t_path element
*/

static void		ft_init_path(char *name_d, t_dirent *dp, t_path **tmp)
{
	if ((*tmp = (t_path*)malloc(sizeof(t_path))))
	{
		(*tmp)->name = ft_strdup(dp->d_name);
		ft_addpath(name_d, tmp);
		(*tmp)->prev = NULL;
		(*tmp)->next = NULL;
		(*tmp)->flag = 0;
	}
}

/*
** Func insert t_path element by *root element if it exist
*/

static int		ft_insert_in(char *name_d, t_path **root, t_path **temp)
{
	t_path	*current;
	t_path	*parent;

	current = *root;
	while (1)
	{
		parent = current;
		if (!(ft_strcmp((*temp)->name, parent->name)))
			return (0);
		else if (ft_strcmp((*temp)->name, parent->name) < 0)
		{
			if (!(ft_insert_prev(&current, &parent, temp)))
				return (0);
		}
		else
		{
			if (!(ft_insert_next(&current, &parent, temp)))
				return (0);
		}
	}
}

/*
** Func insert t_path element by *root element in all conditions
*/

static void		insert(char *name_d, t_dirent *dp, t_path **root, size_t *len)
{
	t_path	*temp;

	ft_init_path(name_d, dp, &temp);
	if (*root == NULL)
	{
		*root = temp;
		(*len) += 1;
	}
	else
	{
		ft_insert_in(name_d, root, &temp);
		(*len) += 1;
	}
}

/*
** Func finds files in dir and add it to tree of type t_path
*/

void			ft_get_path(char *name_d, t_path **root, size_t *len, \
				char *find)
{
	DIR			*dir;
	t_stat		*stat_b;
	t_dirent	*dp;

	if ((stat_b = (t_stat *)malloc(sizeof(t_stat))) == NULL)
		return ;
	if (lstat(name_d, stat_b) == -1)
		return ;
	if (!(dir = opendir(name_d)))
		return ;
	while (dir != NULL)
	{
		if ((dp = readdir(dir)) != NULL)
		{
			if (ft_strnequ(dp->d_name, find, ft_strlen(find)))
				insert(name_d, dp, root, len);
		}
		else
			closedir(dir) == 0 ? dir = NULL : 0;
	}
	free(stat_b);
}

/*
** Func find and return **char of all insertions of string find in PATH
*/

char			**ft_path_pars(char *find, char *path, size_t *total)
{
	t_path	*root;
	char	**list;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	root = NULL;
	list = ft_strsplit(path, ':');
	while (list[i])
	{
		ft_get_path(list[i], &root, &len, find);
		free(list[i]);
		i++;
	}
	if (list != NULL)
		free(list);
	*total = len;
	list = ft_add_block(&root, len);
	ft_path_free(&root);
	return (list);
}
