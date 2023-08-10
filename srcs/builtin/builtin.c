/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:24:23 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/08 22:26:23 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_builtin(t_cmd *cmd, char ***env)
{
	int						i;
	static const char		*str[8] = {"pwd", "cd", "echo", "exit", "export", "unset", "env", NULL};
	static const t_builtin	func[7] = {ft_pwd, ft_cd, ft_echo, ft_exit, ft_export, ft_unset, ft_env};

	i = 0;
	if (!cmd)
		return (0);
	while (str[i])
	{
		if (!ft_strcmp(cmd->cmd, str[i]))
		{
			// ft_env(NULL, env);
			func[i](++cmd->arg, env);
			// ft_env(NULL, env);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_builtin_vrmnt(char *str)
{
	int					i;
	static const char	*tab[8] = {"pwd", "cd", "echo", "exit", "export", "unset", "env", NULL};

	i = 0;
	while (str && tab[i])
	{
		if (!ft_strcmp(str, tab[i]))
			return (1);
		i++;
	}
	return (0);
}
