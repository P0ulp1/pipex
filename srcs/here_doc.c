/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:35:06 by phautena          #+#    #+#             */
/*   Updated: 2024/09/30 17:02:38 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(char *argv[])
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
		return (1);
	return (0);
}

void	here_doc_write(char *lim, int fd_in)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, lim, ft_strlen(lim)))
		{
			free(line);
			return ;
		}
		ft_putstr_fd(line, fd_in);
		free(line);
	}
}

int	cmds_doc(t_cmd **cmds, char *argv[], char *envp[], t_files *files)
{
	t_cmd	*cmd;
	char	*path;
	int		len;
	int		i;

	len = tab_len(argv - 1);
	i = 3;
	while (i < len - 2)
	{
		path = get_cmd_path(argv[i], envp);
		if (!path)
			ft_putstr_fd("Command not found\n", 2);
		cmd = new_cmd(path);
		if (!cmd)
			return (free_cmds(cmds), 1);
		free(path);
		cmd->args = get_cmd_args(argv[i]);
		if (!cmd->args)
			return (free_cmds(cmds), 1);
		cmd->files = files;
		cmd->pid = -1;
		cmd_to_end(cmds, cmd);
		i++;
	}
	return (0);
}
