
#ifndef FC_H
# define FC_H

# define		POSIX_FC_DIFF 16

# define		HIST_ERROR -2
# define		HIST_EXEC -1
# define		HIST_SEARCH 1

# define		FLAG_N 0x1
# define		FLAG_R 0x2
# define		FLAG_S 0x4
# define		FLAG_L 0x8
# define		FLAG_E 0x10
# define		ARG_FIRST 0x1
# define		ARG_SECOND 0x2
# define		ARG_SECOND 0x2
# define        FC_COMP_ARRAY 10

typedef	struct	s_btin_fc
{
	int			flag;
	char		*editor;
	int			first;
	int			last;
	int			first_buf;
	int			last_buf;
	char		**s_comp;
	char		*s_cmd;
}				t_btin_fc;

/*
** File fc.c
*/

int				btin_fc_find_mode(char **argv, t_btin_fc **fc_arg,
					int *flags);
int				btin_fc_other_args(char **argv, int i,
					t_btin_fc **fc_arg, int *flags);
int				btin_fc_list_mode(char **argv, int j, t_btin_fc **fc_arg,
					int *flags);
int				btin_fc_exec_mode(char **argv, int j, t_btin_fc **fc_arg,
					int *flags);

/*
** File fc_modes_l.c
*/

int				btin_fc_list_check_line_args(char **argv, int j,
					t_btin_fc **fc_arg, int *flags);
int				btin_fc_list_check_other_args(char **argv,
					t_btin_fc **fc_arg, int *flags);
int				btin_fc_list_mode_num_args(char **argv, int i,
                    t_btin_fc **fc_arg, int *flags);
int				btin_fc_list_nums_no_error(char **argv,
					t_btin_fc **fc_arg, int *flags);
int				btin_fc_calculate_nums__list(int buffer, int from);

/*
** File fc_mode_s.c
*/

int				btin_fc_exec_check_other_args(char **argv,
					t_btin_fc **fc_arg, int *flags);
int				btin_fc_exec_check_line_args(char **argv, int j,
					t_btin_fc **fc_arg, int *flags);
int				btin_fc_exec_mode_comp(char **argv,
					t_btin_fc **fc_arg, int *flags);
int				btin_fc_exec_check_invalid(char **argv,
					t_btin_fc **fc_arg, int *flags);
int				btin_fc_one_int__exec(t_btin_fc **fc_arg);


/*
** File fc_mode_e.c
*/

int				btin_fc_edit_mode(char **argv, t_btin_fc **fc_arg,
					int *flags);
int				btin_fc_edit_other_args(char **argv,
					t_btin_fc **fc_arg, int *flags);
int				btin_fc_edit_mode_num_args(char **argv, int i,
					t_btin_fc **fc_arg, int *flags);
int				btin_fc_two_ints__edit(t_btin_fc **fc_arg);
int				btin_fc_save_editor(char **argv, int i,
					int j, t_btin_fc **fc_arg);

/*
** File fc_num_calc.c
*/

int				btin_fc_two_ints__list(t_btin_fc **fc_arg, int *flags);
int				btin_fc_positive_int__list(int value,
					int from, int to);
int				btin_fc_negative_int__list(int value);
int				btin_fc_positive_int__exec(int value, int from,
					int to);
int				btin_fc_negative_int__exec(int value);

/*
** File fc_modes_flags.c
*/

int				btin_fc_edit_mode_flags_off(int *flags);
int				btin_fc_exec_mode_flags_off(int *flags);
int				btin_fc_list_mode_flags_off(int *flags);
int				btin_fc_other_flags(char argvij, int *flags);

/*
** File fc_modes_no_arguments.c
*/

int				btin_fc_exec_no_args(t_btin_fc **fc_arg, int *flags);
int				btin_fc_list_mode_no_args(t_btin_fc **fc_arg, int *flags);
int				btin_fc_edit_no_args(t_btin_fc **fc_arg, int *flags);

/*
** File fc_exec.c
*/

int				btin_fc_route_execution(t_btin_fc *fc_arg, int flags,
					char **envir);
int				btin_fc_execute_edition(t_btin_fc *fc_arg, int flags,
					char **envir);
int				btin_fc_execute_list(t_btin_fc *fc_arg, int flags, int flag);
int				btin_fc_execute_list_reverse(t_btin_fc *fc_arg, int flags, int flag);
int				btin_fc_execute_execution(t_btin_fc *fc_arg, int flags);

/*
** File fc_exec_modes_s.c
*/

int				btin_fc_exec_mode_add_comp(t_btin_fc **fc_arg, char *comp);
char			*make_history_assignments(t_btin_fc *fc_arg, char *cmd);
char			*insert_history_assignment(char *buf, int *buf_len,
					char *change, char *what);
char			*insert_history_assignment_whole_line(char *buf, int *buf_len,
					char *change, int len_change);
int				btin_fc_save_parser_globals(int flag);

/*
** File fc_exec_modes_e.c
*/

t_ltree			*btin_fc_before_exec(t_btin_fc *fc_arg,
					char **envir, char *tmpfile);
int				btin_fc_write_to_tmpfile(t_btin_fc *fc_arg,
					int flags, int fd);
int				btin_fc_read_from_tmpfile(char *tmpfile);
int				btin_fc_execute_edit_reverse(t_btin_fc *fc_arg,
					int flags, int fd, int flag);
int				btin_fc_execute_edit(t_btin_fc *fc_arg,
					int flags, int fd, int flag);

/*
** File fc_tmpfile.c
*/

int				ft_tmpfile_fc(char *tmpl, char **tmp_nameto_vim);

#endif