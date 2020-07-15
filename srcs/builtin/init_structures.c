#include "shell42.h"
#include "builtin42.h"
#include "builtins_list.h"

t_btin_fc			*init_btin_fc(void)
{
	t_btin_fc		*fc;

	fc = (t_btin_fc*)ft_xmalloc(sizeof(t_btin_fc));
	fc->flag = 0;
	fc->editor = NULL;
    fc->first = 0;
	fc->last = 0;
	fc->s_comp = NULL;
	fc->s_cmd = NULL;
	return (fc);
}

int					btin_return_exit_status(void)
{
	int				li;
	int				sy;
	
	li = find_in_variable(&sy, "?");
	return (ft_atoi(&g_envi[li][sy]));
}

int					btin_check_arg_if_cmd_name(char *arg)
{
	int				i;
	int				answer;

	i = 0;
	if (ft_isalnum(arg[i]) || arg[i] == '_' ||
		(arg[i] == '.' && ft_isalnum(arg[i])))
	{
		// answer = check_if_alias(arg);
		// if (answer >= 0)
		// 	return (ARG_ALIAS);
		answer = check_if_builtin(arg);
		if (answer >= 0)
			return (ARG_BUILTIN);
		return (0);
	}
	return (ARG_INVALID);
}

int					check_if_builtin(char *cmd_name)
{
	int				i;

	i = 1;	
	while (g_builtins[i])
	{
		if (!ft_strcmp(cmd_name, g_builtins[i]))
			return (i);
		i++;
	}
	return (-1);
}