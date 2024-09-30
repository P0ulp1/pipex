/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:51:37 by phautena          #+#    #+#             */
/*   Updated: 2024/09/30 17:00:08 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_from_exec(t_cmd **cmds)
{
	close_pipes(cmds);
	free_cmds(cmds);
	return_error();
	if (!access("temp.txt", F_OK))
		unlink("temp.txt");
	exit(1);
}

void	return_error(void)
{
	static int	error;

	if (!error)
		perror("Pipex error\n");
	error = 1;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	cmd = *cmds;
	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		if (temp->args)
			free_array(temp->args);
		if (temp->path)
			free(temp->path);
		free(temp);
	}
	cmds = NULL;
}
