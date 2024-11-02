/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:15:21 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/02 21:27:40 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	wait_heredoc_child(pid_t pid)
{
	int	status;

	// printf("PID : %d | waiting for child... (wait_child)\n", getpid());
	if (waitpid(pid, &status, 0) == -1)
	{
		err_msg("waitpid", strerror(errno), 0);
		clean_exit_shell(FAILURE);
	}
	if (WEXITSTATUS(status) == CTRL_C)
	{
		ft_exit_status(CTRL_C, ADD);
		return (STOP_EXEC);
	}
	else
		return (SUCCESS);
		// printf("PID : %d | a child is done ! (wait_child)\n", getpid());
}

static int	__fill_all_heredoc(t_data *d, t_redir_lst *r)
{
	t_redir_lst	*curr;
	int			latest_read_fd;

	curr = r;
	latest_read_fd = 0;
	set_signals_in_heredoc();
	while (curr != NULL)
	{
		if (curr->type == HERE_DOC)
		{
			if (latest_read_fd != 0)
				close(latest_read_fd);
			latest_read_fd = open_heredoc(d, curr->limiter);
			if (latest_read_fd == STOP_EXEC)
				return (latest_read_fd);
		}
		curr = curr->next;
	}
	return (latest_read_fd);
}

int	handle_heredoc(t_data *d, t_exec_lst **e_lst)
{
	t_exec_lst	*curr;

	curr = *e_lst;
	while (curr != NULL)
	{
		if (curr->heredoc_nb > 0)
		{
			curr->latest_hd = __fill_all_heredoc(d, curr->redir);
			if (curr->latest_hd == STOP_EXEC)
			{
				curr->latest_hd = 0;
				return (STOP_EXEC);
			}
		}
		curr = curr->next;
	}
	return (SUCCESS);
}
