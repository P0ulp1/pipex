/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:21:46 by phautena          #+#    #+#             */
/*   Updated: 2024/09/27 15:38:22 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_to_end(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*temp;

	temp = *cmds;
	if (!temp)
	{
		*cmds = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	new->prev = temp;
	temp->next = new;
}

t_cmd	*new_cmd(char *path)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->path = ft_strdup(path);
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}
