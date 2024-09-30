/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:15:05 by phautena          #+#    #+#             */
/*   Updated: 2024/09/30 16:23:24 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipes(t_cmd **cmds)
{
	t_cmd	*temp;
	int		pipefd[2];
	int		nb_process;

	temp = *cmds;
	temp->to_read = temp->files->in;
	nb_process = cmds_size(temp) - 1;
	while (nb_process > 0)
	{
		if (pipe(pipefd) < 0)
			ft_putstr_fd("Error", 2);
		temp->to_write = pipefd[1];
		if (temp->next)
			temp->next->to_read = pipefd[0];
		temp = temp->next;
		nb_process--;
	}
	temp->to_write = temp->files->out;
}

void	close_pipes(t_cmd **cmds)
{
	t_cmd	*temp;

	temp = *cmds;
	while (temp)
	{
		if (temp->to_read > -1)
			close(temp->to_read);
		if (temp->to_write > -1)
			close(temp->to_write);
		temp = temp->next;
	}
}

void	execute_cmds(t_cmd **cmds, char *envp[])
{
	t_cmd	*temp;

	temp = *cmds;
	while (temp)
	{
		temp->pid = fork();
		if (temp->pid == 0)
		{
			if (check_cmd(temp))
				error_from_exec(cmds);
			dup2(temp->to_write, STDOUT_FILENO);
			dup2(temp->to_read, STDIN_FILENO);
			close_pipes(cmds);
			execve(temp->path, temp->args, envp);
		}
		if (temp->pid < 0)
			error_from_exec(cmds);
		temp = temp->next;
	}
	close_pipes(cmds);
	wait_for_all(cmds);
}

void	wait_for_all(t_cmd **cmds)
{
	t_cmd	*temp;

	temp = *cmds;
	while (temp)
	{
		if (temp->pid > -1)
			waitpid(temp->pid, NULL, 0);
		temp = temp->next;
	}
}

void	pipex(t_cmd **cmds, char *envp[])
{
	init_pipes(cmds);
	if ((*cmds)->to_read > -1)
		dup2((*cmds)->files->in, STDIN_FILENO);
	execute_cmds(cmds, envp);
}
