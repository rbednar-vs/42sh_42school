
#include "parser.h"

/*
** Do we include pos_end? This should be discussed
*/

/*
** This function replaces any symbols which are considered to be spaces to
** actual spaces. Probably should be called before techline form.
*/

int		spaceizer(char *str)
{
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str == '\t')
			*str = ' ';
		str++;
	}
	return (0);
}

char	**get_argv(char *exec_cmd)
{
	char	**ret;

	if (spaceizer(exec_cmd))
		return (0);
	return (ret = ft_strsplit(exec_cmd, ' '));
}

/*
** This function returns positive integer, which is argc, or -1 in case of any
** illegal symbols discovered
*/

int		get_argc(size_t pos_start, size_t pos_end)
{
	size_t	iter;
	int		ret;

	iter = pos_start;
	ret = 0;
	while (iter < pos_end)
	{
		if (g_techline.line[iter] == 1)
			iter++;
		else if (!g_techline.line[iter])
		{
			ret++;
			while (!g_techline.line[iter])
				iter++;
		}
		else
			return (-1);
	}
	return (ret);
}

/*
** It is assumed, that we receive starting and ending position with only space
** specchars. By the way, we also have to process "raw" tabs (maybe as spaces --
** there is no difference)
*/

int		exec_init(t_ltree *pos)
{
	char	*exec_cmd;
	char	**exec_av;
//	int		exec_ac;

	write(1, "KEKESTAN!\n", 10);
	if (!(exec_cmd = (char *)malloc(pos->end - pos->start + 1)))
		return (-1);
	ft_memcpy(exec_cmd, g_cmd + pos->start, pos->end - pos->start);
//	if ((exec_ac = get_argc(pos_start, pos_end)) == -1)
//		return (-1);
	if (!(exec_av = get_argv(exec_cmd)))
		return (-1);
	free(exec_cmd);
	return (exec_core(exec_av));
}
