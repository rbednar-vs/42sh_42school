/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell42.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:49 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/14 21:08:05 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL42_H
# define SHELL42_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>

// # include <stdio.h> //DELETE

# include "exit_status.h"
# include "builtin42.h"
# include "libft.h"
# include "libft_42.h"
# include "parser.h"
# include "readline.h"

# include "ft_printf.h" //If not used, delete
# include "get_next_line.h" //If not used, delete

# define 			MAX_HISTORY 10
# define			MAXDIR 255

typedef struct		s_prompt
{
	int				(*prompt_func)(void);
}					t_prompt;

/*
** @hist is an array with commands (not separated by \n but
** separated as they came to parser)
** @len is the number of lines (commands) in the history
** @last is counter of the last command saved in the history
** @start is a counter from which command from history file we start to
** fill out buffer - not to rewrite the whole buffer to the file but to add
** We need all
*/

typedef struct		s_history
{
	char			**hist;
	int				len;
	int				counter;
	int				last;
	int				start;
	int				start_control;
}					t_history;

/*
** @BSLASH is "\", @SCOLON is ";", @AND is "&", @DQUOTE is '"',
** @SQUOTE is "'", @OPAREN is "(", @CPAREN is ")", @OBRACKET is "["
** @CBRACKET is "]", @OBRACE is "{", CBRACE is "}", @DOLLAR is "$",
** @TILDA is "~", @PIPE is "|", @GTHAN is ">", @LTHAN is "<",
** @AST is "*", @EQUAL = "=", @ENTER is "\n", @COMENT is "#"
*/

enum				e_techline
{
	SPACE = 1,
	BSLASH,
	SCOLON,
	AND,
	DQUOTE,
	SQUOTE,
	OPAREN,
	CPAREN,
	OBRACKET,
	CBRACKET,
	OBRACE,
	CBRACE,
	DOLLAR,
	TILDA,
	PIPE,
	GTHAN,
	LTHAN,
	AST,
	EQUAL,
	ENTER,
	COMENT,
	GLUE,
	TEXT
};

/*
** @g_env - global variable with (char **environ) parameters
** @g_sh_var - shell variables
*/

char				**g_env;
char				**g_shvar;
char				**g_lovar;
t_prompt			g_prompt;
t_history			g_hist;

/*
** File environment42.c
*/

int					save_environment(void);
int					save_shell_variables(void);
int					save_local_variables(char *var);
int					save_history_variables(void);
size_t				find_in_variables(char **arr, size_t *j, char *name);

/*
** File signals_processing42.c
*/

int					signal_ctrl_c(void);
int					signal_ctrl_d(void);
int					route_exit(void);
int					signals_reroute(int from);
void				sig_fork(int sig);

/*
** File errors_handler42.c
*/

int					error_handler(int status, char *str);
int					syntax_errors(int status, char *str);

/*
** File clean_all42.c
*/

int					clean_everything(void);
int					clean_readline42(void);
int					clean_parser42(void);

#endif
