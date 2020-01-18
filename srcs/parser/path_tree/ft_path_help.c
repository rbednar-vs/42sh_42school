/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:57:07 by rbednar           #+#    #+#             */
/*   Updated: 2020/01/18 20:03:12 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/*
** Functions to insert t_path element prev or next
*/

int	ft_insert_prev(t_path **current, t_path **parent, t_path **temp)
{
	*current = (*current)->prev;
	if (*current == NULL)
	{
		(*parent)->prev = *temp;
		return (0);
	}
	return (1);
}

int	ft_insert_next(t_path **current, t_path **parent, t_path **temp)
{
	*current = (*current)->next;
	if (*current == NULL)
	{
		(*parent)->next = *temp;
		return (0);
	}
	return (1);
}

/*
** Function to free tree t_path
*/

int	ft_path_free(t_path **root)
{
	if (root != NULL && *root != NULL)
	{
		ft_path_free(&((*root)->prev));
		free((*root)->name);
		free((*root)->path);
		ft_path_free(&((*root)->next));
		free(*root);
	}
	return (0);
}
