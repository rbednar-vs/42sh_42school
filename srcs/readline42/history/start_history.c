/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:02:53 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/03 18:18:14 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

#define MAXDIR 255

int				start_history(void)
{
	int			fd;
	size_t		j;
	size_t		i;

	init_history();
	i = find_in_variables(g_shvar, &j, "HISTFILE=");
	fd = open(g_shvar[i] + j, O_RDONLY);
	// printf("FD %d - %s\n", fd, g_shvar[i]);
	if (fd == -1)
		return (0);
	save_hist_buffer(fd);

	i = 0;
	while (g_hist.hist[i])
	{
		printf("%lu - %s\n", i + 1, g_hist.hist[i]);
		i++;
	}

	close(fd);
	return (0);
}

void			init_history(void)
{
	size_t		i;
	int			tmp;

	i = 0;
	while (ft_strncmp(g_shvar[i], "HISTFILESIZE=",
		(tmp = ft_strchri(g_shvar[i], '=') + 1)) != 0)
		i++;
	g_hist.len = ft_atoi(&g_shvar[i][tmp]);
	g_hist.hist = (char**)ft_xmalloc(sizeof(char*) * (g_hist.len + 1));
	g_hist.hist[g_hist.len] = 0;
	g_hist.last = -1;
	g_hist.start = 0;
	g_hist.counter = 0;
}

/*
** We find the directory we are in a try to find a history file. If we find -
** send it back to the start_history function and save everything from file to
** the buffer. If we can not open it - the buffer will start with the first
** command in the session
*/

char			*define_history_file(void)
{
	char		*dir;

	dir = (char*)ft_xmalloc(MAXDIR);
	getcwd(dir, MAXDIR);
	if (dir[0] == 0)
	{
		free(dir);
		return (NULL);
	}
	ft_strcat(dir, "/.42sh_history");
	return (dir);
}

/*
** We save the buffer if it exists amd change the working variable $HISTCMD
*/

int				save_hist_buffer(int fd)
{
	size_t		i;
	char		*tmp;

	i = 0;
	tmp = NULL;
	while (ft_gnl(fd, &tmp) > 0)
	{
		if (i >= g_hist.len)
		{
			g_hist.hist = ft_realloc_array(&g_hist.hist,
				g_hist.len, g_hist.len + MAX_HISTORY);
			g_hist.len += MAX_HISTORY;
		}
		g_hist.hist[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	free(tmp);
	g_hist.last = i - 1;
	g_hist.counter = i;
	g_hist.start = i;
	return (0);
}

int				check_if_histsize_changed(void)
{
	size_t		i;
	size_t		j;
	int			user_len;

	i = find_in_variables(g_shvar, &j, "HISTFILESIZE=");
	if (!ft_isdigit(g_shvar[i][j]))
		return (0);
	user_len = ft_atoi(g_shvar[i] + j);
	if (user_len < 0)
		return (0);
	else if (user_len > 0 && user_len > g_hist.len)
	{
		g_hist.hist = ft_realloc_array(&g_hist.hist,
			g_hist.len, user_len);
		g_hist.len = user_len;
	}
	return (0);
}
