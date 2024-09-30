/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:27:17 by phautena          #+#    #+#             */
/*   Updated: 2024/09/30 16:13:33 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_env(char *envp[])
{
	char	*env;
	char	**splitted;
	char	**fixed;

	env = get_env_path(envp);
	if (!env)
		return (NULL);
	splitted = ft_split(env, ':');
	free(env);
	if (!splitted)
		return (NULL);
	fixed = fix_env(splitted);
	free_array(splitted);
	if (!fixed)
		return (NULL);
	return (fixed);
}

char	*get_env_path(char *envp[])
{
	char	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			env = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			if (!env)
				return (NULL);
			break ;
		}
		i++;
	}
	return (env);
}

char	**fix_env(char **env)
{
	char	**res;
	int		len;
	int		i;

	len = 0;
	while (env[len])
		len++;
	res = malloc((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (env[i])
	{
		res[i] = ft_strjoin(env[i], "/");
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}
