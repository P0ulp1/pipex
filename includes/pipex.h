/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:10:45 by phautena          #+#    #+#             */
/*   Updated: 2024/09/30 16:57:44 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_printf/includes/ft_printf.h"
# include "../Libft/libft.h"
# include "../GNL/get_next_line.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_files
{
	int	in;
	int	out;
}	t_files;

typedef struct s_cmd
{
	char			*path;
	char			**args;
	int				pid;
	int				to_read;
	int				to_write;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_files	*files;
}	t_cmd;

///pipex.c>>>
int		here_doc(char *argv[]);
///cmd.c>>>
char	**get_cmd_args(char *cmd);
char	*get_cmd_path(char *cmd, char *envp[]);
int		create_cmds(t_cmd **cmds, char *argv[], char *envp[], t_files *files);
int		parsing(char *argv[], t_files *files, t_cmd **cmds, char *envp[]);
///exec.c>>>
void	init_pipes(t_cmd **cmds);
void	wait_for_all(t_cmd **cmds);
void	execute_cmds(t_cmd **cmds, char *envp[]);
void	close_pipes(t_cmd **cmds);
void	pipex(t_cmd **cmds, char *envp[]);
///utils.c>>>
char	*dup_cmd(char *cmd);
int		init_files(char *argv[], t_files *files, int hd);
int		tab_len(char *tab[]);
int		cmds_size(t_cmd *cmds);
int		check_cmd(t_cmd *cmd);
///free.c>>>
void	return_error(void);
void	free_array(char **array);
void	free_cmds(t_cmd **cmds);
void	error_from_exec(t_cmd **cmds);
///list.c>>>
void	cmd_to_end(t_cmd **cmds, t_cmd *new);
t_cmd	*new_cmd(char *path);
///env.c>>>
char	**get_env(char *envp[]);
char	*get_env_path(char *envp[]);
char	**fix_env(char **env);
///here_doc.c>>>
int		here_doc(char *argv[]);
void	here_doc_write(char *lim, int fd_in);
int		cmds_doc(t_cmd **cmds, char *argv[], char *envp[], t_files *files);

#endif
