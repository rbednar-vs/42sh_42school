/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_work.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:55:12 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/26 03:40:08 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Simle to remove unused number (num_sym) of symbols by moving end of g_cmd
** g_techline.line and resizing g_cmd_size and g_techline.len.
*/

int		ft_reglue(size_t *i, int num, t_ltree *sub)
{
	size_t	z;
	size_t	size;

	ft_memmove(&(sub->l_cmd[*i]), &(sub->l_cmd[*i + num]),
	sub->l_techline.len - (*i + num - 1));
	ft_memmove(&(sub->l_techline.line[*i]), &(sub->l_techline.line[*i + num]),
	sub->l_techline.len - (*i + num - 1));
	sub->l_techline.len -= num;
	z = sub->l_techline.len;
	size = z + num;
	while (++z <= size)
	{
		sub->l_cmd[z] = '\0';
		sub->l_techline.line[z] = '\0';
	}
	return (0);
}

int		pre_parsing_back(size_t *i, t_ltree *sub)
{
	char	*end;

	end = sub->l_techline.line;
	if (end[*i] == BSLASH && end[*i + 1] == ENTER)
		ft_reglue(i, 2, sub);
	if (end[*i] == BSLASH && end[*i + 1] == BSLASH)
	{
		ft_reglue(i, 1, sub);
		(*i)++;
	}
	if (end[*i] == BSLASH)
		ft_reglue(i, 1, sub);
	return (0);
}

int		pre_parsing_andor_pipe(size_t *i, t_ltree *sub)
{
	char	*end;

	end = sub->l_techline.line;
	if ((end[*i] == PIPE && end[*i + 1] == PIPE) ||
		(end[*i] == AND && end[*i + 1] == AND) ||
		end[*i] == PIPE)
	{
		if (end[*i] == PIPE && end[*i + 1] != PIPE)
			*i += 1;
		else
			*i += 2;		
		while (end[*i] == SPACE)
			(*i)++;
		if (end[*i] == ENTER)
		{
			end[*i] = SPACE;
			sub->l_cmd[*i] = ' ';
		}
	}
	return (0);
}

int		pre_parsing_squote(size_t *i, t_ltree *sub)
{
	char	*end;

	end = sub->l_techline.line;
	if (end[*i] == SQUOTE)
	{
		ft_reglue(i, 1, sub);
		while (end[*i] != SQUOTE)
			(*i)++;
		ft_reglue(i, 1, sub);
	}
	pre_parsing_andor_pipe(i, sub);
	pre_parsing_back(i, sub);
	return (0);
}

/*
** This function and subfunctions needs to cut and glue line before parsing.
** It shall be done by POSIX to remove \, "" and '' from line
*/

int		pre_parsing_cut_glue(t_ltree *sub)
{
	char	*end;
	size_t	i;

	i = 0;
	end = sub->l_techline.line;
	while (i < sub->l_techline.len)
	{
		if (end[i] == DQUOTE)
		{
			ft_reglue(&i, 1, sub);
			while (end[i] != DQUOTE)
			{
				end[i] == SPACE ? end[i] = GLUE : 0;
				pre_parsing_back(&i, sub);
				i++;
			}
			ft_reglue(&i, 1, sub);
		}
		else
			pre_parsing_squote(&i, sub);
		if (end[i] == ENTER && sub->l_cmd[i + 1] == '\0')
			ft_reglue(&i, 1, sub);
		i++;
	}
	// printf("techline pre:");//печать для проверки
	// i = -1;
	// while (++i < sub->l_techline.len + 1)
	// 	printf("%3d", sub->l_techline.line[i]);
	// printf("\n");
	// printf("l_cmd pre=%s<end\n", sub->l_cmd);
	return (0);
}
