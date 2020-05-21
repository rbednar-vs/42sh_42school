#include "shell42.h"

/*
** Environmental shell variables - are dinamic, exist within the session,
** the function save_environment_variables saves the parent process
** environ to e-bash @g_env.
**
** Can be changed by assignment (HOME=aaa)
** or export (export HOME=aaa)
** and a new line added by export-builtin (export FOO=bar)
*/

int					save_environment_variable(int num)
{
	extern char		**environ;
	int				i;

	i = 0;
	while (environ[i])
	{
		if (num + 12 == g_var_size)
		{
			g_envi = ft_realloc_array(&g_envi, g_var_size, g_var_size * 2);
			g_var_size *= 2;
		}
		g_envi[num] = (char*)ft_xmalloc((ft_strlen(environ[i] + 2) * (sizeof(char))));
		ft_strcpy(g_envi[num] + 1, environ[i]);
		g_envi[num][0] |= ENV_VIS;
		g_envi[num][0] |= SET_VIS;
		num++;
		i++;
	}
	return (num);
}

/*
** Shell readonly variables - always static, array @g_rdovar
**
** Can be only read by the user and corrected only within e-bash program
*/

char				*ft_add_rdovar(char *first, char *scnd, int flag)
{
	char	*res;

	res = (char*)ft_xmalloc((ft_strlen(first) + ft_strlen(scnd) + 2) * (sizeof(char)));
	ft_strcpy(res + 1, first);
	if (scnd)
		ft_strcpy(res + ft_strlen(first) + 1, scnd);
	if (flag != 2)
		res[0] |= READONLY;
	if (flag != 1)
		res[0] |= SET_VIS;
	return (res);
}

int					save_readonly_variable()
{
	char	*tmp;

	g_envi[0] = ft_add_rdovar("?=0", NULL, 1);
	g_envi[1] = ft_add_rdovar("0=e-bash", NULL, 1);
	g_envi[2] = ft_add_rdovar("42SH_SUBSHELL=0", NULL, 1);
	g_envi[3] = ft_add_rdovar("42SH_PARSER=0", NULL, 1);
	g_envi[4] = ft_add_rdovar("42SH_NONINTERACTIVE=0", NULL, 1);
	tmp = getcwd(NULL, MAXDIR);
	g_envi[5] = ft_add_rdovar("PWD=", tmp, 0);
	g_envi[6] = ft_add_rdovar("OLDPWD", tmp, 0);
	g_envi[7] = ft_add_rdovar("42SH=", tmp, 0);
	free(tmp);
	tmp = ft_itoa(getuid());
	g_envi[8] = ft_add_rdovar("UID=", tmp, 0);
	free(tmp);
	tmp = ft_itoa(geteuid());
	g_envi[9] = ft_add_rdovar("EUID=", tmp, 0);
	free(tmp);
	tmp = ft_itoa(getppid());
	g_envi[10] = ft_add_rdovar("PPID=", tmp, 0);
	free(tmp);
	tmp = ft_itoa(getpid());
    g_envi[11] = ft_add_rdovar("$=", tmp, 1);
    free(tmp);
	return (12);
}

/*
** Shell working variables - always static, array @g_shvar
**
** Can be changed by assignment (HISTFILE=5), can NOT be added
** If there is an export variable (export HISTFILE=5)
** the variable starts to be visible in @g_env (by env command)
*/

int					save_shell_variable(int num)
{
	char			*tmp;

	g_envi[num++] = ft_add_rdovar("HISTFILE=", NULL, 2);
	tmp = ft_itoa(MAX_HISTBUF);
	g_envi[num++] = ft_add_rdovar("HISTSIZE=", tmp, 2);
	free(tmp);
	tmp = ft_itoa(MAX_HISTFILE);
	g_envi[num++] = ft_add_rdovar("HISTFILESIZE=", tmp, 2);
	free(tmp);
	g_envi[num++] = ft_add_rdovar("FCEDIT=vim", NULL, 2);
	return (num);
}

/*
** Shell local variables - dinamic, exist within the session
** @g_lovar in e-bash
** 
** Can be added and changed by assignment (fuu=bar)
** And if already exists in @g_lovar and
** is used in export (export fuu=bbb),
** the variable starts to be visible in @g_env (by env command)
*/

int					create_env(void)
{
	int		num;

	g_envi = (char **)ft_xmalloc(ENV_BUFFER * sizeof(char*));
	num = save_readonly_variables();
	num = save_shell_variable(num);
	num = save_environment_variable(num);
	return (0);
}

int                 exit_status_variables(int status)
{
    char            *tmp;

    tmp = ft_itoa(status);
    ft_bzero(&g_envi[0][2], MAX_EXIT_STATUS - 2);
   	ft_strcpy(&g_envi[0][2], tmp);
    free(tmp);
    return (0);
}
