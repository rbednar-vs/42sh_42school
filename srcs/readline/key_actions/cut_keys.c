/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 18:06:09 by tmp               #+#    #+#             */
/*   Updated: 2020/08/25 20:31:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					backspace_cutcharbefore(void)
{
	char			*swap;
	int				len_swap;
	char			*save_yank;

	check_after_line();
	if (g_rline.pos <= 0)
		return (incorrect_sequence());
	undo(0);
	save_yank = ft_strndup(g_rline.cmd + g_rline.pos - 1, 1);
	make_ctrl_p(0, save_yank);
	swap = g_rline.cmd + g_rline.pos;
	len_swap = ft_strlen(swap);
	if (g_rline.cmd[g_rline.pos - 1] == '\n')
		return (backspace_newline(swap, len_swap));
	ft_strcpy(g_rline.cmd + g_rline.pos - 1, swap);
	ft_bzero(g_rline.cmd + g_rline.pos - 1 + len_swap,
		g_rline.cmd_buff_len - g_rline.cmd_len);
	g_rline.cmd_len--;
	arrow_left_jumpcharleft();
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

int					backspace_newline(char *swap, int len_swap)
{
	int				pos_back;

	pos_back = g_rline.pos;
	arrow_left_jumpcharleft();
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
		&g_rline.pos_y, 1);
	ft_strcpy(g_rline.cmd + pos_back - 1, swap);
	ft_bzero(g_rline.cmd + pos_back - 1 + len_swap,
		g_rline.cmd_buff_len - g_rline.cmd_len);
	g_rline.cmd_len--;
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

int					delete_cutcharunder(void)
{
	char			*swap;
	int				len_swap;
	char			*save_yank;

	check_after_line();
	if (g_rline.pos == 0 && g_rline.cmd_len == 0)
	{
		if (route_exit() == OUT)
			return (OUT);
	}
	if (g_rline.pos < 0 || g_rline.pos >= g_rline.cmd_len)
		return (incorrect_sequence());
	undo(0);
	save_yank = ft_strndup(g_rline.cmd + g_rline.pos, 1);
	make_ctrl_p(0, save_yank);
	swap = g_rline.cmd + g_rline.pos + 1;
	len_swap = ft_strlen(swap);
	ft_strcpy(g_rline.cmd + g_rline.pos, swap);
	ft_bzero(g_rline.cmd + g_rline.pos + len_swap,
		g_rline.cmd_buff_len - g_rline.cmd_len);
	g_rline.cmd_len--;
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

int					delete_till_compl(int delete)
{
	char			*swap;
	int				len_swap;
	int				i;

	if (g_rline.pos > 0)
	{
		swap = g_rline.cmd + g_rline.pos;
		len_swap = ft_strlen(swap);
		ft_strcpy(g_rline.cmd + g_rline.pos - delete, swap);
		ft_bzero(g_rline.cmd + g_rline.pos - delete + len_swap,
			g_rline.cmd_buff_len - ft_strlen(g_rline.cmd));
		g_rline.cmd_len -= delete;
		i = -1;
		while (++i < delete)
			arrow_left_jumpcharleft();
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
			&g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	else
		return (incorrect_sequence());
	return (0);
}

int					esc_r_clearline(void)
{
	char			*save_yank;

	check_after_line();
	save_yank = ft_strdup(g_rline.cmd);
	make_ctrl_p(0, save_yank);
	while (g_rline.pos)
		arrow_left_jumpcharleft();
	tputs(g_cap.cd, 1, printc);
	ft_bzero(g_rline.cmd, g_rline.cmd_buff_len);
	g_rline.cmd_len = 0;
	return (0);
}
