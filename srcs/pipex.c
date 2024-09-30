/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:11:46 by phautena          #+#    #+#             */
/*   Updated: 2024/09/30 17:00:12 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmds;
	t_files	files;

	cmds = NULL;
	if (argc < 5)
		return (ft_printf("At least 5 arguments are required.\n"));
	if (parsing(argv, &files, &cmds, envp))
		return (1);
	pipex(&cmds, envp);
	free_cmds(&cmds);
	if (!access("temp.txt", F_OK))
		unlink("temp.txt");
	return (0);
}
