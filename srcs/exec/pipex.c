/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:40:18 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/11 23:18:58 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_nofork(t_data *data, t_cmd *cmd, char ***env)
{
	free(data->pid);
	data->fddup[0] = dup(STDOUT_FILENO);
	data->fddup[1] = dup(STDIN_FILENO);
	if (!openfiles_nofork(data, cmd))
	{
		printf("JEXCUTE %s DANS NO FORK\n", cmd->cmd);
		ft_is_builtin(cmd, env);
		dupclose(data->fddup);
		free_arg(0, 1, 1, data->onecmd->arg, &data->onecmd->lst);
		return (0);
	}
	dupclose(data->fddup);
	return (0);
}

void	ft_enfant(t_data *data, char **argv, int i, char ***env)
{
	t_cmd	*cmd;

	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, &slash);
	cmd = NULL;
	free(data->pid);
	cmd = parse(argv[i]);
	data->cmds = cmd;
	if (cmd == NULL)
	{
		close_heredocs(data->docs, data->nb_hd);
		free_arg(0, 2, 1, cmd->arg, data->tab, &cmd->lst);
		exit(1);
	}
	redirection(data, i, cmd);
	if (cmd->cmd && !ft_is_builtin(cmd, env))
		execute(data, cmd, env);
	free_arg(0, 3, 1, data->env_copy, cmd->arg, data->tab, &cmd->lst);
	exit(127);
}

void	ft_parent(t_data *data, int i)
{
	close(data->fd[1]);
	if (i != 0)
		close(data->previous);
	data->previous = data->fd[0];
	signal(SIGQUIT, SIG_IGN);
}

void	*ft_pipex(t_data *data, char **argv, char ***env)
{
	int	i;

	i = -1;
	if (data->nbcmd == 1 && get_cmd(data))
		return (ft_nofork(data, data->onecmd, env), NULL);
	while (++i < data->nbcmd)
	{
		if (pipe(data->fd) == -1)
			return (write(2, "pipe failed\n", 13), NULL);
		signal(SIGINT, SIG_IGN);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			ft_enfant(data, argv, i, env);
		else if (data->pid[i] > 0)
			ft_parent(data, i);
	}
	signal(SIGINT, &ctrlc);
	return (free_pipex(data));
}
