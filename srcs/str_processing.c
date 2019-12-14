/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:07:05 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/14 19:42:44 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** @num_space - counts on which line is space found
** @num_pos - counts on which line is position found
** @beg - beginning of the word, its column
**
** We need the following: the line cursor is on (pos), the line space is on
** the column space is on (get it from i). And we have 3 variants:
** 1) pos and space are on the same line
** 2) pos and space are on the lines one after another (we clear from pos
** till the beginning of line and from the end of previous line till the space)
** 3) pos and space have several lines between them - we need to clear them too
*/

unsigned int		on_which_line(size_t cmd_pos, unsigned short col)
{
	unsigned int	i;

	i = 1;
	while (cmd_pos >= col * i)
		i++;
	return (i);
}

int					position_relative(unsigned short *x,
						unsigned short *y, size_t analyse)
{
	if (g_rline.prompt_len + analyse < g_screen.ws_col)
	{
		(x) ? *x = g_rline.prompt_len + analyse : 0;
		(y) ? *y = 1 : 0;
	}
	else
	{
		(x) ? *x = (g_rline.prompt_len + analyse) % g_screen.ws_col : 0;
		(y) ? *y = on_which_line(g_rline.prompt_len + analyse,
			g_screen.ws_col) : 0;
	}
	return (0);
}

int					move_cursor_back_after_print(short flag)
{
	size_t			tmp;
	unsigned short	new_x;
	unsigned short	new_y;

	g_rline.str_num = count_str_num();
	tmp = 0;
	if (flag == 0)
	{
		if (ft_strlen(g_rline.cmd) + g_rline.prompt_len ==
		g_screen.ws_col * g_rline.str_num)
		{
			putcap("sf");
			tmp = 1;
		}
	}
	if (position_relative(&new_x, &new_y, g_rline.pos))
		return (-1);
	position_cursor("ch", 0, new_x);
	if (g_rline.str_num + tmp - new_y == 1)
		putcap("up");
	else if (g_rline.str_num + tmp - new_y > 1)
		position_cursor("UP", 0, g_rline.str_num + tmp - new_y);
	return (0);
}

/*
** @direction can be left = 'l' or right = 'r'
*/

int					move_cursor_from_old_position(size_t pos_old,
						char direction)
{
	unsigned short	new_x;
	unsigned short	new_y;
	unsigned short	old_y;

	if (position_relative(0, &old_y, pos_old))
		return (-1);
	if (position_relative(&new_x, &new_y, g_rline.pos))
		return (-1);
	if (direction == 'l')
	{
		if (old_y - new_y == 1)
			putcap("up");
		else if (old_y - new_y > 1)
			position_cursor("UP", 0, old_y - new_y);
	}
	else
	{
		if (new_y - old_y == 1)
			putcap("do");
		else if (new_y - old_y > 1)
			position_cursor("DO", 0, new_y - old_y);
	}
	position_cursor("ch", 0, new_x);
	return (0);
}
