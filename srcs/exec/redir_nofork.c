/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_nofork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 00:59:43 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/25 02:34:31 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	invalid_fd_nofork(t_data *data, t_cmd *cmd, char *file)
{
	(void)data;
	(void)cmd;
	ft_printf("bash: %s: ", file);
	perror("");
	return (1);
}

int	openfiles_nofork(t_data *data, t_cmd *cmd)
{
	t_list	*tmp;
	int		fd;

	fd = -1;
	tmp = cmd->lst;
	while (tmp)
	{
		if (tmp->type == 1)
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (tmp->type == 2)
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (tmp->type == 3)
			fd = open(tmp->file, O_RDONLY);
		else if (tmp->type == 4)
			fd = 0; // quelpipe(data, data->docs, tmp->file);
		fprintf(stderr, "FD = %i\n", fd);
		if (fd == -1)
			return (invalid_fd_nofork(data, cmd, tmp->file));
		if (tmp->type == 1 || tmp->type == 2)
			dup2(fd, STDOUT_FILENO);
		else
			dup2(fd, STDIN_FILENO);
		if (tmp->type != 4)
			close(fd);
		tmp = tmp->next;
	}
	for (int i = 0; i < data->nb_hd; i++)
		close(data->docs[i].fd[0]);
	// close_heredocs(data->docs, data->nb_hd);
	return (0);
}
