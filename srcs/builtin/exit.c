#include "shell42.h"
#include "builtin42.h"

int				btin_exit(t_ltree *pos)
{
	int			status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (pos->ar_c > 1)
		status = btin_exit_arguments(pos->ar_v);
	else
		status = 0;
	// ft_one_ltree_clear(pos); //почистить все листы
	fill_hist_in_file();
	clean_everything();
	exit(status);
}

int				btin_exit_arguments(char **ar_v)
{
	int			status;
	int			i;
	char		*str;

	status = 0;
	if (ft_strcmp(ar_v[1], "--help") == '0')
		return (usage_btin("exit"));
	i = (ar_v[1][0] && ar_v[1][0] == '-') ? 0 : -1;
	while (ar_v[1][++i])
		if (!(ar_v[1][i] >= '0' && ar_v[1][i] <= '9'))
		{
			str = ft_strjoin(ar_v[0], ": ");
			str = ft_strrejoin(str, ar_v[1]);
			error_handler(SYNTAX_ERROR | (ERR_NUMERIC << 9), str);
			usage_btin("exit");
			free(str);
			status = SYNTAX_ERROR;
			break ;
		}
	(status != SYNTAX_ERROR) ? status = ft_atoi(ar_v[1]) : 0;
	(status < 0) ? status &= 0xFF : 0;
	return (status);
}