
#include "shell42.h"
#include "jobs.h"

void	wait_for_job (job *j)
{
	while (!job_is_stopped (j, 0) && !job_is_completed (j));
}

/*
** Moves job to foreground: gives controlling terminal, sends continue signal if
** it is needed, blocks further work until it reports and performs cleanup in
** case job is completed (we aren't able to do this in SIGCHLD handler, as it
** will result in race condition and possible segfaults)
*/

void	put_job_in_foreground (job *j, int cont)
{
	j->fg = 1;
	j->clean = 0;
	tcsetpgrp(STDIN_FILENO, j->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &j->tmodes);
		if (kill(- j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)"); /* TODO: change */
    }

	wait_for_job(j);
	tcsetpgrp(STDIN_FILENO, g_shell_pgid);
	tcgetattr(STDIN_FILENO, &j->tmodes);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell_tmodes);
	j->clean = 1;
	if (job_is_completed(j))
		free_job(j);
}

/*
** Puts job in the background and informs user about this action. If the cont
** argument is true, sends process group a SIGCONT signal to wake it up.
*/

void	put_job_in_background (job *j, int cont)
{
	j->fg = 0;
	j->clean = 1;
	ft_printf("[%d] %d\n", j->jid, j->pgid);
	if (cont)
		if (kill (-j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)"); //correct
}

/*
** Determines further shell actions based on shell mode (interactive or not) and
** job FG mode (j->fg == 1 -- foreground, j->fg == 0 -- background)
*/

int		bg_fg_wait(job *j)
{
	if (!g_is_interactive)
		wait_for_job(j);
	else if (j->fg)
		put_job_in_foreground(j, 0);
	else
		put_job_in_background(j, 0);
	return (0);
}