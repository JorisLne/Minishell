/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:43:03 by jlaine            #+#    #+#             */
/*   Updated: 2025/03/01 09:53:41 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_subshell(t_ast_subshell *subshell, t_shell *sh)
{
	pid_t	pid;
	int		status;

	pid = safe_fork(sh);
	if (pid == 0)
	{
		sh->in_main_process = false;
		set_signal_child_process();
		execute(subshell->child, O_EXIT, sh);
	}
	safe_wait(&status, sh);
	status = check_process_child_exit(status, NULL, sh);
	return (status);
}
