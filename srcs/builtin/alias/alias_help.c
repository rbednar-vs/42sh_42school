/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:41:31 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/07 20:30:36 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

/*
** In the shell command language, a word consisting solely of underscores,
** digits, and alphabetics from the portable character set and any of the
** following characters: '!', '%', ',', '@'. (POSIX)
*/

int		btin_alias_valid_name(char *name)
{
	int	i;

	i = (name) ? ft_strlen(name) - 1 : 0;
	while (i >= 0 && name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '!' || name[i] == '%' ||
			name[i] == ',' || name[i] == '@' || name[i] == '_')
			i--;
		else
			break ;
	}
	if (++i == 0 && name)
		return (1);
	return (0);
}

/*
** Forming string name='command' from name=command
*/

char	*btin_alias_line_form(char *arg)
{
	char	*tmp;

	tmp = ft_xmalloc(sizeof(char) * (ft_strlen(arg) + 3));
	ft_strncat(tmp, arg, ft_strchri(arg, '='));
	ft_strcat(tmp, "='");
	ft_strcat(tmp, &arg[ft_strlen(tmp) - 1]);
	ft_strcat(tmp, "'");
	return (tmp);
}

/*
** Uses to check if "name" in alias array is equal to new "name" in buf array
*/

int		btin_alias_check_name(t_list *arr, t_list *buf)
{
	char	*als;
	char	*tmp;
	int		ret;

	als = ft_strndup((char*)arr->content, ft_strchri((char*)arr->content, '='));
	tmp = ft_strndup((char*)buf->content, ft_strchri((char*)buf->content, '='));
	ret = ft_strcmp(als, tmp);
	free(als);
	free(tmp);
	return (ret == 0 ? 1 : 0);
}

/*
** Uses to delete one alias by name=arg
*/

int		btin_alias_delete(t_list **alias, char *arg)
{
	t_list	*dest;
	t_list	tmp;
	t_list	*del;

	dest = *alias;
	del = dest;
	tmp.content = ft_strjoin(arg, "=");
	while (dest)
	{
		if (btin_alias_check_name(dest, &tmp))
		{
			del->next = dest->next;
			free(dest->content);
			*alias = del == dest ? del->next : *alias;
			free(dest);
			dest = del;
			break ;
		}
		del = dest;
		dest = del->next;
	}
	free(tmp.content);
	return (0);
}

/*
** Uses to delete all aliases. Cleans alias array if part of exit
** or "unalias -a"
*/

int		btin_alias_delete_all(t_list **alias)
{
	ft_lstclear(alias);
	return (0);
}
