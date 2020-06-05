#include "shell42.h"
#include "parser.h"
#include "builtin42.h"
#include "builtins_list.h"

char	*get_env(char *var)
{
	char	*val;
	size_t	i;
	size_t	len;

	val = 0;
	i = 0;
	printf("Warning: get_env() is deprecated. Use ft_find_var() instead\n");
	if (!g_env)
		return (NULL);
	len = ft_strlen(var);
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], var, len))
			break;
		i++;
	}
	if (g_env[i])
		val = ft_strdup(g_env[i] + len + 1);
	return (val);
}

/*
** So, let's talk about pipes:
** 1) If only PIPED_OUT -- create pipe
** 2) If only PIPED_IN -- delete pipe
*/

/*
** consider changing architecture to... well, something else
*/

int	exec_clean(char *path, int exit_status, char *err_msg)
{
	if (path)
		exit_status_variable(exit_status);
	free(path);
	if (err_msg)
		ft_putendl_fd(err_msg, STDERR_FILENO); // through error_handler
	return (exit_status);
}

/*
** Check if programm to start is buildin and if it is - start builtin
*/

int		ft_builtins_check(process *p, int flag)
{
	int	i;
	t_ltree	xXx_PLACEHOLDER_xXx;

	i = 1;	
	while (g_builtins[i])
	{
		if (!ft_strcmp(p->argv[0], g_builtins[i]))
		{
			if (flag)
			{
				xXx_PLACEHOLDER_xXx.ar_c = p->argc;
				vec_dup(&xXx_PLACEHOLDER_xXx.ar_v, p->argv);
				vec_dup(&xXx_PLACEHOLDER_xXx.envir, p->envp);
				exit_status_variable(g_builtins_func[i](&xXx_PLACEHOLDER_xXx));
				ft_arrdel(xXx_PLACEHOLDER_xXx.ar_v);
				ft_arrdel(xXx_PLACEHOLDER_xXx.envir);
				p->completed = 1;
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

int		fd_list_process(t_ltree *pos, int mode)
{
	t_list		*fd_list;
	t_fd_redir	*redir;

	if (!mode)
	{
		std_save(0);
		fd_list = pos->fd;
		while (fd_list)
		{
			redir = (t_fd_redir *)fd_list->content;
			if (redir->fd_in != CLOSE)
				dup2(redir->fd_in, redir->fd_out);
			else
			{
				dup2(redir->fd_out, redir->fd_out); //decide, what to do here
				close(redir->fd_out);
			}
			fd_list = fd_list->next;
		}
	}
	else
		std_save(1);
	return (0);
}
