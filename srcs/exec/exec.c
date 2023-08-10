/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:53:20 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/08 22:28:22 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*write_path(char *cmd, t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	while (data->path && data->path[i] && cmd)
	{
		path = ft_strjoin(data->path[i], "/");
		if (!path)
			return ("");
		path = ft_realloc(path, cmd);
		if (access(path, F_OK | X_OK) != -1)
			return (path);
		free(path);
		i++;
	}
	return ("");
}

void	*execute(t_data *data, t_cmd *cmd, char ***env)
{
	char	*path;

	if (cmd->cmd && ft_strchr(cmd->cmd, '/'))
		path = cmd->cmd;
	else
	{
		data->path = path_recup(*env);
		if (!data->path)
			return (ft_printf("%s: command not found\n", cmd->cmd), NULL);
		path = write_path(cmd->cmd, data);
		ft_freetab(data->path);
	}
	execve(path, cmd->arg, data->env_copy);
	if (errno == 13)
		ft_printf("%s: permission denied\n", cmd->cmd);
	else if (cmd->cmd && ft_strchr(cmd->cmd, '/'))
		ft_printf("%s: no such file or directory \n", cmd->cmd);
	else
		error_cmd(cmd->cmd);
	return (NULL);
}

int	get_cmd(t_data *data)
{
	data->onecmd = parse(data->tab[0]);
	if (data->onecmd == NULL)
	{
		free_arg(1, 1, 0, data->pid, data->tab),
		exit(1);
	}
	if (ft_is_builtin_vrmnt(data->onecmd->cmd))
		return (1);
	free_arg(0, 1, 1, data->onecmd->arg, &data->onecmd->lst);
	return (0);
}

char	**path_recup(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}
