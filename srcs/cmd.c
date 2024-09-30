/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:52:16 by phautena          #+#    #+#             */
/*   Updated: 2024/09/30 16:57:55 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_cmds(t_cmd **cmds, char *argv[], char *envp[], t_files *files)
{
	t_cmd	*cmd;
	char	*path;
	int		len;
	int		i;

	len = tab_len(argv - 1);
	i = 2;
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

char	**get_cmd_args(char *cmd)
{
	char	**flags;
	char	**res;
	int		len;
	int		i;

	flags = ft_split(cmd, ' ');
	if (!flags)
		return (NULL);
	len = tab_len(flags);
	res = malloc((len + 1) * sizeof(char *));
	if (!res)
		return (free_array(flags), NULL);
	i = 0;
	while (flags[i])
	{
		res[i] = ft_strdup(flags[i]);
		if (!res[i])
			return (free_array(flags), NULL);
		i++;
	}
	res[i] = NULL;
	free_array(flags);
	return (res);
}

char	*get_cmd_path(char *cmd, char *envp[])
{
	char	**env;
	char	**args;
	char	*path;
	int		i;

	args = ft_split(cmd, ' ');
	if (!args)
		return (NULL);
	if (access(args[0], X_OK) == 0)
		return (free_array(args), dup_cmd(args[0]));
	env = get_env(envp);
	if (!env)
		return (free_array(args), NULL);
	i = 0;
	while (env[i])
	{
		path = ft_strjoin(env[i], args[0]);
		if (!path)
			return (free_array(args), NULL);
		if (access(path, X_OK) == 0)
			return (free_array(env), free_array(args), path);
		free(path);
		i++;
	}
	return (free_array(env), free_array(args), NULL);
}

int	parsing(char *argv[], t_files *files, t_cmd **cmds, char *envp[])
{
	int	hd;

	hd = here_doc(argv);
	if (init_files(argv, files, hd))
		return (1);
	if (hd)
	{
		if (cmds_doc(cmds, argv, envp, files))
			return (2);
	}
	else
	{
		if (create_cmds(cmds, argv, envp, files))
			return (3);
	}
	return (0);
}
