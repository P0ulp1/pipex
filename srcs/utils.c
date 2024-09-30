/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:53:01 by phautena          #+#    #+#             */
/*   Updated: 2024/09/30 16:56:29 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*dup_cmd(char *cmd)
{
	char	*res;

	res = ft_strdup(cmd);
	if (!res)
		return (NULL);
	return (res);
}

int	init_files(char *argv[], t_files *files, int hd)
{
	int	len;
	int	fd_in;
	int	fd_out;

	len = tab_len(argv) - 1;
	if (hd)
	{
		fd_in = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
		here_doc_write(argv[2], fd_in);
		if (fd_in > 0)
			close(fd_in);
		fd_in = open("temp.txt", O_RDONLY);
	}
	else
		fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		return_error();
	fd_out = open(argv[len], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_out < 0)
		return_error();
	files->in = fd_in;
	files->out = fd_out;
	return (0);
}

int	tab_len(char *tab[])
{
	int	i;

	if (!tab)
		return (1);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	cmds_size(t_cmd *cmds)
{
	t_cmd	*temp;
	int		i;

	temp = cmds;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

int	check_cmd(t_cmd *cmd)
{
	if (!cmd->path)
		return (1);
	if (access(cmd->path, X_OK) != 0)
		return (2);
	if (cmd->to_read < 0)
		return (3);
	if (cmd->to_write < 0)
		return (4);
	return (0);
}
