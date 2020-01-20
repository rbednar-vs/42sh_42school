/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:27:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/20 14:22:33 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** @g_tablevel is a counter according to that we complete this or that line
** from the g_menu
** @g_complete - is a string, according to which we search
** options for completion
** @g_menu - the full menu for completion
*/

size_t				g_tablevel;
char				*g_complete;
char				**g_menu;

static char			*path_parse(void)
{
	size_t			i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], "PATH=", 5) == 0)
			return (g_env[i] + 5);
		i++;
	}
	//список builtin и измерение самого длинного слова + общее количество
	return (NULL);
}

/*
** @pool = pool of variables: binary-files (1), variables (2),
** arguments (3), bell (nothing can be done - 0);
*/

int					auto_completion(void)
{
	size_t			pos_back;
	size_t			total;
	int				max_len;
	char			*tech_line;

	pos_back = g_rline.pos;
	max_len = 0;
	if (!(g_rline.flag & TAB))
	{
		g_complete = fill_complete(pos_back); //по моей логике только в случае, когда в строке нет ничего complete будет пустым, во всех остальных случаях он будет заполненным
		tech_line = get_techline_compl(g_complete, g_rline.pos);
		g_menu = route_menu_receipt(tech_line, pos_back, &total, &max_len);
		if (g_menu == NULL)
		{
			free(g_complete);
			return (incorrect_sequence());
		}
		print_menu(pos_back, g_menu, total, max_len);
		g_rline.flag |= TAB;
		g_tablevel = 0;
	}
	else
	{
		g_tablevel++;
		//TODO подстановка слова
	}
	return (0);
}

char				**route_menu_receipt(char *tech_line,
						size_t tech_len, size_t *total, int *max_len)
{
	char			**menu;
	int				pool;
	int				tmp;		

	if (tech_line == NULL)
		menu = ft_path_pars("", path_parse(), total, max_len);
	else
	{
		if ((tmp = analyse_techline_compl(tech_line, tech_len, &pool)) == 0)
			return (NULL);
		if (pool == 1)
			menu = ft_path_pars(g_complete + tmp - 1,
				path_parse(), total, max_len);
		else if (pool == 2)
			menu = get_variables(g_complete + tmp - 1, total, max_len);
		else
			menu = get_arguments(g_complete + tmp - 1, total, max_len);	
	}
	return (menu);
}

char				*fill_complete(size_t pos_back)
{
	size_t			beg_word;
	size_t			end_word;
	size_t			space;
	char			*tmp;
	char			*complete;

	beg_word = g_rline.pos;
	end_word = beg_word;
	if (!ft_isalnum(g_rline.cmd[beg_word]) && beg_word > 0
		&& ft_isalnum(g_rline.cmd[beg_word - 1]))
		beg_word--;
	while (beg_word > 0 && ft_isalnum(g_rline.cmd[beg_word]))
		beg_word--;
	while (g_rline.cmd[end_word] && end_word < g_rline.pos
		&& ft_isalnum(g_rline.cmd[end_word]))
		end_word++;
	space = beg_word;
	while (space > 0 && g_rline.cmd[space] == ' ')
		space--;
	tmp = ft_strndup(g_rline.cmd + beg_word, end_word - beg_word);
	complete = ft_strtrim(tmp);
	free(tmp);
	return (complete);
}

int					check_menu(void) //поправить возврат после нажатия символа
{
	if (g_rline.flag & TAB)
	{
		// free(g_complete);
		// clean_menu();
		g_rline.flag &= ~TAB;
	}
	return (0);
}
