/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_modes_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 00:07:44 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/03/23 16:47:27 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_fc_edit_mode_flags_off(int *flags)
{
	if (*flags & FLAG_L)
		*flags &= ~FLAG_L;
	if (*flags & FLAG_S)
		*flags &= ~FLAG_S;
	if (!(*flags & FLAG_E))
		*flags |= FLAG_E;
	if (*flags & FLAG_N)
		*flags &= ~FLAG_N;
	return (HIST_EXEC);
}

int					btin_fc_exec_mode_flags_off(int *flags)
{
	if (!(*flags & FLAG_S))
		*flags |= FLAG_S;
	if (*flags & FLAG_E)
		*flags &= ~FLAG_E;
	if (*flags & FLAG_L)
		*flags &= ~FLAG_L;
	if (*flags & FLAG_R)
		*flags &= ~FLAG_R;
	if (*flags & FLAG_N)
		*flags &= ~FLAG_N;
	return (HIST_EXEC);
}

int					btin_fc_list_mode_flags_off(int *flags)
{
	if (!(*flags & FLAG_L))
		*flags |= FLAG_L;
	if (*flags & FLAG_E)
		*flags &= ~FLAG_E;
	if (*flags & FLAG_S)
		*flags &= ~FLAG_S;
	return (HIST_EXEC);
}

int					btin_fc_other_flags(char argvij, int *flags)
{
	if (!(argvij == 'r' || argvij == 'n'))
	{
		error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), "fc");
		usage_btin("fc");
		return (HIST_ERROR);
	}
	else if (argvij == 'r')
		*flags |= FLAG_R;
	else if (argvij == 'n')
		*flags |= FLAG_N;
	return (0);
}